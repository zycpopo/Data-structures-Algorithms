#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"
#include"queue.h"

//ǰ�����
void preOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL");
		return;
	}
	printf("%c", root->data);
	preOrder(root->left);
	preOrder(root->right);
}
//�������
void inOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL");
		return;
	}
	inOrder(root->left);
	printf("%c",root->data);
	inOrder(root->right);
}
//�������
void postOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL");
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	printf("%c", root->data);
}

//�������ڵ����
int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1+BinaryTreeSize(root->left) + BinaryTreeSize(root->right);
}
//������Ҷ�ӽڵ����
int BinaryTreeleaSize(BTNode* root)
{
	if (root == NULL);
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return BinaryTreeleaSize(root->left) 
		+BinaryTreeleaSize(root->right);
}
//��������k��ڵ����
int BinaryTreeleveSize(BTNode* root,int k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return BinaryTreeleveSize(root->left, k--) + BinaryTreeleveSize(root->right, k--);
}
//���������/�߶�
int BinaryTreeDepth(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftDep = BinaryTreeDepth(root->left);
	int rightDep = BinaryTreeDepth(root->right);

	return 1 + (leftDep > rightDep ? leftDep : rightDep);
}
//����������ֵΪx�Ľ��
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->data == x)
	{
		return root;
	}
	BTNode* leftFind = BinaryTreeFind(root->left, x);
	if (leftFind)
	{
		return leftFind;
	}

	BTNode* rightFind = BinaryTreeFind(root->right, x);
	if (rightFind)
	{
		return rightFind;
	}
	return NULL;
}
//����������--���Ҹ�
void BinaryTreeDestroy(BTNode** root)
{
	if (*root == NULL) {
		return;
	}
	BinaryTreeDestroy(&((*root)->left));
	BinaryTreeDestroy(&((*root)->right));
	free(*root);
	*root = NULL;
}


//�������
void leverOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		//ȡ��ͷ������ͷ
		BTNode* top = QueueFront(&q);
		QueuePop(&q);
		printf("%c", top->data);
		//���ǿ����Һ��������
		if (top->left)
			QueuePush(&q, top->left);
		if (top->right)
			QueuePush(&q, top->right);
	}

	QueueDestroy(&q);
}