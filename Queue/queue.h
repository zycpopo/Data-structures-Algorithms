#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;

//���нڵ�Ľṹ
typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QueueNode;
//���нṹ
typedef struct Queue
{
	QueueNode* phead;
	QueueNode* ptail;
	int size;
}Queue;

//��ʼ��
void QueueInit(Queue* p);
//���ٶ���
void QueueDestroy(Queue* p);

//�����--��β
void QueuePush(Queue* p, QDataType x);
//������--����
void QueuePop(Queue* p);

//�ж϶����Ƿ�Ϊ��
bool QueueEmpty(Queue* p);
//��ȡ������ЧԪ�صĸ���
int QueueSize(Queue* p);

//��ȡ��������
QDataType QueueFront(Queue* p);
//��ȡ��β����
QDataType QueueBack(Queue* p);