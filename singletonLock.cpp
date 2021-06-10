#include <chrono>
#include <iostream>
#include <future>
#include <mutex>

constexpr auto tenMill = 10000000;

using namespace std;

mutex myMutex;

class MySingleton{
    public:
        static MySingleton& getInstance(){
            lock_guard<mutex> myLock(myMutex);
            if(!instance){
                instance = new MySingleton();
            }
            volatile int dummy{};
            return *instance;
        }
    private:
        MySingleton() = default;
        ~MySingleton() = default;
        MySingleton(const MySingleton&) = delete;
        MySingleton& operator=(const MySingleton&) = delete;

        static MySingleton* instance;
};

MySingleton* MySingleton::instance = nullptr;