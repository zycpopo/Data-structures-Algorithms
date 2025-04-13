#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include"tree.h"

void QueueInit(Queue* p)
{
	assert(p);
	p->phead = p->ptail = NULL;
	p->size = 0;
}

void QueueDestroy(Queue* p)
{
	assert(p);
	QueueNode* pcur = p->phead;
	while (pcur)
	{
		QueueNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	p->phead = p->ptail = NULL;
	p->size = 0;
}

void QueuePush(Queue* p, QDataType x)
{
	assert(p);
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;
	//����Ϊ��
	if (p->phead == NULL)
	{
		p->phead = p->ptail = newnode;
	}
	//���зǿ�
	else {
		p->ptail->next = newnode;
		p->ptail = p->ptail->next;
	}
	p->size++;
}

void QueuePop(Queue* p)
{
	assert(!QueueEmpty(p));
	//ֻ��һ���ڵ㣬phead��ptail���ÿ�
	if (p->phead == p->ptail)
	{
		free(p->phead);
		p->phead = p->ptail = NULL;
	}
	else
	{
		QueueNode* next = p->phead->next;
		free(p->phead);
		p->phead = next;
	}
	p->size--;
}

bool QueueEmpty(Queue* p)
{
	assert(p);
	return p->phead == NULL;
}

QDataType QueueFront(Queue* p)
{
	assert(!QueueEmpty(p));
	return p->phead->data;
}

QDataType QueueBack(Queue* p)
{
	assert(!QueueEmpty(p));
	return p->ptail->data;
}

int QueueSize(Queue* p)
{
	assert(p);
	//��������--�����ڲ���Ƶ�����ö�����Ч���ݸ����ĳ���
	QueueNode* pcur = p->phead;
	int size = 0;
	while (pcur)
	{
		size++;
		pcur = pcur->next;
	}
	return size;
	//�ڶ��֣�������Ƶ�����ö�����ЧԪ�����ݸ����ĳ���
	//return p->size;
}