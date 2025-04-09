#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* arr;
	int size;
	int capacity;
}HP;

void Swap(int* x, int* y);
void AdjustUp(HPDataType* arr, int child);
void AdjustDown(HPDataType* arr, int parent, int n);

void HPInit(HP* php);
void HPDestroy(HP* php);
void HPPrint(HP* php);

void HPPush(HP* php,HPDataType x);
void HPPop(HP* php);

HPDataType HPTop(HP* php);

bool HPEmpty(HP* php);