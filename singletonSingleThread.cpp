#include <chrono>
#include <iostream>

using namespace std;

constexpr auto tenMill = 10000000;

class MySingleton{
    public:
        static MySingleton& getInstance(){
            static MySingleton instance;
            volatile int dummy{};
            return instance;
        }
    private:
        MySingleton() = default;
        ~MySingleton() = default;
        MySingleton(const MySingleton&) = delete;
        MySingleton& operator=(const MySingleton&) = delete;
};

int main()
{
    constexpr auto fourtyMill = 4 * tenMill;

    const auto begin = chrono::system_clock::now();
    for(size_t i = 0; i <= fourtyMill; ++i){
        MySingleton::getInstance();
    }

    const auto end = chrono::system_clock::now() - begin;

    cout << chrono::duration<double>(end).count() << endl;
}