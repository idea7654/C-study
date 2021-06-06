//여러 개의 음악을 이용하여 재생 목록을 생성
//재생목록에 음악을 추가
//재생 목록에서 음악을 제거
//음악을 순환적으로 재생

#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> list1 = {1, 2, 3, 4, 5};
    list1.push_back(6);
    list1.insert(next(list1.begin()), 0);
    list1.insert(list1.end(), 7);

    list1.pop_back();

    cout << "insert & remove after list: ";
    for(auto i : list1){
        cout << i << " ";
    }

    while(true){
        
    }
}