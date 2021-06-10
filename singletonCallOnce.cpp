#include <chrono>
#include <iostream>
#include <future>
#include <mutex>
#include <thread>
#include <atomic>

constexpr auto tenMill = 10000000;
using namespace std;

class MySingleton{
    public:
        static MySingleton* getInstance(){
            //call_once(initInstanceFlag, &MySingleton::initSingleton);
            //volatile int dummy{};
            //return *instance;
            MySingleton* sin = instance.load();
            if(!sin)
            {
                lock_guard<mutex> myLock(myMutex);
                sin = instance.load(memory_order_relaxed);
                if(!sin)
                {
                    sin = new MySingleton();
                    instance.store(sin);
                }
            }
            volatile int dummy{};
            return sin;
        }
    private:
        MySingleton() = default;
        ~MySingleton() = default;
        MySingleton(const MySingleton&) = delete;
        MySingleton& operator=(const MySingleton&) = delete;

        //static MySingleton* instance;
        //static once_flag initInstanceFlag;

        // static void initSingleton(){
        //     instance = new MySingleton();
        // }
        static atomic<MySingleton*> instance;
        static mutex myMutex;
};

//MySingleton* MySingleton::instance = nullptr;
//once_flag MySingleton::initInstanceFlag;
atomic<MySingleton*> MySingleton::instance;
mutex MySingleton::myMutex;