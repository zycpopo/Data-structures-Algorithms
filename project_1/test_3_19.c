#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ADMIN_ACCOUNT "admin123"
#define ADMIN_PASSWORD "Admin123"
#define DATA_FILE "library.dat"
#define MAX_USERS 10

typedef int (*compare_func)(const void*, const void*);

typedef struct {
    char id[20];
    char title[100];
    char author[20];
    char publisher[100];
    int year;
    char state[10];
} Book;

typedef struct BookNode {
    Book book;
    struct BookNode* next;
} BookNode;

typedef struct {
    char username[20];
    char password[20];
} User;

typedef enum {
    EXIT,
    ADMIN,
    USER
} LoginType;

// 链表操作函数
BookNode* create_node(Book book);
void insert_node(BookNode** head, Book book);
void delete_node(BookNode** head, char* id);
void free_list(BookNode* head);
BookNode* load_books();
void save_books(BookNode* head);
int count_books(BookNode* head);
void sort_list(BookNode** head, compare_func cmp);

// 其他函数声明
LoginType login();
void admin_menu();
void user_menu();
void register_user();
int save_user(User new_user);
int load_users(User users[]);
void init_system();
void add_book();
void delete_book();
void find_book();
void show_books();
void borrow_book();
void modify_book();
void sort_books();
int compare_title_asc(const Book* a, const Book* b);
int compare_title_desc(const Book* a, const Book* b);
int compare_id_asc(const Book* a, const Book* b);
int compare_id_desc(const Book* a, const Book* b);
int compare_year_asc(const Book* a, const Book* b);
int compare_year_desc(const Book* a, const Book* b);

BookNode* g_head = NULL;

int main() {
    init_system();
    g_head = load_books();
    while (1) {
        LoginType type = login();
        if (type == EXIT) break;
        switch (type) {
        case ADMIN: admin_menu(); break;
        case USER: user_menu(); break;
        default: printf("无效选项!\n");
        }
    }
    free_list(g_head);
    printf("系统已退出\n");
    return 0;
}

/* 链表操作实现 */
BookNode* create_node(Book book)
{
    BookNode* newNode = (BookNode*)malloc(sizeof(BookNode));
    if (newNode)
    {
        newNode->book = book;
        newNode->next = NULL;
    }
    return newNode;
}

