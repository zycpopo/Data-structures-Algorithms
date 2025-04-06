#define _CRT_SECURE_NO_WARNINGS

#include"stack.h"

void StackInit(ST* p)
{
	p->arr = NULL;
	p->top = p->capacity = 0;
}
//销毁栈
void StackDestory(ST* p)
{
	if (p->arr)
		free(p->arr);
	p->arr = NULL;
	p->top = p->capacity = 0;
}

//入栈--栈顶
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

//判断栈是否为空
bool StackEmpty(ST* p)
{
	assert(p);
	return p->top == 0;
}

//出栈--栈顶
void StackPop(ST* p)
{
	assert(!StackEmpty(p));
	--p->top;
}

//取栈顶元素
STDataType StackTop(ST* p)
{
	assert(!StackEmpty(p));
	return p->arr[p->top - 1];
}

//获取栈中有效元素的个数
int StackSize(ST* p)
{
	return p->top;
}