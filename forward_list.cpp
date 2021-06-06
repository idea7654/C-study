#include <string>
#include <iostream>
#include <forward_list>

using namespace std;

struct citizen
{
    string name;
    int age;
};

ostream &operator<<(ostream &os, const citizen &c)
{
    return (os << "[" << c.name << ", " << c.age << "]");
}

int main()
{
    forward_list<citizen> citizens = {
        {"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
    };

    auto citizens_copy = citizens;

    cout << "all citizens: ";
    for(const auto &c : citizens){
        cout << c << " ";
    }
    cout << endl;

    citizens.remove_if([](const citizen &c){
        return (c.age < 19);
    });

    cout << "Now voters: ";
    for(const auto &c : citizens)
    {
        cout << c << " ";
    } 
    cout << endl;

    citizens_copy.remove_if([](const citizen &c){
        return (c.age != 18);
    });
    cout << "Be Voter next year: ";
    for(const auto &c : citizens_copy){
        cout << c << " ";
    }
    cout << endl;

    while(true){
        
    }
}