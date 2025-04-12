#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"

//前序遍历
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

//中序遍历
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

//后序遍历
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