#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;

typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
} BiTNode, * BiTree;

void CreateBiTree(BiTree& T) {
    TElemType ch;
    cin >> ch;
    if (ch == '#') T = NULL;
    else {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void PrintTree(BiTree T, int level) {
    if (T == NULL) return;
    PrintTree(T->rchild, level + 1);
    for (int i = 0; i < level; i++) cout << "    ";
    cout << T->data << endl;
    PrintTree(T->lchild, level + 1);
}

void PreOrderNonRecursive(BiTree T) {
    if (T == NULL) return;
    stack<BiTree> s;
    s.push(T);
    cout << "先序遍历结果：";
    while (!s.empty()) {
        BiTree p = s.top();
        s.pop();
        cout << p->data << " ";
        if (p->rchild != NULL)
            s.push(p->rchild);
        if (p->lchild != NULL)
            s.push(p->lchild);
    }
    cout << endl;
}

void InOrderNonRecursive(BiTree T) {
    if (T == NULL) return;
    stack<BiTree> s;
    BiTree p = T;
    cout << "中序遍历结果：";
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            s.push(p);
            p = p->lchild;
        }
        if (!s.empty()) {
            p = s.top();
            s.pop();
            cout << p->data << " ";
            p = p->rchild;
        }
    }
    cout << endl;
}

void PostOrderRecursive(BiTree T) {
    if (T == NULL) return;
    PostOrderRecursive(T->lchild);
    PostOrderRecursive(T->rchild);
    cout << T->data << " ";
}

int CountLeaf(BiTree T) {
    if (T == NULL) return 0;
    if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

int GetHeight(BiTree T) {
    if (T == NULL) return 0;
    int leftH = GetHeight(T->lchild);
    int rightH = GetHeight(T->rchild);
    return (leftH > rightH ? leftH : rightH) + 1;
}

int CountLeafAtLevel(BiTree T, int k) {
    if (T == NULL || k < 1) return 0;
    if (k == 1 && T->lchild == NULL && T->rchild == NULL)
        return 1;
    return CountLeafAtLevel(T->lchild, k - 1) + CountLeafAtLevel(T->rchild, k - 1);
}

int main() {
    BiTree T = NULL;
    cout << "请输入二叉树的扩展先序序列（空节点用'#'表示，如ABC##DE###）：" << endl;
    CreateBiTree(T);

    cout << "\n二叉树树状结构（从右到左层级显示）：" << endl;
    PrintTree(T, 0);

    PreOrderNonRecursive(T);
    InOrderNonRecursive(T);
    cout << "后序遍历结果：";
    PostOrderRecursive(T);
    cout << endl;

    int leafNum = CountLeaf(T);
    cout << "叶子节点个数：" << leafNum << endl;

    int height = GetHeight(T);
    cout << "二叉树高度：" << height << endl;

    int targetLevel;
    cout << "请输入要统计叶子节点的指定层（≥1）：";
    cin >> targetLevel;
    int leafAtLevel = CountLeafAtLevel(T, targetLevel);
    cout << "第" << targetLevel << "层的叶子节点个数：" << leafAtLevel << endl;

    return 0;
}