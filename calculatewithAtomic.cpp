#include <atomic>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

constexpr long long maxSize = 100000000;
using namespace std;

int main()
{
    cout << endl;
    vector<int> randValues;
    randValues.reserve(maxSize);

    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<> uniformDist(1, 10);
    for(long long i = 0; i < maxSize; ++i)
    {
        randValues.push_back(uniformDist(engine));
    }

    atomic<unsigned long long> sum = {};
    cout << boolalpha << "sum.is_lock_free(): " << sum.is_lock_free() << endl;
    cout << endl;

    auto sta = chrono::steady_clock::now();

    for(auto i: randValues) sum += i;
    chrono::duration<double> dur = chrono::steady_clock::now() - sta;

    cout << "Time for addition " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;
    cout << endl;

    sum = 0;
    sta = chrono::steady_clock::now();
    for(auto i: randValues) sum.fetch_add(i);

    dur = chrono::steady_clock::now() - sta;
    cout << "Time for addition " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;
    cout << endl;

    while(true)
    {
      
    }
}