#pragma once
#pragma comment(lib, "ws2_32")
#include <thread>
#include <WS2tcpip.h>

#include <thread>
#include <vector>

#define MAX_SOCKBUF 1024 //패킷크기
#define MAX_WORKERTHREAD 4 //쓰레드 풀에 넣을 쓰레드 수

enum class IOOperation
{
    RECV,
    SEND
};

//WSAOVERLAPPED구조체를 확장 시켜서 필요한 정보를 더 넣었다,.
struct stOverlappedEx
{
    WSAOVERLAPPED m_wsaOverlapped; //Overlapped I/O구조체
    SOCKET m_socketClient; //클라이언트 소켓
    WSABUF m_wsaBuf; //Overlapped I/O작업 버퍼
    char m_szBuf[MAX_SOCKBUF]; //데이터 버퍼
    IOOperation m_eOperation; //작업 동작 종류
};

//클라이언트 정보를 담기 위한 구조체

struct stClientInfo
{
    SOCKET m_socketClient; //Client와 연결되는 소켓
    stOverlappedEx m_stRecvOverlappedEx; //Recv Overlapped I/O작업을 위한변수
    stOverlappedEx m_stSendOverlappedEx; //SEND Overlapped I/O작업을 위한 변수

    stClientInfo()
    {
        ZeroMemory(&m_stRecvOverlappedEx, sizeof(stOverlappedEx)); //초기화
        ZeroMemory(&m_stSendOverlappedEx, sizeof(stOverlappedEx));
        m_socketClient = INVALID_SOCKET;
    }
};

//클라이언트 정보 저장 구조체
std::vector<stClientInfo> mClientInfos;
//클라이언트의 접속을 받기위한 리슨 소켓
SOCKET		mListenSocket = INVALID_SOCKET;
//접속 되어있는 클라이언트 수
int			mClientCnt = 0;
//IO Worker 스레드
std::vector<std::thread> mIOWorkerThreads;
//Accept 스레드
std::thread	mAccepterThread;
//CompletionPort객체 핸들
HANDLE		mIOCPHandle = INVALID_HANDLE_VALUE;
//작업 쓰레드 동작 플래그
bool		mIsWorkerRun = true;
//접속 쓰레드 동작 플래그
bool		mIsAccepterRun = true;
//소켓 버퍼
char		mSocketBuf[1024] = { 0, };

class IOCompletionPort{
    public:
        IOCompletionPort(void){}
        ~IOCompletionPort(void)
        {
            WSACleanup();
        }

        bool InitSocket()
        {
            WSADATA wsaData;
            int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if(0 != nRet)
            {
                printf("WSAStartUp() Error");
                return false;
            }

            mListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_UDP, NULL, NULL, WSA_FLAG_OVERLAPPED);

            if(INVALID_SOCKET == mListenSocket)
            {
                printf("socket() Error");
                return false;
            }

