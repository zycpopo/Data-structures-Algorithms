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

//��������(�ȶ���)
void CountingSort(std::vector<int>& arr) 
{
	if (arr.empty()) return;

	//STL
	int min_val = *std::min_element(arr.begin(), arr.end());
	int max_val = *std::max_element(arr.begin(), arr.end());
	int range = max_val - min_val + 1;

	std::vector<int> count(range, 0);

	for (int num : arr)
	{
		count[num - min_val]++;
	}

	std::vector<int> output(arr.size());
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1]; 
	}

	for (int i = arr.size() - 1; i >= 0; i--) {
		output[count[arr[i] - min_val] - 1] = arr[i];
		count[arr[i] - min_val]--;
	}

	arr = output;
}

//ð������
void BubbleSort(std::vector<int>& arr)
{
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) 
	{
		bool swapped = false;                  
		for (int j = 0; j < n - i - 1; j++)
		{ 
			if (arr[j] > arr[j + 1]) 
			{
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break; // ���û�н�����˵���Ѿ�������ǰ����
	}
}