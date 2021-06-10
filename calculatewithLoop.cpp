#include <chrono>
#include <iostream>
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
    for(long long i = 0; i < maxSize; ++i){
        randValues.push_back(uniformDist(engine));
    }
    const auto sta = chrono::steady_clock::now();

    unsigned long long sum = {};
    for(auto n: randValues){
        sum += n;
    }

    const chrono::duration<double> dur = chrono::steady_clock::now() - sta;
    cout << "Time for mySimulation " << dur.count() << " seconds" << endl;
    cout << "Result: " << sum << endl;
    cout << endl;

    while(true)
    {
 
    }
}