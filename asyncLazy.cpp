#include <chrono>
#include <future>
#include <iostream>

using namespace std;

int main(){
    cout << endl;
    auto begin = chrono::system_clock::now();

    auto asyncLazy = async(launch::deferred, []{return chrono::system_clock::now();});

    auto asyncEager = async(launch::async, []{return chrono::system_clock::now();});

    this_thread::sleep_for(chrono::seconds(1));

    auto lazyStart = asyncLazy.get() - begin;
    auto eagerStart = asyncEager.get() - begin;

    auto lazyDuration = chrono::duration<double>(lazyStart).count();
    auto eagerDuration = chrono::duration<double>(eagerStart).count();

    cout << "asyncLazy evaluated after: " << lazyDuration << " seconds" << endl;
    cout << "asyncEager evaluated after: " << eagerDuration << " seconds" << endl;

    cout << endl;

    while(true){
        
    }
}