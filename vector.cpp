#include <iostream>
#include <forward_list>
#include <vector>

//지난 몇년간의 싱가포르 F1 그랑프리 수상자 명단이 있음
//벡터 반복자를 사용하여 데이터로부터 유용한 정보를 검색
//다음으로 forward_list로 같은 작업 반복하고
//벡터 반복자와 다른 점을 살펴봄

using namespace std;

int main(){
    vector<string> vec = {
        "Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg", "Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel", "Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
    };

    auto it = vec.begin();
    cout << "latest winner: "<< *it << endl;
    
    it += 8;
    cout << "8years ago winner: " << *it << endl;

    advance(it, -3);
    cout << "and 3years later winner: " << *it << endl;

    forward_list<string> fwd(vec.begin(), vec.end());

    auto it1 = fwd.begin();
    cout << "latest winnder: " << *it1 << endl;
    
    advance(it1, 5);
    cout << "5years ago winner: " << *it1 << endl;

    while(true){
        
    }
}