#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"sort.h"
using namespace std;

int main() {
    vector<int> arr = { 64, 25, 12, 22, 11, 90, 34 };
    //selectsort_1(arr);
    selectsort_2(arr);
    cout << "ÅÅÐòºóÊý×é£º";
    for (int num : arr) 
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}