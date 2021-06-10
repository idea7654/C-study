#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <atomic>

using namespace std;

constexpr long long maxSize = 100000000;

constexpr long long fir = 25000000;
constexpr long long sec = 50000000;
constexpr long long thi = 75000000;
constexpr long long fou = 100000000;

mutex myMutex;

void sumUp(atomic<unsigned long long> /*unsigned long long*/ &sum,  const vector<int> &val, unsigned long long beg, unsigned long long end){
    for(auto it = beg; it < end; ++it){
        // lock_guard<mutex> myLock(myMutex);
        //sum += val[it];
        sum.fetch_add(val[it]);
    }
}

int main(){
    cout << endl;

    vector<int> randValues;
    randValues.reserve(maxSize);
    mt19937 engine;
    uniform_int_distribution<> uniformDist(1, 10);
    for(long long i = 0; i < maxSize; ++i){
        randValues.push_back(uniformDist(engine));
    }

    // unsigned long long sum = 0;
    atomic<unsigned long long> sum(0);
    const auto sta = chrono::steady_clock::now();

    thread t1(sumUp, ref(sum), ref(randValues), 0, fir);
    thread t2(sumUp, ref(sum), ref(randValues), fir, sec);
    thread t3(sumUp, ref(sum), ref(randValues), sec, thi);
    thread t4(sumUp, ref(sum), ref(randValues), thi, fou);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    chrono::duration<double> dur = chrono::steady_clock::now() - sta;
    cout << "Time for addition " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;
    cout << endl;

    while(true)
    {

    }
}