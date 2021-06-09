#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;

class hash_map
{
    //std::vector<int> data;
    std::vector<std::list<int>> data;
    public:
        hash_map(size_t n) //최대 크기를 표현하는 타입
        {
            //data = std::vector<int>(n, -1);
            data.resize(n);
        }
        void insert(uint value)
        {
            int n = data.size();
            //data[value % n] = value;
            //std::cout << value << " add " << std::endl;
            data[value % n].push_back(value);
            std::cout << value << " add " << std::endl;
        }
        bool find(uint value)
        {
            int n = data.size();
            // return (data[value % n] == value);
            auto& entries = data[value%n];
            return std::find(entries.begin(), entries.end(), value) != entries.end();
        }

        void erase(uint value)
        {
            int n = data.size();
            // if(data[value % n] == value)
            // {
            //     data[value % n] = -1;
            //     std::cout << value << " remove " << std::endl;
            // }
            auto& entries = data[value%n];
            auto iter = std::find(entries.begin(), entries.end(), value);
            if(iter != entries.end()){
                entries.erase(iter);
                std::cout << value << " remove " << std::endl;
            }
        }
};

int main()
{
    hash_map map(7);

    auto print = [&](int value){
        if(map.find(value)){
            std::cout << " in hash map " << value << " find";
        }else{
            std::cout << " in hash map " << value << " not found";
        }
        std::cout << std::endl;
    };

    map.insert(2);
    map.insert(25);
    map.insert(10);
    //print(25);

    map.insert(100);
    map.insert(55);
    print(100);
    print(2);

    map.erase(2);
    while(true)
    {

    }
}