#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//����ջ�Ľṹ
typedef int STDataType;
typedef struct Stack {
	STDataType* arr;
	int top;
	int capacity;
}ST;

//��ʼ��ջ
void StackInit(ST* p);
//����ջ
void StackDestory(ST* p);

//��ջ
void StackPush(ST* p,STDataType X);
//��ջ
void StackPop(ST* p);
//ȡջ��Ԫ��
STDataType Stacktop(ST* p);

//��ȡջ����ЧԪ�ظ���
int StackSize(ST* p);
//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(ST* p);
