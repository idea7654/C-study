#include <future>
#include <thread>
#include <iostream>

using namespace std;

int main(){
    cout << endl;

    int res;
    thread t([&]{res=2000+11;});
    t.join();
    cout << "res: " << res << endl;

    auto fut = async([]{return 2000 + 11;});
    cout << "fut.get(): " << fut.get() << endl;

    cout << endl;
    while(true){
        
    }
};