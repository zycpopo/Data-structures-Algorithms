#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"

BTNode* buynode(char x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->data = x;
	node->left = node->right = NULL;

	return node;
}

BTNode* creatBT() {
	BTNode* nodeA = buynode('A');
	BTNode* nodeB = buynode('B');
	BTNode* nodeC = buynode('C');
	BTNode* nodeD = buynode('D');
	BTNode* nodeE = buynode('E');
	BTNode* nodeF = buynode('F');

	nodeA->left = nodeB;
	nodeA->right = nodeC;
	nodeB->left = nodeD;
	nodeB->right = nodeE;
	nodeC->left = nodeF;

	return nodeA;
}

int main()
{
	BTNode* root = creatBT();

	preOrder(root);
	printf("\n");
	inOrder(root);
	printf("\n");
	postOrder(root);
	printf("\n");
	return 0;
}