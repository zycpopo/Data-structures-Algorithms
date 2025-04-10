#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

void Swap(int* x, int* y);
void siftdown(int* arr, int parent, int n);
void siftup(int* arr, int child);

void HPsort(int* arr, int n);