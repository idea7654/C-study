#include <iostream>
#include <vector>
#include <algorithm>
enum class city : int
{
    MOSCOW,
    LONDON,
    SEOUL,
    SEATTLE,
    DUBAI,
    SYDNEY
};

std::ostream& operator<<(std::ostream& os, const city c)
{
    switch(c)
    {
        case city::LONDON:
            os<<"London";
            return os;
        case city::MOSCOW:
            os<<"Moscow";
            return os;
        case city::SEOUL:
            os<<"Seoul";
            return os;
        case city::SEATTLE:
            os<<"Seattle";
            return os;
        case city::DUBAI:
            os<<"Dubai";
            return os;
        case city::SYDNEY:
            os<<"Sydney";
            return os;
        default:
            return os;
    }
}

struct graph
{
    std::vector<std::vector<std::pair<int, int>>> data;

    graph(int n)
    {
        data = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>());
    }

    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "add Edge: " << c1 << "-" << c2 << "=" << dis << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1].push_back({n2, dis});
        data[n2].push_back({n1, dis});
    }

    void removeEdge(const city c1, const city c2)
    {
        std::cout << "Remove Edge: " << c1 << "-" << c2 << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        std::remove_if(data[n1].begin(), data[n1].end(), [n2](const auto& pair){
            return pair.first == n2;
        });
        std::remove_if(data[n2].begin(), data[n2].end(), [n1](const auto& pair){
            return pair.first == n1;
        });
    }
};

int main()
{
    

    while(true)
    {

    }

    return 0;
}