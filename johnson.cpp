#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;


bool HasNegativeCycle(const vector<Edge> &edges, vector<int> distance)
{
    for(auto &e : edges)
        {
        if(distance[e.src] == UNKNOWN)
            continue;
        if(distance[e.src] + e.weight < distance[e.dst])
            return true;
    }

    return false;
}

vector<int> BellmanFord(vector<Edge> edges, int V)
{
    vector<int> distance(V + 1, UNKNOWN);

    int s = V;
    for(int i = 0; i < V; i++)
    {
        edges.push_back(Edge {s, i, 0});
    }

    distance[s] = 0;

    for(int i = 0; i < V; i++)
    {
        for(auto &e : edges)
        {
            if(distance[e.src] == UNKNOWN)
                continue;

            if(distance[e.dst] > distance[e.src] + e.weight)
            {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    if(HasNegativeCycle(edges, distance))
    {
        cout << "Found minus weight" << endl;
        return {};
    }

    return distance;
}
