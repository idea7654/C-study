#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Object
{
    int id;
    int weight;
    double value;
    double value_per_unit_weight;

    Object(int i, int w, double v) : id(i), weight(w), value(v), value_per_unit_weight(v / w) {};

    inline bool operator<(const Object &obj) const
    {
        return this->value_per_unit_weight < obj.value_per_unit_weight;
    }

    friend ostream& operator<<(ostream& os, const Object& obj);
};

ostream& operator<<(ostream& os, const Object &obj)
{
    os << "[" << obj.id << "] price: " << obj.value << " \t weight: " << obj.weight << " kg \tvaluePerWeight: " << obj.value_per_unit_weight;
    return os;
}

auto fill_knapsack(vector<Object> &objects, int knapsack_capacity)
{
    vector<Object> knapsack_contents;
    knapsack_contents.reserve(objects.size());

    sort(objects.begin(), objects.end());
    reverse(objects.begin(), objects.end());

    //가장 가치 있는 물건들 먼저 배낭에 추가
    auto current_object = objects.begin();
    int current_total_weight = 0;
    while(current_total_weight < knapsack_capacity && current_object != objects.end())
    {
        knapsack_contents.push_back(*current_object);

        current_total_weight += current_object->weight;
        current_object++;
    }

    //마지막 추가한 물건에 의해 배낭 최대 허용 무게가 초가된 경우
    int weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity; //현재 무게 - 허용무게 = 초과무게
    Object &last_object = knapsack_contents.back(); // 배낭에 들어있는 맨 마지막 물건
    if(weight_of_last_obj_to_remove > 0) // 초과무게가 있으면
    {
        last_object.weight -= weight_of_last_obj_to_remove; //맨 마지막 물건의 무게를 초과무게만큼 빼고
        last_object.value -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove; //값을 해당 비율만큼 빼줌
    }
    return knapsack_contents;
}

int main()
{
    vector<Object> objects;
    objects.reserve(7);

    vector<int> weights {1, 2, 5, 9, 2, 3, 4};
    vector<double> values{10, 7, 15, 10, 12, 11, 5};
    for(auto i = 0; i < 7; i++)
    {
        objects.push_back(Object(i+1, weights[i], values[i]));
    }
    cout << "[Available]" << endl;
    for(auto &o : objects)
    {
        cout << o << endl;
    }
    cout << endl;

    int knapsack_capacity = 7;
    auto solution = fill_knapsack(objects, knapsack_capacity);

    cout << "[In backpack]: " << endl;
    for(auto &o : solution){
        cout << o << endl;
    }
    cout << endl;

    while(true)
    {
        
    }
}