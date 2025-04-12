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

//前序遍历---根左右
void preOrder(BTNode* root);
//中序遍历---左根右
void inOrder(BTNode* root);
//后序遍历---左右根
void postOrder(BTNode* root);