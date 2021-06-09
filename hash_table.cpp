#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void print(const unordered_set<int>& container)
{
    for(const auto& element : container)
    {
        std::cout << element << " ";
    }
    cout << endl;
}

void print(const unordered_map<int, int>& container)
{
    for(const auto& element : container)
    {
        cout << element.first << ": " << element.second << ", ";
    }
    cout << endl;
}

void find(const unordered_set<int>& container, const int element)
{
    if(container.find(element) == container.end())
    {
        cout << element << " search: Fail" << endl;
    }else{
        cout << element << " search: Success" << endl;
    }
}

void find(const unordered_map<int, int>& container, const int element)
{
    auto it = container.find(element);
    if(it == container.end())
    {
        cout << element << " search: Fail" << endl;
    }else{
        cout << element << " search: Success, value = " << it->second << endl;
    }
}

int main()
{
    cout << "*** unordered_set example ***" << endl;
    unordered_set<int> set1 = {1, 2, 3, 4, 5};

    cout << "set1 InitValue: "; print(set1);

    set1.insert(2);
    cout << "add 2: "; print(set1);

    set1.insert(10);
    set1.insert(300);
    cout << "add 10, 300: "; print(set1);

    find(set1, 4);
    find(set1, 100);

    set1.erase(2);
    cout << "remove 2: "; print(set1);

    find(set1, 2);

    cout << "*** unordered_map example ***" << endl;

    unordered_map<int, int> squareMap;

    squareMap.insert({2, 4});
    squareMap[3] = 9;
    cout << "add 2, 3's sqrt: "; print(squareMap);

    squareMap[20] = 400;
    squareMap[30] = 900;
    cout << "add 20, 30's sqrt: "; print(squareMap);

    find(squareMap, 10);
    find(squareMap, 20);
    cout << "squareMap[3] = " << squareMap[3] << endl;
    cout << "squareMap[100] = " << squareMap[100] << endl;
    print(squareMap);

    while(true)
    {
        
    }
}