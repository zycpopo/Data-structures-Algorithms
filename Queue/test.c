#define _CRT_SECURE_NO_WARNINGS
#include"Queue.h"

void test01()
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, 0);
	QueuePush(&q, 2);
	QueuePush(&q, 3); 
	QueuePush(&q, 10);
	//QueuePop(&q);
	int front = QueueFront(&q);
	int rear = QueueBack(&q);
	printf("front:%d\n", front);
	printf("rear:%d\n", rear);
	printf("size:%d", QueueSize(&q));
	QueueDestroy(&q);
}

int main()
{
	test01();
	return 0;
}