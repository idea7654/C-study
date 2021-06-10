#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <future>
#include <thread>

using namespace std;

constexpr long long maxSize = 100000000;
constexpr long long fir = 25000000;
constexpr long long sec = 50000000;
constexpr long long thi = 75000000;
constexpr long long fou = 100000000;

void sumUp(promise<unsigned long long> &&prom, const vector<int> &val, unsigned long long beg, unsigned long long end){
    unsigned long long sum{};
    for(auto i = beg; i < end; i++)
    {
        sum += val[i];
    }
    prom.set_value(sum);
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

    promise<unsigned long long> prom1;
    promise<unsigned long long> prom2;
    promise<unsigned long long> prom3;
    promise<unsigned long long> prom4;

    auto fut1 = prom1.get_future();
    auto fut2 = prom2.get_future();
    auto fut3 = prom3.get_future();
    auto fut4 = prom4.get_future();

    const auto sta = chrono::system_clock::now();

    thread t1(sumUp, move(prom1), ref(randValues), 0, fir);
    thread t2(sumUp, move(prom2), ref(randValues), fir, sec);
    thread t3(sumUp, move(prom3), ref(randValues), sec, thi);
    thread t4(sumUp, move(prom4), ref(randValues), thi, fou);

    auto sum = fut1.get() + fut2.get() + fut3.get() + fut4.get();

    chrono::duration<double> dur = chrono::system_clock::now() - sta;

    cout << "Time for addition: " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    cout << endl;

    while(true){

    }
}