void insert_node(BookNode** head, Book book)
{
    BookNode* newNode = create_node(book);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else {
        BookNode* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void delete_node(BookNode** head, char* id)
{
    BookNode* temp = *head, * prev = NULL;
    while (temp != NULL && strcmp(temp->book.id, id) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;

    if (prev == NULL) {
        *head = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
}

void free_list(BookNode* head) {
    BookNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

BookNode* load_books() {
    FILE* fp = fopen(DATA_FILE, "rb");
    if (!fp) return NULL;

    BookNode* head = NULL;
    Book book;
    while (fread(&book, sizeof(Book), 1, fp)) {
        insert_node(&head, book);
    }
    fclose(fp);
    return head;
}

void save_books(BookNode* head) {
    FILE* fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf("文件保存失败！\n");
        return;
    }

    BookNode* temp = head;
    while (temp != NULL) {
        fwrite(&temp->book, sizeof(Book), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

int count_books(BookNode* head) {
    int count = 0;
    BookNode* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* 核心功能实现 */
void add_book() {
    Book new_book;
    printf("\n======                添加书籍                 ======\n");
    printf("\n请输入书籍信息：\n");
    printf("ISBN："); scanf("%19s", new_book.id);
    printf("书名："); scanf("%99s", new_book.title);
    printf("作者："); scanf("%19s", new_book.author);
    printf("出版社："); scanf("%99s", new_book.publisher);
    printf("年份："); scanf("%d", &new_book.year);
    strcpy(new_book.state, "未借出");

    insert_node(&g_head, new_book);
    save_books(g_head);
    printf("书籍添加成功！\n");
}

void delete_book() {
    char target[20];
    printf("\n======                删除书籍                 ======\n");
    printf("请输入要删除的书籍ISBN：");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            printf("找到目标书籍：\n");
            printf("书名：%s\n", temp->book.title);

            printf("确认删除吗？(yes/no): ");
            char choice[10];
            scanf("%9s", choice);
            if (strcmp(choice, "yes") == 0) {
                delete_node(&g_head, target);
                save_books(g_head);
                printf("书籍删除成功！\n");
            }
            else {
                printf("操作已取消\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("未找到ISBN为 %s 的书籍\n", target);
}

void find_book() {
    int choice;
    char keyword[100];
    int found = 0;

    printf("\n======                查找书籍                 ======\n");
    printf("======   1. 按书名搜索 ====== 2. 按作者搜索    ======\n");
    printf("======   3. 按ISBN搜索 ====================    ======\n");
    printf("请选择搜索方式：");
    scanf("%d", &choice);
    printf("关键词：");
    scanf("%99s", keyword);

    BookNode* temp = g_head;
    while (temp != NULL) {
        int match = 0;
        switch (choice) {
        case 1:
            if (strcmp(temp->book.title, keyword)==0) match = 1;
            break;
        case 2:
            if (strcmp(temp->book.author, keyword) == 0) match = 1;
            break;
        case 3:
            if (strcmp(temp->book.id, keyword) == 0) match = 1;
            break;
        }

        if (match) {
            found++;
            printf("[%d] ISBN:%s | 书名:%s | 作者:%s | 状态:%s\n",
                found, temp->book.id, temp->book.title,
                temp->book.author, temp->book.state);
        }
        temp = temp->next;
    }
    printf("找到 %d 条记录\n", found);
}

void show_books() {
    printf("\n======              显示所有书籍               ======\n");
    printf("%-10s %-15s %-15s %-30s %-10s %-10s\n",
        "编号", "书名", "作者", "出版社", "年份", "状态");

    BookNode* temp = g_head;
    while (temp != NULL) {
        printf("%-10s %-15s %-15s %-30s %-10d %-10s\n",
            temp->book.id,
            temp->book.title,
            temp->book.author,
            temp->book.publisher,
            temp->book.year,
            temp->book.state);
        temp = temp->next;
    }
    printf("共 %d 本书\n", count_books(g_head));
}

void borrow_book() {
    char target[20];
    printf("\n======                借阅书籍                 ======\n");
    printf("输入ISBN：");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            if (strcmp(temp->book.state, "未借出") == 0) {
                strcpy(temp->book.state, "已借出");
                save_books(g_head);
                printf("借阅成功！\n");
            }
            else {
                printf("书籍已被借出\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("未找到书籍\n");
}

void modify_book() {
    char target[20];
    printf("\n======                修改书籍                 ======\n");
    printf("输入ISBN：");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            printf("当前信息：\n书名：%s\n作者：%s\n出版社：%s\n年份：%d\n",
                temp->book.title, temp->book.author,
                temp->book.publisher, temp->book.year);

            printf("新ISBN："); scanf("%19s", temp->book.id);
            printf("新书名："); scanf("%99s", temp->book.title);
            printf("新作者："); scanf("%19s", temp->book.author);
            printf("新出版社："); scanf("%99s", temp->book.publisher);
            printf("新年份："); scanf("%d", &temp->book.year);
            printf("新状态："); scanf("%9s", temp->book.state);

            save_books(g_head);
            printf("修改成功！\n");
            return;
        }
        temp = temp->next;
    }
    printf("未找到书籍\n");
}

int compare_id(const Book* a, const Book* b)
{
    return strcmp(a->id, b->id);  // 升序排列
}

void sort_books()
{
    if (g_head == NULL || g_head->next == NULL) return;

    int swapped;
    BookNode* ptr1;
    BookNode* lptr = NULL;

    printf("\n正在根据图书编号排序...\n");
    do {
        swapped = 0;
        ptr1 = g_head;

        while (ptr1->next != lptr)
        {
            if (compare_id(&ptr1->book, &ptr1->next->book) > 0)
            {
                // 交换节点数据
                Book temp = ptr1->book;
                ptr1->book = ptr1->next->book;
                ptr1->next->book = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    save_books(g_head);
    printf("排序完成！\n");
    show_books();
}

int load_users(User users[])
{
    FILE* fp = fopen("users.dat", "rb");
    if (!fp) return 0;

    int count = 0;
    while (fread(&users[count], sizeof(User), 1, fp))
    {
        count++;
        if (count >= MAX_USERS) break;
    }
    fclose(fp);
    return count;
}

int save_user(User new_user) {
    FILE* fp = fopen("users.dat", "ab");
    if (!fp) return 0;

    int success = fwrite(&new_user, sizeof(User), 1, fp);
    fclose(fp);
    return success;
}

void register_user()
{
    User new_user;
    User existing[MAX_USERS];
    int count = load_users(existing);

    while (1) {
        printf("\n用户名（3-19位字母数字）：");
        scanf("%19s", new_user.username);

        int exists = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(new_user.username, existing[i].username) == 0)
            {
                exists = 1;
                break;
            }
        }

        if (exists) {
            printf("用户名已存在！\n");
            continue;
        }

        if (strlen(new_user.username) < 3) {
            printf("至少3个字符！\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("密码（6-19位）：");
        scanf("%19s", new_user.password);
        printf("确认密码：");
        char confirm[20];
        scanf("%19s", confirm);

        if (strcmp(new_user.password, confirm) != 0) {
            printf("密码不一致！\n");
            continue;
        }

        if (strlen(new_user.password) < 6) {
            printf("至少6位！\n");
            continue;
        }
        break;
    }

    if (save_user(new_user)) {
        printf("注册成功！\n");
    }
    else {
        printf("注册失败！\n");
    }
}

LoginType login() {
    int choice;
    User users[MAX_USERS];
    int user_count = load_users(users);

    printf("\n=====           图书信息管理系统           ======\n");
    printf("======   1.管理员登录 ====== 2. 用户登录   ======\n");
    printf("======   3. 用户注册  ====== 0. 退出系统   ======\n");
    scanf("%d", &choice);

    if (choice == 0) return EXIT;

    if (choice == 3) {
        register_user();
        return login();
    }

    char account[20], password[20];
    printf("账号："); scanf("%19s", account);
    printf("密码："); scanf("%19s", password);

    switch (choice) 
    {
    case 1:
        if (strcmp(account, ADMIN_ACCOUNT) == 0 &&
            strcmp(password, ADMIN_PASSWORD) == 0) 
        {
            return ADMIN;
        }
        break;
    case 2:
        for (int i = 0; i < user_count; i++) 
        {
            if (strcmp(account, users[i].username) == 0 &&
                strcmp(password, users[i].password) == 0) 
            {
                return USER;
            }
        }
        break;
    }

    printf("账号或密码错误！\n");
    return login();
}

void admin_menu() 
{
    int choice;
    do {
        printf("\n======             管理员操作              ======\n");
        printf("======   1. 添加书籍 ====== 2. 删除书籍    ======\n");
        printf("======   3. 查找书籍 ====== 4.显示所有书籍 ======\n");
        printf("======   5. 修改书籍 ====== 6. 排序书籍    ======\n");
        printf("======   7. 借阅书籍 ====== 0. 返回上级    ======\n");
        printf("请输入：");
        scanf("%d", &choice);

        switch (choice) {
        case 1: add_book(); break;
        case 2: delete_book(); break;
        case 3: find_book(); break;
        case 4: show_books(); break;
        case 5: modify_book(); break;
        case 6: sort_books(); break;
        case 7: borrow_book(); break;
        }
    } while (choice != 0);
}

void return_book()
{
    char target[20];
    printf("\n======                归还书籍                 ======\n");
    printf("输入ISBN：");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            if (strcmp(temp->book.state, "已借出") == 0) {
                strcpy(temp->book.state, "未借出");
                save_books(g_head);
                printf("归还成功！\n");
            }
            else {
                printf("书籍未被借出\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("未找到书籍\n");
}


void user_menu() {
    int choice;
    do {
        printf("\n======              用户操作               ======\n");
        printf("======   1. 查找书籍 ====== 2. 借阅书籍    ======\n");
        printf("======   3. 归还书籍 ====== 0. 返回上级    ======\n");
        printf("请输入：");
        scanf("%d", &choice);
        switch (choice) 
        {
        case 1: find_book(); break;
        case 2: borrow_book(); break;
        case 3: return_book(); break;
        }
    } while (choice != 0);
}

void init_system() 
{
    FILE* fp = fopen(DATA_FILE, "ab+");
    if (fp) fclose(fp);
    fp = fopen("users.dat", "ab+");
    if (fp) fclose(fp);
}