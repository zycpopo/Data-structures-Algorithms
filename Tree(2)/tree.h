#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char BTDataType;
typedef struct BinaryTreeNode 
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

//前序遍历——根左右
void preOrder(BTNode* root);
//中序遍历
void inOrder(BTNode* root);
//后序遍历
void postOrder(BTNode* root);


//二叉树节点个数
int BinaryTreeSize(BTNode* root);
//二叉树叶子节点个数
int BinaryTreeleaSize(BTNode* root);
//二叉树第k层节点个数
int BinaryTreeleveSize(BTNode* root, int k);
//二叉树深度/高度
int BinaryTreeDepth(BTNode* root);
//二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//二叉树销毁
void BinaryTreeDestroy(BTNode** root);
