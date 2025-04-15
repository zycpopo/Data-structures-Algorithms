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

//ǰ���������������
void preOrder(BTNode* root);
//�������
void inOrder(BTNode* root);
//�������
void postOrder(BTNode* root);


//�������ڵ����
int BinaryTreeSize(BTNode* root);
//������Ҷ�ӽڵ����
int BinaryTreeleaSize(BTNode* root);
//��������k��ڵ����
int BinaryTreeleveSize(BTNode* root, int k);
//���������/�߶�
int BinaryTreeDepth(BTNode* root);
//����������ֵΪx�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//����������
void BinaryTreeDestroy(BTNode** root);
