#pragma once
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


//����ջ�Ľṹ
typedef int STDataType;
typedef struct Stack
{
	STDataType* arr;
	int top;     //ָ��ջ����λ��
	int capacity;//ջ������
}ST;

//��ʼ��
void StackInit(ST* ps);
//����
void StackDestroy(ST* ps);

//��ջ---ջ��
void StackPush(ST* ps, STDataType x);
//��ջ����ջ��
void StackPop(ST* ps);
//ȡջ��Ԫ��
STDataType StackTop(ST* ps);

//��ȡջ����ЧԪ�ظ���
int StackSize(ST* ps);
//ջ�Ƿ�Ϊ��
bool StackEmpty(ST* ps);