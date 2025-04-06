#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//定义栈的结构
typedef int STDataType;
typedef struct Stack {
	STDataType* arr;
	int top;
	int capacity;
}ST;

//初始化栈
void StackInit(ST* p);
//销毁栈
void StackDestory(ST* p);

//入栈
void StackPush(ST* p,STDataType X);
//出栈
void StackPop(ST* p);
//取栈顶元素
STDataType Stacktop(ST* p);

//获取栈中有效元素个数
int StackSize(ST* p);
//判断栈是否为空
bool StackEmpty(ST* p);
