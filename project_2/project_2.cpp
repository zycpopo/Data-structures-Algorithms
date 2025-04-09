#include <iostream>
#define CONTACTS "contacts.dat"

typedef struct {
    char name[20];
    char phone[20];
    char email[30];
    char group[10];
}Contact;

typedef struct ContactNode {
    Contact contact;
    struct Contact* next;
}ContactNode;

void find_contact();
void add_contact();
void show_contact();
void delete_contact();
void sort_contact();

void free_list();

ContactNode* c_head = NULL;

int main()
{
    int system();
    int flag = 0;
    do {
        printf("通讯录\n");
        printf("1.查找联系人2.添加联系人\n");
        printf("3.删除联系人4.显示练习人\n");
        printf("5.排序联系人0.退出系统\n");
        scanf("%d", &flag);
    
    switch (flag) {

    case 0:printf("系统已退出\n"); break;
    case 1:find_contact(); break;
    case 2:add_contact(); break;
    case 3:delete_contact(); break;
    case 4:show_contact(); break;
    case 5:sort_contact(); break;

    default:printf("无效选项！\n");
    }
    } while (flag != 0);
    free_list(c_head);
    printf("系统已退出！\n");
    return 0;
}

int system() {
    FILE* fp = fopen(CONTACTS, "ab+");
    if (fp) fclose(fp);
}

ContactNode* creat_node(Contact contact)
{
    ContactNode* newNode=(ContactNode*)new(sizeof(ContactNode))
}