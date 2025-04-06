#define _CRT_SECURE_NO_WARNINGS

#include"stack.h"

void StackInit(ST* p)
{
	p->arr = NULL;
	p->top = p->capacity = 0;
}
//����ջ
void StackDestory(ST* p)
{
	if (p->arr)
		free(p->arr);
	p->arr = NULL;
	p->top = p->capacity = 0;
}

//��ջ--ջ��
void StackPush(ST* p, STDataType X)
{
	assert(p);
	if (p->top == p->capacity)
	{
		int newCapacity = p->capacity == 0 ? 4 : 2 * p->capacity;
		STDataType* tmp = (STDataType*)realloc(p->arr, newCapacity * sizeof(STDataType));
		if (tmp == NULL)
		{
			perror("realloc fail");
			exit(1);
		}
		p->arr = tmp;
		p->capacity = newCapacity;
	}
	p->arr[p->top++] = X;
}

//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(ST* p)
{
	assert(p);
	return p->top == 0;
}

//��ջ--ջ��
void StackPop(ST* p)
{
	assert(!StackEmpty(p));
	--p->top;
}

//ȡջ��Ԫ��
STDataType StackTop(ST* p)
{
	assert(!StackEmpty(p));
	return p->arr[p->top - 1];
}

//��ȡջ����ЧԪ�صĸ���
int StackSize(ST* p)
{
	return p->top;
}