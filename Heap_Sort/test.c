#define _CRT_SECURE_NO_WARNINGS

#include"hp_sort.h"

int main()
{
	int arr[6] = { 10,9,12,14,17,19 };
	int len = sizeof(arr) / sizeof(arr[0]);

	printf("����֮ǰ��");
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	HPsort(arr, len);

	printf("����֮��");
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}