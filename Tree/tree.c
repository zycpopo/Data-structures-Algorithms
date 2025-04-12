#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"

//ǰ�����
void preOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

//�������
void inOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	inOrder(root->left);
	printf("%c ", root->data);
	inOrder(root->right);
}

//�������
void postOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	printf("%c ", root->data);
}