#define _CRT_SECURE_NO_WARNINGS
#include"Stack.h"

void StackInit(ST* ps)
{
	ps->arr = NULL;
	ps->top = ps->capacity = 0;
}
//����
void StackDestroy(ST* ps)
{
	if (ps->arr)
		free(ps->arr);
	ps->arr = NULL;
	ps->top = ps->capacity = 0;
}
//��ջ---ջ��
void StackPush(ST* ps, STDataType x)
{
	assert(ps);
	if (ps->top == ps->capacity)
	{
		//����
		int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		STDataType* tmp = (STDataType*)realloc(ps->arr, newCapacity * sizeof(STDataType));
		if (tmp == NULL)
		{
			perror("realloc fail!");
			exit(1);
		}
		ps->arr = tmp;
		ps->capacity = newCapacity;
	}
	ps->arr[ps->top++] = x;
}
//ջ�Ƿ�Ϊ��
bool StackEmpty(ST* ps)
{
	assert(ps);
	return ps->top == 0;
}
//��ջ����ջ��
void StackPop(ST* ps)
{
	assert(!StackEmpty(ps));
	--ps->top;
}
//ȡջ��Ԫ��
STDataType StackTop(ST* ps)
{
	assert(!StackEmpty(ps));
	return ps->arr[ps->top - 1];
}
//��ȡջ����ЧԪ�ظ���
int StackSize(ST* ps)
{
	return ps->top;
}