#define _CRT_SECURE_NO_WARNINGS
#include"work.h"

void test01()
{
	int arr[10] = { 2,3,6,5,8,7,4,1,9,10 };
	//insertsort(arr, 10);
	//shellsort(arr, 10);
	//selectsort(arr, 10);
	//heapsort(arr, 10);
	//bubblesort(arr, 10);
	//QuickSort(arr, 0, 10 - 1);
	
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	test01();
}