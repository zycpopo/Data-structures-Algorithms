#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;

//队列节点的结构
typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QueueNode;
//队列结构
typedef struct Queue
{
	QueueNode* phead;
	QueueNode* ptail;
	int size;
}Queue;

//初始化
void QueueInit(Queue* p);
//销毁队列
void QueueDestroy(Queue* p);

//入队列--队尾
void QueuePush(Queue* p, QDataType x);
//出队列--队首
void QueuePop(Queue* p);

//判断队列是否为空
bool QueueEmpty(Queue* p);
//获取队列有效元素的个数
int QueueSize(Queue* p);

//获取队首数据
QDataType QueueFront(Queue* p);
//获取队尾数据
QDataType QueueBack(Queue* p);