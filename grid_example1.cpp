#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
//각각의 작업은 고유한 ID, 시간시간, 종료시간을 가짐
//int, int, int
//N개의 작업을 포함하는 list작성..각 작업은 1부터N까지의 고유한 ID를 가지며, 시작시간과 종료시간은 임의의 정수로 설정
//종료시간을 기준으로 전체작업 리스트 정렬
//그리디 방식으로 가장 빠른 종료시간을 갖는 작업을 선택
//현재 선택된 작업과 시간이 겹치는 작업은 모두 제거..즉, 현재 작업 종료시간보다 먼저 작업하는 작업은 제거
//리스트에 작업이 남아있으면 b로 이동..

using namespace std;

struct Object
{
    int id;
    int startTime;
    int finishTime;

    Object(int i, int st, int ft) : id(i), startTime(st), finishTime(ft) {};

    inline bool operator<(const Object &obj) const
    {
        return this->finishTime < obj.finishTime;
    }
    friend ostream& operator<<(ostream& os, const Object& obj);
};

ostream& operator<<(ostream& os, const Object &obj)
{
    os << "[" << obj.id << "] startTime: " << obj.startTime << " \t finishTime: " << obj.finishTime;
    return os;
}
void getWork(vector<Object> &obj, int count)
{
    //obj -> 종료시간이 되어야 함..
    int finish = 0;

    vector<Object> newVector;
    newVector.reserve(obj.size());

    sort(obj.begin(), obj.end());

    auto current_obj = obj.begin();
    // for(auto i : obj)
    // {
    //     cout << i << endl;
    // }
    while(finish < count && current_obj != obj.end())
    {
        if(current_obj == obj.begin())
        {
            newVector.push_back(*current_obj);
            finish = current_obj->finishTime;
        }else{
            if(current_obj->startTime >= finish){
                newVector.push_back(*current_obj);
                finish = current_obj->finishTime;
            }
            //newVector.push_back(*current_obj);
        }
        current_obj++;
    }
    for(auto i : newVector)
    {
        cout << i << endl;
    }
}

int main()
{
    vector<Object> objects;
    objects.reserve(10);
    vector<int> startTime {5, 6, 16, 7, 9, 10, 6, 2, 10, 4};
    vector<int> finishTime {9, 20, 19, 10, 19, 19, 12, 17, 13, 7};
    for(int i = 0; i < 10; i++)
    {
        objects.push_back(Object(i+1, startTime[i], finishTime[i]));
    }

    getWork(objects, 20);

    while(true)
    {

    }
}