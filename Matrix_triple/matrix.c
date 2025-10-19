#include <stdio.h>
#include <locale.h>
typedef struct 
{
    int value;
    int row;
    int col;
}Triple;

typedef struct
{
    Triple data[101];
    int cols;
    int rows;
    int nums;
}Matrix;

int addmatrix(Matrix m, Matrix n, Matrix *r)
{
    if(m.cols != n.cols || m.rows != n.rows)
    {
        printf("两个矩阵维度不匹配，无法相加\n");
        return 0;
    }
    
    r->rows = m.rows;
    r->cols = m.cols;
    r->nums = 0;
    
    int i = 1, j = 1, k = 1;
    
    while(i <= m.nums && j <= n.nums)
    {
        if(m.data[i].row < n.data[j].row || 
           (m.data[i].row == n.data[j].row && m.data[i].col < n.data[j].col))
        {
            r->data[k] = m.data[i];
            i++;
            k++;
            r->nums++;
        }
        else if(n.data[j].row < m.data[i].row || 
                (m.data[i].row == n.data[j].row && n.data[j].col < m.data[i].col))
        {
            r->data[k] = n.data[j];
            j++;
            k++;
            r->nums++;
        }
        else
        {
            int sum = m.data[i].value + n.data[j].value;
            if(sum != 0)
            {
                r->data[k].row = m.data[i].row;
                r->data[k].col = m.data[i].col;
                r->data[k].value = sum;
                k++;
                r->nums++;
            }
            i++;
            j++;
        }
    }
    
    while(i <= m.nums)
    {
        r->data[k] = m.data[i];
        i++;
        k++;
        r->nums++;
    }
    
    while(j <= n.nums)
    {
        r->data[k] = n.data[j];
        j++;
        k++;
        r->nums++;
    }
    
    return 1;
}

int submatrix(Matrix m, Matrix n, Matrix *r)
{
    Matrix temp = n;
    for(int i = 1; i <= temp.nums; i++)
    {
        temp.data[i].value = -temp.data[i].value;
    }
    return addmatrix(m, temp, r);
}

void input(Matrix *m)
{
    printf("请输入矩阵的行数、列数、非零元素数：");
    scanf("%d%d%d", &m->rows, &m->cols, &m->nums);
    
    m->data[0].row = m->rows;
    m->data[0].col = m->cols;
    m->data[0].value = m->nums;
    
    for(int i = 1; i <= m->nums; i++)
    {
        printf("请输入第%d个非零元素的行、列、值:\n", i);
        scanf("%d%d%d", &m->data[i].row, &m->data[i].col, &m->data[i].value);
    }
}

void output(Matrix m)
{
    int k = 1;
    printf("矩阵内容：\n");
    for(int i = 1; i <= m.rows; i++)
    {
        for(int j = 1; j <= m.cols; j++)
        {
            if(k <= m.nums && m.data[k].row == i && m.data[k].col == j)
            {
                printf("%d ", m.data[k].value);
                k++;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main()
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    Matrix x, y, o, s;
    
    input(&x);
    input(&y);
    
    if(addmatrix(x, y, &o))
    {
        printf("矩阵相加结果：\n");
        output(o);
    }
    
    if(submatrix(x, y, &s))
    {
        printf("矩阵相减结果：\n");
        output(s);
    }
    
    return 0;
}
