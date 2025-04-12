#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef char BTDataType;
typedef struct BinaryTreeNode {
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

//ǰ�����---������
void preOrder(BTNode* root);
//�������---�����
void inOrder(BTNode* root);
//�������---���Ҹ�
void postOrder(BTNode* root);