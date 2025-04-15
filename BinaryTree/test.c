#define _CRT_SECURE_NO_WARNINGS
#include"tree.h"
#include"queue.h"

BTNode* buyNode(char x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->data = x;
	node->left = node->right = NULL;

	return node;
}

BTNode* createBinaryTree()
{
	BTNode* nodeA = buyNode('A');
	BTNode* nodeB = buyNode('B');
	BTNode* nodeC = buyNode('C');
	BTNode* nodeD = buyNode('D');
	BTNode* nodeE = buyNode('E');
	BTNode* nodeF = buyNode('F');

	nodeA->left = nodeB;
	nodeA->right = nodeC;
	nodeB->left = nodeD;
	nodeC->left = nodeE;
	nodeC->right = nodeF;

	return nodeA;
}

void test01()
{
	BTNode* root = createBinaryTree();
	//preOrder(root);
	//inOrder(root);
	//postOrder(root);
	//printf("size:%d\n", BinaryTreeSize(root));
	//printf("size:%d\n", BinaryTreeSize(root));
	printf("size:%d\n", BinaryTreeSize(root));
	printf("Leaf size:%d\n", BinaryTreeleaSize(root));
	printf("K size:%d\n", BinaryTreeleveSize(root, 1));
	printf("depth:%d\n", BinaryTreeDepth(root));
	if (BinaryTreeFind(root, 'G'))
	{
		printf("找到了\n");
	}
	else
	{
		printf("未找到\n");
	}

	printf("层序遍历：");
	leverOrder(root);


	BinaryTreeDestroy(&root);
}
int main()
{
	test01();
	return 0;
}