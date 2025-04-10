#define _CRT_SECURE_NO_WARNINGS

//交换
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
//向下调整
void siftdown(int* arr, int parent, int n)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child] > arr[child + 1])
		{
			child++;
		}
		if (arr[child] < arr[parent])
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

//向上调整
void siftup(int* arr, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else { break; 
		}
	}
}

void HPsort(int* arr, int n)
{
	//建堆--向下调整算法
	for (int i = (n-1-1)/2; i >= 0; i--)
	{
		siftdown(arr, i, n);
	}
    //排序
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		siftdown(arr, 0, end);
		end--;
	}
}