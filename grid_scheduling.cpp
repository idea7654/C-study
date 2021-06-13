#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
auto compute_waiting_times(vector<T> &service_times)
{
    vector<T> W(service_times.size());
    W[0] = 0;

    for(auto i = 1; i < service_times.size(); i++)
    {
        W[i] = W[i - 1] + service_times[i - 1];
    }

    return W;
}

template<typename T>
void print_vector(vector<T>& V)
{
    for(auto &i : V)
    {
        cout.width(2);
        cout << i << " ";
    }
    cout << endl;
}

template<typename T>
void compute_and_print_waiting_times(vector<T> &service_times)
{
    auto waiting_times = compute_waiting_times<int>(service_times);

    cout << "- duration: ";
    print_vector<T>(service_times);

    cout << "- waiting: ";
    print_vector<T>(waiting_times);

    auto ave_waiting_times = accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
    cout << "- ava waiting: " << ave_waiting_times;

    cout << endl;
}

int main()
{
    vector<int> service_times {8, 1, 2, 4, 9, 2, 3, 5};

    cout << "[init duration & waiting]: " << endl;
    compute_and_print_waiting_times<int>(service_times);

    sort(service_times.begin(), service_times.end());

    cout << endl;
    cout << "[Sorted duration & waiting]: " << endl;
    compute_and_print_waiting_times<int>(service_times);

    while(true)
    {

    }
}