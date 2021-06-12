#include <iostream>
#include <vector>

using namespace std;

template <typename T>
vector<T> merge(vector<T>& arr1, vector<T>& arr2)
{
    vector<T> merged;

    auto iter1 = arr1.begin(); // 첫 배열의 시작점
    auto iter2 = arr2.begin(); // 두번째 배열의 시작점

    while(iter1 != arr1.end() && iter2 != arr2.end()) //원소개수가 1이 아니라면 반복
    {
        if(*iter1 < *iter2) //시작점의 크기를 비교
        {
            merged.emplace_back(*iter1); 
            iter1++;
        }
        else{
            merged.emplace_back(*iter2);
            iter2++;
        }
        //더 작은 수를 merged에 넣고 해당 값을 1증가시킴
    }

    if(iter1 != arr1.end())
    {
        for(; iter1 != arr1.end(); iter1++)
        {
            merged.emplace_back(*iter1);
        }
        //iter1이 끝점이 아니라면(iter2가 끝났다면) 남은만큼 merged에 iter1원소를 추가
    }else{
        for(; iter2 != arr2.end(); iter2++)
        {
            merged.emplace_back(*iter2);
        }
    }
    return merged;
}

template <typename T>
vector<T> merge_sort(vector<T> arr)
{
    if(arr.size() > 1)
    {
        auto mid = size_t(arr.size() / 2);
        auto left_half = merge_sort<T>(vector<T>(arr.begin(), arr.begin() + mid));
        auto right_half = merge_sort<T>(vector<T>(arr.begin() + mid, arr.end()));

        return merge<T>(left_half, right_half);
    }

    return arr;
}

template <typename T>
void print_vector(vector<T> arr)
{
    for(auto i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}

void run_merge_sort_test()
{
    vector<int> S1 {45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
    vector<float> S2 {45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f};
    vector<double> S3 {45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0};
    vector<char> C {'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

    cout << "not sorted vector: " << endl;

    print_vector(S1);
    print_vector(S2);
    print_vector(S3);
    print_vector(C);
    cout << endl;

    auto sorted_S1 = merge_sort<int>(S1);
    auto sorted_S2 = merge_sort<float>(S2);
    auto sorted_S3 = merge_sort<double>(S3);
    auto sorted_C = merge_sort<char>(C);

    cout << "sorted by merge vector: " << endl;
    print_vector(sorted_S1);
    print_vector(sorted_S2);
    print_vector(sorted_S3);
    print_vector(sorted_C);
    cout << endl;
}

int main()
{
    run_merge_sort_test();
    while(true)
    {

    }
    return 0;
}