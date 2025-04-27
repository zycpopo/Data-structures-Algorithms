#define _CRT_SECURE_NO_WARNINGS
#include"work.h"

void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void insertsort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0)
		{
			if (arr[end] > tmp)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else { break; }
		}
		arr[end + 1] = tmp;
	}
}

void shellsort(int* arr, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > tmp)
				{
					arr[end + gap] = arr[end];
					end-=gap;
				}
				else {
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}
}

void selectsort(int* arr, int n)
{
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int maxi = begin;
		int mini = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (arr[i] > arr[maxi])
			{
				maxi = i;
			}
			if (arr[i] < arr[mini])
			{
				mini = i;
			}
		}
		Swap(&arr[mini], &arr[begin]);
	    if (maxi == begin)
		{
			maxi = mini;
		}
		Swap(&arr[maxi], &arr[end]);
		begin++;
		end--;
	}
}

void adjustdown(int* arr, int parent, int n)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child] < arr[child + 1])
		{
			child++;
		}

		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}

void heapsort(int* arr, int n)
{
	//建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		adjustdown(arr, i, n);
	}
	//堆排序
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		adjustdown(arr, 0, end);
		end--;
	}
}

void bubblesort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n-1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

//hoare版本
int _QuickSort1(int* arr, int left, int right)
{
	int keyi = left;
	++left;
	while (left <= right)
	{
		//right：从右往左走，找比基准值要小的
		while (left <= right && arr[right] > arr[keyi])
		{
			right--;
		}
		//left：从左往右走，找比基准值要大的
		while (left <= right && arr[left] < arr[keyi])
		{
			left++;
		}
		//right left 
		if (left <= right)
		{
			Swap(&arr[left++], &arr[right--]);
		}
	}
	Swap(&arr[keyi], &arr[right]);
	return right;
}
//lomuto前后指针法
int _QuickSort(int* arr, int left, int right)
{
	int keyi = left;
	int prev = left, cur = prev + 1;
	while (cur <= right)
	{
		if (arr[cur] < arr[keyi] && ++prev != cur)
		{
			Swap(&arr[prev], &arr[cur]);
		}
		cur++;
	}
	Swap(&arr[keyi], &arr[prev]);
	return prev;
}
//快速排序
void QuickSort(int* arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	//找基准值
	int keyi = _QuickSort(arr, left, right);
	//left keyi right
	//左序列[left,keyi-1]     右序列[keyi+1,right]
	QuickSort(arr, left, keyi - 1);
	QuickSort(arr, keyi + 1, right);
}