            //소켓 초기화 성공
            return true;
        }

        //서버용 함수
        //서버의 주소정보를 소켓과 연결시키고 접속 요청을 받기 위해 소켓을 등록하는 함수
        bool BindandListen(int nBindPort)
        {
            SOCKADDR_IN stServerAddr;
            stServerAddr.sin_family = AF_INET;
            stServerAddr.sin_port = htons(nBindPort);
            stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

            //위에서 지정한 서버 주소 정보와 cIOCompletionPort소켓을 연결
            int nRet = bind(mListenSocket, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN));
            if(0 != nRet)
            {
                printf("bind() ERROR");
                return false;
            }

            nRet = listen(mListenSocket, 5); //접속 대기큐 5개
            if(0 != nRet)
            {
                printf("listen() Error");
                return false;
            }

            //서버 등록완료
            return true;
        }

        bool StartServer(const UINT32 maxClientCount)
        {
            CreateClient(maxClientCount);

            //CompletionPort 객체 생성 요청을 한다
            mIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, MAX_WORKERTHREAD);
            if(NULL == mIOCPHandle)
            {
                printf("CreateIOCompletionPort() ERROR");
                return false;
            }

            bool bRet = CreateWorkerThread();
            if(bRet == false)
            {
                return false;
            }

            bRet = CreateAccepterThread();
            if(bRet == false)
            {
                return false;
            }

            //서버 시작
            return true;
        }
        //스레드 파괴
        void DestroyThread()
        {
            mIsWorkerRun = false;
            CloseHandle(mIOCPHandle);

            for(auto& th: mIOWorkerThreads)
            {
                if(th.joinable())
                {
                    th.join();
                }
            }
            //Accepter스레드 종료
            mIsAccepterRun = false;
            closesocket(mListenSocket);

            if(mAccepterThread.joinable())
            {
                mAccepterThread.join();
            }
        }
    private:
        void CreateClient(const UINT32 maxClientCount)
        {
            for(UINT32 i = 0; i < maxClientCount; ++i)
            {
                mClientInfos.emplace_back();
            }
        }
        //WaitingTrhead Queue에서 대기할 스레드들을 생성
        bool CreateWorkerThread()
        {
            unsigned int uidThreadId = 0;
            //WaitingThread Queue에 대기 상태로 넣을 스레드들 생성 권장개는 개수 : cpu개수 * 2 + 1
            for(int i = 0; i < MAX_WORKERTHREAD; i++){
                mIOWorkerThreads.emplace_back([this]{WorkerThread();});
            }

            printf("WorkerThread Start");
            return true;
        }

        bool CreateAccepterThread()
        {
            mAccepterThread = std::thread([this]{AccepterThread();});
            printf("AccepterThread 시작");
            return true;
        }
        //사용하지 않는 클라이언트 정보 구조체를 반환
        stClientInfo* GetEmptyClientInfo()
        {
            for(auto& client : mClientInfos)
            {
                if(INVALID_SOCKET == client.m_socketClient)
                {
                    return &client;
                }
            }
            return nullptr;
        }
        //CompletionPort객체와 소켓과 CompletionKey를 연결
        bool BindIOCompletionPort(stClientInfo* pClientInfo)
        {
            //소켓과pClinetInfo를 CompletionPort객체와 연결시킴
            auto hIOCP = CreateIoCompletionPort((HANDLE)pClientInfo->m_socketClient, mIOCPHandle, (ULONG_PTR)(pClientInfo), 0);
            if(hIOCP == NULL || mIOCPHandle != hIOCP)
            {
                printf("CreateIOCompletionPort() ERROR");
                return false;
            }

            return true;
        }
        //WSARecvOverlapped I/O작업을 시킴
        bool BindRecv(stClientInfo* pClientInfo)
        {
            DWORD dwFlag = 0;
            DWORD dwRecvNumBytes = 0;

            //Overlapped I/O를 위해 각 정보 세팅
            pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.len = MAX_SOCKBUF;
            pClientInfo->m_stRecvOverlappedEx.m_wsaBuf.buf = pClientInfo->m_stRecvOverlappedEx.m_szBuf;
            pClientInfo->m_stRecvOverlappedEx.m_eOperation = IOOperation::RECV;

            int nRet = WSARecv(pClientInfo->m_socketClient, &(pClientInfo->m_stRecvOverlappedEx.m_wsaBuf), 1, &dwRecvNumBytes, &dwFlag, (LPWSAOVERLAPPED) &(pClientInfo->m_stRecvOverlappedEx), NULL);
            if(nRet == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
            {
                printf("WSARecv() ERROR");
                return false;
            }
            return true;
        }

        bool SendMsg(stClientInfo* pClientInfo, char* pMsg, int nLen){
            DWORD dwRecvNumBytes = 0;

            //전송될 메시지 복사
            CopyMemory(pClientInfo->m_stSendOverlappedEx.m_szBuf, pMsg, nLen);

            //Overlapped I/O를 위해 각 정보를 세팅해준다
            pClientInfo->m_stSendOverlappedEx.m_wsaBuf.len = nLen;
            pClientInfo->m_stSendOverlappedEx.m_wsaBuf.buf = pClientInfo->m_stSendOverlappedEx.m_szBuf;
            pClientInfo->m_stSendOverlappedEx.m_eOperation = IOOperation::SEND;

            int nRet = WSASend(pClientInfo->m_socketClient, &(pClientInfo->m_stSendOverlappedEx.m_wsaBuf), 1, &dwRecvNumBytes, 0, (LPWSAOVERLAPPED) &(pClientInfo->m_stSendOverlappedEx), NULL);

            //socket_error면 끊어진걸로 처리
            if(nRet == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
            {
                printf("WSASend() ERROR");
                return false;
            }

            return true;
        }
        //Overlapped I/O작업에 대한 완료 통보를 받아
        //그에 해당하는 처리를 하는 함수
        void WorkerThread()
        {
            //CompletionKey를 받을 포인터 변수
            stClientInfo* pClientInfo = NULL;
            //함수 호출 성공 여부
            bool bSuccess = true;
            //Overlapped I/O작업에서 전송된 데이터 크기
            DWORD dwIoSize = 0;
            //I/O작업을 위해 요청한 Overlapped 구조체를 받을 포인터
            LPOVERLAPPED lpOverlapped = NULL;

            while(mIsWorkerRun)
            {
                //////////////////////////////////////////////////////
			    //이 함수로 인해 쓰레드들은 WaitingThread Queue에
			    //대기 상태로 들어가게 된다.
			    //완료된 Overlapped I/O작업이 발생하면 IOCP Queue에서
			    //완료된 작업을 가져와 뒤 처리를 한다.
			    //그리고 PostQueuedCompletionStatus()함수에의해 사용자
			    //메세지가 도착되면 쓰레드를 종료한다.
			    //////////////////////////////////////////////////////
            }
        }

        void AccepterThread()
        {
            
        }
};