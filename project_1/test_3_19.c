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

// �����������
BookNode* create_node(Book book);
void insert_node(BookNode** head, Book book);
void delete_node(BookNode** head, char* id);
void free_list(BookNode* head);
BookNode* load_books();
void save_books(BookNode* head);
int count_books(BookNode* head);
void sort_list(BookNode** head, compare_func cmp);

// ������������
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
        default: printf("��Чѡ��!\n");
        }
    }
    free_list(g_head);
    printf("ϵͳ���˳�\n");
    return 0;
}

/* �������ʵ�� */
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
        printf("�ļ�����ʧ�ܣ�\n");
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

/* ���Ĺ���ʵ�� */
void add_book() {
    Book new_book;
    printf("\n======                ����鼮                 ======\n");
    printf("\n�������鼮��Ϣ��\n");
    printf("ISBN��"); scanf("%19s", new_book.id);
    printf("������"); scanf("%99s", new_book.title);
    printf("���ߣ�"); scanf("%19s", new_book.author);
    printf("�����磺"); scanf("%99s", new_book.publisher);
    printf("��ݣ�"); scanf("%d", &new_book.year);
    strcpy(new_book.state, "δ���");

    insert_node(&g_head, new_book);
    save_books(g_head);
    printf("�鼮��ӳɹ���\n");
}

void delete_book() {
    char target[20];
    printf("\n======                ɾ���鼮                 ======\n");
    printf("������Ҫɾ�����鼮ISBN��");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            printf("�ҵ�Ŀ���鼮��\n");
            printf("������%s\n", temp->book.title);

            printf("ȷ��ɾ����(yes/no): ");
            char choice[10];
            scanf("%9s", choice);
            if (strcmp(choice, "yes") == 0) {
                delete_node(&g_head, target);
                save_books(g_head);
                printf("�鼮ɾ���ɹ���\n");
            }
            else {
                printf("������ȡ��\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ�ISBNΪ %s ���鼮\n", target);
}

void find_book() {
    int choice;
    char keyword[100];
    int found = 0;

    printf("\n======                �����鼮                 ======\n");
    printf("======   1. ���������� ====== 2. ����������    ======\n");
    printf("======   3. ��ISBN���� ====================    ======\n");
    printf("��ѡ��������ʽ��");
    scanf("%d", &choice);
    printf("�ؼ��ʣ�");
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
            printf("[%d] ISBN:%s | ����:%s | ����:%s | ״̬:%s\n",
                found, temp->book.id, temp->book.title,
                temp->book.author, temp->book.state);
        }
        temp = temp->next;
    }
    printf("�ҵ� %d ����¼\n", found);
}

void show_books() {
    printf("\n======              ��ʾ�����鼮               ======\n");
    printf("%-10s %-15s %-15s %-30s %-10s %-10s\n",
        "���", "����", "����", "������", "���", "״̬");

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
    printf("�� %d ����\n", count_books(g_head));
}

void borrow_book() {
    char target[20];
    printf("\n======                �����鼮                 ======\n");
    printf("����ISBN��");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            if (strcmp(temp->book.state, "δ���") == 0) {
                strcpy(temp->book.state, "�ѽ��");
                save_books(g_head);
                printf("���ĳɹ���\n");
            }
            else {
                printf("�鼮�ѱ����\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ��鼮\n");
}

void modify_book() {
    char target[20];
    printf("\n======                �޸��鼮                 ======\n");
    printf("����ISBN��");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            printf("��ǰ��Ϣ��\n������%s\n���ߣ�%s\n�����磺%s\n��ݣ�%d\n",
                temp->book.title, temp->book.author,
                temp->book.publisher, temp->book.year);

            printf("��ISBN��"); scanf("%19s", temp->book.id);
            printf("��������"); scanf("%99s", temp->book.title);
            printf("�����ߣ�"); scanf("%19s", temp->book.author);
            printf("�³����磺"); scanf("%99s", temp->book.publisher);
            printf("����ݣ�"); scanf("%d", &temp->book.year);
            printf("��״̬��"); scanf("%9s", temp->book.state);

            save_books(g_head);
            printf("�޸ĳɹ���\n");
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ��鼮\n");
}

int compare_id(const Book* a, const Book* b)
{
    return strcmp(a->id, b->id);  // ��������
}

void sort_books()
{
    if (g_head == NULL || g_head->next == NULL) return;

    int swapped;
    BookNode* ptr1;
    BookNode* lptr = NULL;

    printf("\n���ڸ���ͼ��������...\n");
    do {
        swapped = 0;
        ptr1 = g_head;

        while (ptr1->next != lptr)
        {
            if (compare_id(&ptr1->book, &ptr1->next->book) > 0)
            {
                // �����ڵ�����
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
    printf("������ɣ�\n");
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
        printf("\n�û�����3-19λ��ĸ���֣���");
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
            printf("�û����Ѵ��ڣ�\n");
            continue;
        }

        if (strlen(new_user.username) < 3) {
            printf("����3���ַ���\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("���루6-19λ����");
        scanf("%19s", new_user.password);
        printf("ȷ�����룺");
        char confirm[20];
        scanf("%19s", confirm);

        if (strcmp(new_user.password, confirm) != 0) {
            printf("���벻һ�£�\n");
            continue;
        }

        if (strlen(new_user.password) < 6) {
            printf("����6λ��\n");
            continue;
        }
        break;
    }

    if (save_user(new_user)) {
        printf("ע��ɹ���\n");
    }
    else {
        printf("ע��ʧ�ܣ�\n");
    }
}

LoginType login() {
    int choice;
    User users[MAX_USERS];
    int user_count = load_users(users);

    printf("\n=====           ͼ����Ϣ����ϵͳ           ======\n");
    printf("======   1.����Ա��¼ ====== 2. �û���¼   ======\n");
    printf("======   3. �û�ע��  ====== 0. �˳�ϵͳ   ======\n");
    scanf("%d", &choice);

    if (choice == 0) return EXIT;

    if (choice == 3) {
        register_user();
        return login();
    }

    char account[20], password[20];
    printf("�˺ţ�"); scanf("%19s", account);
    printf("���룺"); scanf("%19s", password);

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

    printf("�˺Ż��������\n");
    return login();
}

void admin_menu() 
{
    int choice;
    do {
        printf("\n======             ����Ա����              ======\n");
        printf("======   1. ����鼮 ====== 2. ɾ���鼮    ======\n");
        printf("======   3. �����鼮 ====== 4.��ʾ�����鼮 ======\n");
        printf("======   5. �޸��鼮 ====== 6. �����鼮    ======\n");
        printf("======   7. �����鼮 ====== 0. �����ϼ�    ======\n");
        printf("�����룺");
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
    printf("\n======                �黹�鼮                 ======\n");
    printf("����ISBN��");
    scanf("%19s", target);

    BookNode* temp = g_head;
    while (temp != NULL) {
        if (strcmp(temp->book.id, target) == 0) {
            if (strcmp(temp->book.state, "�ѽ��") == 0) {
                strcpy(temp->book.state, "δ���");
                save_books(g_head);
                printf("�黹�ɹ���\n");
            }
            else {
                printf("�鼮δ�����\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ��鼮\n");
}


void user_menu() {
    int choice;
    do {
        printf("\n======              �û�����               ======\n");
        printf("======   1. �����鼮 ====== 2. �����鼮    ======\n");
        printf("======   3. �黹�鼮 ====== 0. �����ϼ�    ======\n");
        printf("�����룺");
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