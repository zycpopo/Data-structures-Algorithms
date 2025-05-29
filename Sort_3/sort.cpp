#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"sort.h"
using namespace std;

void selectsort_1(vector<int>& arr)
{
	int n = arr.size();
	for (int i = 0; i < n - 1; i++)
	{
		int minindex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minindex])
			{
				minindex = j;
			}
		}
		swap(arr[i], arr[minindex]);
	}
}

void selectsort_2(vector<int>& arr)
{
	int n = arr.size();
	for (int i = 0; i < n / 2; i++)
	{
		int minindex = i;
		int maxindex = i;

		for (int j = i + 1; j < n - i; ++j)
		{
			if (arr[j] < arr[minindex]) {
				minindex = j;
			}
			if (arr[j] > arr[maxindex]) {
				maxindex = j;
		}

			if (minindex != i) {
				swap(arr[i], arr[minindex]);
				// ������ֵλ�øպñ���Сֵ�������ˣ���Ҫ����maxIndex
				if (maxindex == i) {
					maxindex = minindex;
				}
			}
			// �ٽ����ֵ�ŵ��ұ�
			if (maxindex != n - 1 - i) {
				swap(arr[n - 1 - i], arr[maxindex]);
			}
		}
	}
}
