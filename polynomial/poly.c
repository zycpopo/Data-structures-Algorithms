#include <stdio.h>
#include <stdlib.h>

// 定义多项式节点结构
typedef struct PolyNode {
    int coef;        // 系数
    int exp;         // 指数
    struct PolyNode *next; // 指向下一个节点的指针
} PolyNode, *Polynomial;

// 创建多项式节点
PolyNode *createPolyNode(int coef, int exp) {
    PolyNode *node = (PolyNode *)malloc(sizeof(PolyNode));
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    return node;
}

// 初始化多项式
void initPolynomial(Polynomial *poly) {
    *poly = (PolyNode *)malloc(sizeof(PolyNode)); // 头节点
    (*poly)->next = NULL;
}

// 插入多项式节点（按指数降序）
void insertPolyNode(Polynomial poly, int coef, int exp) {
    if (coef == 0) return; // 系数为 0，不插入

    PolyNode *node = createPolyNode(coef, exp);
    PolyNode *p = poly, *q = poly->next;

    // 找到插入位置
    while (q != NULL && q->exp > exp) {
        p = q;
        q = q->next;
    }

    // 如果指数相同，合并同类项
    if (q != NULL && q->exp == exp) {
        q->coef += coef;
        if (q->coef == 0) { // 合并后系数为 0，删除节点
            p->next = q->next;
            free(q);
        }
        free(node);
    } else { // 插入新节点
        p->next = node;
        node->next = q;
    }
}

// 多项式相加
void addPolynomial(Polynomial poly1, Polynomial poly2, Polynomial result) {
    PolyNode *p = poly1->next, *q = poly2->next;

    while (p != NULL && q != NULL) {
        if (p->exp > q->exp) {
            insertPolyNode(result, p->coef, p->exp);
            p = p->next;
        } else if (p->exp < q->exp) {
            insertPolyNode(result, q->coef, q->exp);
            q = q->next;
        } else {
            int coef = p->coef + q->coef;
            if (coef != 0) {
                insertPolyNode(result, coef, p->exp);
            }
            p = p->next;
            q = q->next;
        }
    }

    // 处理剩余节点
    while (p != NULL) {
        insertPolyNode(result, p->coef, p->exp);
        p = p->next;
    }
    while (q != NULL) {
        insertPolyNode(result, q->coef, q->exp);
        q = q->next;
    }
}

// 多项式相减
void subPolynomial(Polynomial poly1, Polynomial poly2, Polynomial result) {
    PolyNode *q = poly2->next;

    // 复制 poly1 到 result
    PolyNode *p = poly1->next;
    while (p != NULL) {
        insertPolyNode(result, p->coef, p->exp);
        p = p->next;
    }

    // 减去 poly2（即加上 -poly2）
    while (q != NULL) {
        insertPolyNode(result, -q->coef, q->exp);
        q = q->next;
    }
}

// 多项式求导
void derivPolynomial(Polynomial poly, Polynomial result) {
    PolyNode *p = poly->next;

    while (p != NULL) {
        if (p->exp > 0) { // 指数大于 0 才有导数
            insertPolyNode(result, p->coef * p->exp, p->exp - 1);
        }
        p = p->next;
    }
}

// 打印多项式
void printPolynomial(Polynomial poly) {
    PolyNode *p = poly->next;
    int first = 1; // 标记是否是第一个项

    while (p != NULL) {
        if (first) {
            if (p->coef < 0) {
                printf("-");
            }
            first = 0;
        } else {
            if (p->coef > 0) {
                printf("+");
            }
        }

        if (abs(p->coef) != 1 || p->exp == 0) {
            printf("%d", abs(p->coef));
        }

        if (p->exp > 0) {
            printf("x");
            if (p->exp > 1) {
                printf("^%d", p->exp);
            }
        }

        p = p->next;
    }

    if (first) { // 多项式为 0
        printf("0");
    }
    printf("\n");
}

// 释放多项式内存
void freePolynomial(Polynomial poly) {
    PolyNode *p = poly, *q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
}

int main() {
    Polynomial poly1, poly2, addResult, subResult, derivResult1, derivResult2;

    // 初始化多项式
    initPolynomial(&poly1);
    initPolynomial(&poly2);
    initPolynomial(&addResult);
    initPolynomial(&subResult);
    initPolynomial(&derivResult1);
    initPolynomial(&derivResult2);

    // 构造多项式 poly1: 3x^5 + 2x^3 - 5x^2 + 1
    insertPolyNode(poly1, 3, 5);
    insertPolyNode(poly1, 2, 3);
    insertPolyNode(poly1, -5, 2);
    insertPolyNode(poly1, 1, 0);

    // 构造多项式 poly2: 2x^4 - 3x^3 + 4x^2 + x - 7
    insertPolyNode(poly2, 2, 4);
    insertPolyNode(poly2, -3, 3);
    insertPolyNode(poly2, 4, 2);
    insertPolyNode(poly2, 1, 1);
    insertPolyNode(poly2, -7, 0);

    // 多项式相加
    addPolynomial(poly1, poly2, addResult);
    printf("Poly1 + Poly2 = ");
    printPolynomial(addResult);

    // 多项式相减
    subPolynomial(poly1, poly2, subResult);
    printf("Poly1 - Poly2 = ");
    printPolynomial(subResult);

    // 多项式求导
    derivPolynomial(poly1, derivResult1);
    printf("Derivative of Poly1 = ");
    printPolynomial(derivResult1);

    derivPolynomial(poly2, derivResult2);
    printf("Derivative of Poly2 = ");
    printPolynomial(derivResult2);

    // 释放内存
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(addResult);
    freePolynomial(subResult);
    freePolynomial(derivResult1);
    freePolynomial(derivResult2);

    return 0;
}