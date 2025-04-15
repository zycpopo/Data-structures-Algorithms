#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"
#include"queue.h"

//前序遍历
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
//中序遍历
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
//后序遍历
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

//二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1+BinaryTreeSize(root->left) + BinaryTreeSize(root->right);
}
//二叉树叶子节点个数
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
//二叉树第k层节点个数
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
//二叉树深度/高度
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
//二叉树查找值为x的结点
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
//二叉树销毁--左右根
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


//层序遍历
void leverOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		//取队头，出队头
		BTNode* top = QueueFront(&q);
		QueuePop(&q);
		printf("%c", top->data);
		//将非空左右孩子入队列
		if (top->left)
			QueuePush(&q, top->left);
		if (top->right)
			QueuePush(&q, top->right);
	}

	QueueDestroy(&q);
}