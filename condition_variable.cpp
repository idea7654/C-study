#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mutex_;
condition_variable condVar;

bool dataReady{false};

void doTheWork(){
    cout << "Processing shared data" << endl;
}

void waitingForWork(){
    cout << "Worker: Waiting for work" << endl;
    unique_lock<mutex> lck(mutex_);
    condVar.wait(lck, []{return dataReady;});
    this_thread::sleep_for(chrono::milliseconds(500));
    doTheWork();
    cout << "Work done" << endl;
}

void setDataReady(){
    {
        lock_guard<mutex> lck(mutex_);
        dataReady = true;
    }
    cout << "Sender: Data is Ready" << endl;
    condVar.notify_one();
}

int main()
{
    cout << endl;

    thread t1(waitingForWork);
    thread t2(setDataReady);

    t1.join();
    t2.join();

    cout << endl;

    while(true){

    }
}