//성, 이름, 접종여부
//int, int, bool
//이름순서로 정렬
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

class Student
{
    private:
        pair<int, int> name;
        bool vaccinated;
    public:
        Student(pair<int, int>n, bool vaccinate):
            name(n), vaccinated(vaccinate) {}
        
        auto getName() {return name;};
        auto isVaccinated() {return vaccinated;};

        bool operator==(const Student& p){
            return this->name == p.name;
        }

        bool operator<(const Student& p){
            return this->name < p.name;
        }

        bool operator>(const Student & p){
            return this->name > p.name;
        }
};

auto generate_random_Student(int max)
{
    random_device rd;
    mt19937 rand(rd());

    uniform_int_distribution<mt19937::result_type> uniform_dist(1, max);

    auto random_name = make_pair(uniform_dist(rand), uniform_dist(rand));
    bool is_vaccinated = uniform_dist(rand) % 2 ? true : false;

    return Student(random_name, is_vaccinated);
}

bool needs_vaccination(Student p, vector<Student>& people)
{
    auto first = people.begin();
    auto last = people.end();

    while(true)
    {
        auto range_length = distance(first, last);
        auto mid_index = floor(range_length / 2);
        auto mid_element = *(first + mid_index);

        if(mid_element == p && mid_element.isVaccinated() == true){
            return true;
        }else if(mid_element == p && mid_element.isVaccinated() == false){
            return false;
        }else if(p < mid_element){
            advance(first, mid_index);
        }

        if(p > mid_element){
            advance(last, -mid_index);
        }

        if(mid_index == 1){
            return true;
        }
    }
}

void search_test(int size, Student P)
{
    vector<Student> people;

    for(auto i = 0; i < size; i++)
    {
        people.push_back(generate_random_Student(size));
    }

    sort(people.begin(), people.end());

    auto begin = chrono::steady_clock::now();

    bool search_result = needs_vaccination(P, people);

    auto end = chrono::steady_clock::now();
    auto diff = chrono::duration_cast<chrono::microseconds>(end - begin);

    cout << "Time for binary: " << diff.count() << "us" << endl;

    if(search_result){
        cout << "(" << P.getName().first << " " << P.getName().second << ") " << "student is need vaccinate" << endl;
    }else{
        cout << "(" << P.getName().first << " " << P.getName().second << ") " << "student is not need vaccinate" << endl;
    }
}

int main()
{
    auto p = generate_random_Student(1000);

    search_test(1000, p);
    search_test(10000, p);
    search_test(100000, p);

    while(true)
    {
        
    }
}