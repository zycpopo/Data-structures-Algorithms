#include"sort.h"
#include"stack.h"
//ֱ�Ӳ�������
void InsertSort(int* arr, int n)
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
			else {
				break;
			}
		}
		arr[end + 1] = tmp;
	}
}
//ϣ������
void ShellSort(int* arr, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;//3 2 1 
		//��ÿ�����ֱ�Ӳ�������
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > tmp)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else {
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}
}

void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
void BubbleSort(int* arr, int n)
{
	for (size_t end = n; end > 0; --end)
	{
		int exchange = 0;
		for (size_t i = 1; i < end; ++i)
		{
			if (arr[i - 1] > arr[i])
			{
				Swap(&arr[i - 1], &arr[i]);
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
	}
}
void SelectSort(int* arr, int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int maxi = begin;
		int mini = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (arr[i] < arr[mini])
			{
				mini = i;
			}
			if (arr[i] > arr[maxi])
			{
				maxi = i;
			}
		}
		//mini begin
		//maxi end
		if (maxi == begin)
		{
			maxi = mini;
		}
		Swap(&arr[mini], &arr[begin]);
		Swap(&arr[maxi], &arr[end]);
		begin++;
		end--;
	}
}


//���µ����㷨
void AdjustDown(int* arr, int parent, int n)
{
	int child = parent * 2 + 1;//����
	while (child < n)
	{
		//��ѣ�<
		//С�ѣ�>
		if (child + 1 < n && arr[child] < arr[child + 1])
		{
			child++;
		}
		//���: >
		//С�ѣ�<
		if (arr[child] > arr[parent])
		{
			//����
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}
//������--- �����
//�Ž���--- ��С��
void HeapSort(int* arr, int n)
{
	//���ѡ������µ����㷨����
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(arr, i, n);
	}
	//������
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDown(arr, 0, end);
		end--;
	}
}
//hoare�汾
int _QuickSort1(int* arr, int left, int right)
{
	int keyi = left;
	++left;
	while (left <= right)
	{
		//right�����������ߣ��ұȻ�׼ֵҪС��
		while (left <= right && arr[right] > arr[keyi])
		{
			right--;
		}
		//left�����������ߣ��ұȻ�׼ֵҪ���
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
//lomutoǰ��ָ�뷨
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
//��������
void QuickSort(int* arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	//�һ�׼ֵ
	int keyi = _QuickSort(arr, left, right);
	//left keyi right
	//������[left,keyi-1]     ������[keyi+1,right]
	QuickSort(arr, left, keyi - 1);
	QuickSort(arr, keyi + 1, right);
}
//�ǵݹ�汾�Ŀ������򡪡�ջ
void QuicSortNoR(int* arr, int left, int right)
{
	ST st;
	StackInit(&st);
	StackPush(&st, left);
	StackPush(&st, right);
	while (!StackEmpty(&st))
	{
		//ȡջ������
		int end = StackTop(&st);
		StackPop(&st);
		int begin = StackTop(&st);
		StackPop(&st);

		//[begin,end]�һ�׼ֵ
		int keyi = begin;
		int prev = begin, cur = prev + 1;
		while (cur <= end)
		{
			if (arr[cur] < arr[keyi] && ++prev != cur)
			{
				Swap(&arr[prev], &arr[cur]);
			}
			cur++;
		}
		Swap(&arr[keyi], &arr[prev]);
		keyi = prev;
		//begin keyi end
		//�����У�[begin,keyi-1]  �����У�[keyi+1,end];
		if (keyi + 1 < end)
		{
			StackPush(&st, keyi + 1);
			StackPush(&st, end);
		}
		if (begin < keyi - 1)
		{
			StackPush(&st, begin);
			StackPush(&st, keyi - 1);
		}
	}
	StackDestroy(&st);
}