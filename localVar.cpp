#include <mutex>
#include <chrono>
#include <iostream>
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

thread_local unsigned long long tmpSum = 0;

mutex myMutex;

void sumUp(atomic<unsigned long long> &sum, const vector<int> &val, unsigned long long beg, unsigned long long end){
    //unsigned long long tmpSum{};
    for(auto i = beg; i < end; i++)
    {
        tmpSum += val[i];
    }
    //lock_guard<mutex> myLock(myMutex);
    //sum += tmpSum;
    sum.fetch_add(tmpSum, memory_order_relaxed);
}

int main()
{
    cout << endl;
    vector<int> randValues;
    randValues.reserve(maxSize);
    
    mt19937 engine;
    uniform_int_distribution<> uniformDist(1, 10);
    for (long long i = 0; i < maxSize; i++)
    {
        randValues.push_back(uniformDist(engine));
    }
    atomic<unsigned long long> sum{};
    const auto sta = chrono::system_clock::now();

    thread t1(sumUp, ref(sum), ref(randValues), 0, fir);
    thread t2(sumUp, ref(sum), ref(randValues), fir, sec);
    thread t3(sumUp, ref(sum), ref(randValues), sec, thi);
    thread t4(sumUp, ref(sum), ref(randValues), thi, fou);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    chrono::duration<double> dur = chrono::system_clock::now() - sta;

    cout << "Time for addition: " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;
    cout << endl;

    while(true){

    }
}