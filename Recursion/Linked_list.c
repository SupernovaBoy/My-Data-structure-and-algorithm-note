#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Linked_Node;

Linked_Node* creatnode(int x);//新建一个节点
Linked_Node* find_position(Linked_Node* head,int k);//找到链表中第k位置的地址
void list_insert(Linked_Node* head, int k, int x);//在链表中第K位置插入值为X的节点
void init(Linked_Node** head);//初始化链表
void print_list(Linked_Node* head);//打印链表


int main(){
    Linked_Node* a;
    init(&a);
    list_insert(a, 1, 1);
    list_insert(a, 2, 2);
    list_insert(a, 3, 3);
    list_insert(a, 4, 4);
    list_insert(a, 5, 5);
    list_insert(a, 6, 6);
    list_insert(a, 7, 7);
    print_list(a);
}


// （5）将单链表按倒序输出。要求：程序中不得出现循环语句。
void print_list(Linked_Node* head){
    if(head == NULL)
        return;
    print_list(head->next);
    printf("%d-->", head->data);
}


// 1、创建一个带头结点的单链表；//
void init(Linked_Node** head){
    (*head) = (Linked_Node*)malloc(sizeof(Linked_Node));
    (*head)->data = NULL;
    (*head)->next = NULL;
}

Linked_Node* creatnode(int x){
    Linked_Node* t;
    t = (Linked_Node*)malloc(sizeof(Linked_Node));
    t->data = x;
    t->next = NULL;
    return t;
}

void list_insert(Linked_Node* head, int k, int x){
    if( k < 1 ) return ;
    else if(k == 1 ){
        Linked_Node* t;
        t = creatnode(x);
        t->next = head->next;
        head->next = t;
        return ;
    }
    else{
        Linked_Node* pre;
        pre = find_position(head, k-1);
        if(pre){
            Linked_Node* t;
            t = creatnode(x);
            t->next = pre->next;
            pre->next = t;
            return ;
        }
    }
}

//找到第K个节点
Linked_Node* find_position(Linked_Node* head,int k){
    int count = 1;
    Linked_Node* t;
    t = head->next;
    while(t && count < k){
        t = t->next;
        count++;
    }
    return t;
}
