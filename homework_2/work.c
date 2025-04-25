#define _CRT_SECURE_NO_WARNINGS
#include"work.h"

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi)
{
    if (*pi == '#' || pi > n)
    {
        (*pi)++;
        return NULL;
    }

    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->data = a[*pi];
    newNode->left = NULL;
    newNode->right = NULL;
    (*pi)++;

    newNode->left = BinaryTreeCreate(a, n, pi);
    newNode->right = BinaryTreeCreate(a, n, pi);
     
    return newNode;
}
// 二叉树销毁
void BinaryTreeDestory(BTNode** root)
{
    if (*root == NULL)
    {
        return;
    }

    BinaryTreeDestory(&((*root)->left));
    BinaryTreeDestory(&((*root)->right));
    //释放节点内存
    free(*root);
    *root = NULL;
}
// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1+BinaryTreeSize(root->left)+
    BinaryTreeSize(root->right);
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    return BinaryTreeLeafSize(root->left, root->right);
}
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
    if (root == NULL) {
        return 0;
    }
    if (k == 1)
    {
        return 1;
    }

    return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}

//⼆叉树的深度/⾼度
int BinaryTreeDepth(BTNode* root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftdeep = BinaryTreeDepth(root->left);
    int rightdeep = BinartTreeDepth(root->right);

    return 1 + (leftdeep > rightdeep ? leftdeep : rightdeep);
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
    if (root == NULL)
    {
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
//前序遍历——根左右
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
//中序遍历--左根右
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
//后序遍历--左右根
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
// 层序遍历
//void BinaryTreeLevelOrder(BTNode* root)
//{
//    Queue q;
//    QueueInit(&q);
//    QueuePush(&q, root);
//    while (!QueueEmpty(&q))
//    {
//        //取队头，出队头
//        BTNode* top = QueueFront(&q);
//        QueuePop(&q);
//        printf("%c ", top->data);
//        //将队头非空左右孩子入队列
//        if (top->left)
//            QueuePush(&q, top->left);
//        if (top->right)
//            QueuePush(&q, top->right);
//    }
//    QueueDestroy(&q);
//}
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root);