#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Linked_Node;

Linked_Node* creatnode(int x);//新建一个节点
Linked_Node* find_position(Linked_Node* head,int k);//找到链表中第k位置的地址
int getlength(Linked_Node* head);//获得链表长度
void init(Linked_Node** head);//初始化链表
void print_list(Linked_Node* head);//打印链表
void list_insert(Linked_Node* head, int k, int x);//在链表中第K位置插入值为X的节点
void list_delete(Linked_Node* head, int i);//在链表中删除第i个节点节点
void delete_number(Linked_Node* head, int x);// 5、删除单链表中值为x的所有元素
void merge_list_up_print(Linked_Node* ha, Linked_Node* hb);// 6、给定两个升序的单链表ha、hb，将其合并为【升序的】hc
void merge_list_down_print(Linked_Node* ha, Linked_Node* hb);// 6、给定两个升序的单链表ha、hb，将其合并为【降序的】hc
void DeleteLinkedList(Linked_Node** head);//清理内存

int main()
{
    Linked_Node* a;
    init(&a);
    Linked_Node* b;
    init(&b);
    list_insert(a, 1, 1);
    list_insert(a, 2, 2);
    list_insert(a, 3, 3);
    list_insert(a, 4, 4);
    list_insert(a, 5, 5);
    list_insert(a, 6, 6);
    list_insert(a, 7, 7);
    list_insert(b, 1, 1);
    list_insert(b, 2, 2);
    list_insert(b, 3, 3);
    list_insert(b, 4, 4);
    list_insert(b, 5, 5);
    list_insert(b, 6, 6);
    list_insert(b, 7, 7);
    merge_list_down_print(a, b);
    DeleteLinkedList(&a);
    DeleteLinkedList(&b);
}


Linked_Node* creatnode(int x){
    Linked_Node* t;
    t = (Linked_Node*)malloc(sizeof(Linked_Node));
    t->data = x;
    t->next = NULL;
    return t;
}

// 1、创建一个带头结点的单链表；//
void init(Linked_Node** head){
    (*head) = (Linked_Node*)malloc(sizeof(Linked_Node));
    (*head)->next = NULL;
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

// 3、在单链表中查找元素x，找到后则【在x之前】插入元素y//
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

//获得链表长度
int getlength(Linked_Node* head){
    Linked_Node* p = head->next;
    int len = 0;
    while (p){
        len++;
        p = p->next;
    }
    return len;
}

// 2、打印输出该单链表；//
void print_list(Linked_Node* head){
    Linked_Node* p = head->next;
    while(p){
        printf("%d-->",p->data);
        p = p->next;
    }
    printf("\n");
}


void list_delete(Linked_Node* head, int k){
    if(k<1)
        return ;
    else if (k == 1){
        if(head->next){
            Linked_Node* temp = head->next;
            head->next = temp->next;
            free(temp);
            return ;
        }
        else 
            return ;
    }
    else{
        Linked_Node* pre;
        pre = find_position(head, k-1);
        if(pre == NULL ||pre->next ==NULL) 
            return ;
        else{
            Linked_Node* temp = pre->next;
            pre->next = temp->next;
            free(temp);
            return ;
        }
    }
}
// 5、删除单链表中值为x的所有元素
void delete_number(Linked_Node* head, int x){
    Linked_Node* pre = head;
    Linked_Node* after = pre->next;
    while(after){
        if(after->data == x){
            Linked_Node* temp = after;
            after = after->next;
            pre->next = after;
            free(temp);
        }
        else{
            pre = pre->next;
            after = after->next;
        }
    }
}
//清理内存
void DeleteLinkedList(Linked_Node** head){
    Linked_Node* temp1,*temp2;
    temp2 = (*head)->next;
    while(temp2){
        temp1 = temp2->next;
        free(temp2);
        temp2 = temp1;
    }
    *head = NULL;
}

// 4、假设单链表是有序的，向该单链表插入元素x，使得插入后依旧有序；
void order_insert(Linked_Node* head, int x){
    Linked_Node* p = head->next;
    Linked_Node* last = head->next;
    while(last->next){
        last = last->next;
    }
    int flag;
    flag = (p->data <= last->data)? 1 : 2;//1代表升序，2代表降序
    if(flag == 1){//此处为升序
        int count = 1;
        while(p){
            if(p->data < x){
                count++;//找出count
                p = p->next;
            }
            else break;
        }
        list_insert(head,count,x);//在count处插入x值
    }
    else{//此处为降序
        int count = 1;
        while(p){
            if(p->data > x){
                count++;//找出count
                p = p->next;
            }
            else break;
        }
        list_insert(head,count,x);//在count处插入x值
    }
}


// 8、将单链表中的最小值结点【摘除】，插入该单链表的头（即作为该单链表的第一个元素）。
void min_trance(Linked_Node* head){
    Linked_Node* p = head->next;
    Linked_Node* q = head->next;
    int x = p->data;
    int count = 1;
    while(p->next){
        p = p->next;//找到最小值x
        x = (x <= p->data) ? x : p->data; 
    }
    while(q->next){
        q = q->next;
        count++;//找到最小值x对应的位置count
        if(q->data ==x)
            break;
    }
    list_delete(head, count);//删除count位置的节点
    list_insert(head, 1, x);//在链表头处插入值为x的节点
}


// 6、给定两个升序的单链表ha、hb，将其合并为【升序的】hc。要求：利用原表空间（即hc中的结点从ha、hb中摘取，不能再重新分配空间）
void merge_list_up_print(Linked_Node* ha, Linked_Node* hb){
    Linked_Node* c;
    init(&c);
    Linked_Node* a1 = ha->next;
    Linked_Node* b1 = hb->next;
    Linked_Node* c1 = c;
    while(a1 && b1){
        if(a1->data < b1->data){
            c1->next = a1;
            c1 = c1->next;
            a1 = a1->next;
        }
        else{
            c1->next = b1;
            c1 = c1->next;
            b1 = b1->next;
        }
    }
    if(a1)
        c1->next = a1;
    if(b1)
        c1->next = b1;
    print_list(c);
}





void merge_list_down_print(Linked_Node* ha, Linked_Node* hb){
    Linked_Node* hc;
    init(&hc);
    Linked_Node* a1 = ha->next;
    Linked_Node* b1 = hb->next;
    Linked_Node* c1 = hc;
    while(a1 && b1){
        if(a1->data < b1->data){
            c1 = a1;
            a1 = a1->next;
        }
        else{
            c1 = b1;
            b1 = b1->next;
        }
        c1->next = hc->next;//使用头插法
        hc->next = c1;
    }
    if(!a1)
        a1 = b1;
    while(a1){
        c1 = a1;
        a1 = a1->next;
        c1->next = hc->next;//使用头插法
        hc->next = c1;
    }
    print_list(hc);
}



