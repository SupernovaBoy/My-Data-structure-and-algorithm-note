#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    int data;
    struct list *prev;
    struct list *next;
}DLinked;
//初始化双链表
void init(DLinked **head);
//释放双链表
void delete_list(DLinked **head);
//从尾部插入
void insert_end(DLinked *head, int data);
//从头部插入
void insert_begin(DLinked *head, int data);
//输出双链表
void print_list(DLinked *head);
//输出双链表中间值
void print_center(DLinked *head);
//获得双链表的长度
void length(DLinked *head);

int main(){
    DLinked *l;
    init(&l);
    insert_end(l, 1);
    insert_end(l, 2);
    insert_end(l, 3);
    insert_end(l, 4);
    insert_end(l, 5);
    insert_end(l, 6);
    insert_end(l, 7);
    insert_end(l, 8);
    insert_end(l, 9);
    insert_end(l, 10);
    print_list(l);
    print_center(l);
    length(l);
    delete_list(&l);
    return 0;
}

void init(DLinked **head){
    *head = (DLinked* )(malloc(sizeof(DLinked)));
    (*head)->prev = NULL;
    (*head)->next = NULL;
}

void delete_list(DLinked **head){
    DLinked *temp2, *temp1;
    temp1 = *head;
    while(temp1){
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
    *head = NULL;
}

void insert_end(DLinked *head, int data){
    DLinked *current = head;
    DLinked *newnode = (DLinked *)(malloc(sizeof(DLinked)));
    if(!newnode){
        printf("Memory ERROR!\n");
        return;
    }
    newnode->data = data;
    newnode->next = NULL;
    while(current->next != NULL)
        current = current->next;
    newnode->prev = current;
    current->next = newnode;
}

void insert_begin(DLinked *head, int data){
    DLinked *newnode = (DLinked *)(malloc(sizeof(DLinked)));
    if(!newnode){
        printf("Memory ERROR!\n");
        return;
    }
    newnode->data = data;
    newnode->prev = head;
    if(head->next == NULL){
        newnode->next = NULL;
        head->next = newnode;
        return ;
    }
    newnode->next = head->next;
    head->next->prev = newnode;
    head->next = newnode;
}

void print_list(DLinked *head){
    DLinked *current = head->next;
    for(; current; current = current->next)
        printf("%d-->",current->data);
    if(!current)
        printf("\n");
}

void print_center(DLinked *head){
    DLinked *fast = head->next;
    DLinked *slow = head->next;
    int cnt1 = 1;
    int cnt2 = 1;
    while(fast){
        fast = fast->next;
        slow = slow->next;
        cnt1++;
        if(fast){
            fast = fast->next;
            cnt2++;
        }
    }
    printf("%d\n",slow->prev->data);
    if(cnt1 == cnt2)//说明为偶数个
        printf("%d\n",slow->data);
}

void length(DLinked *head){
    DLinked *current = head->next;
    int count = 0;
    for(; current; current = current->next)
        count++;
    printf("The length of DLinked is %d.\n", count);
}
 