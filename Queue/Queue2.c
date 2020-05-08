#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

typedef struct queue{
    struct Node *head;
    struct Node *tail;
}Queue;

void init(Queue *q);//初始化
int isempty(Queue *q);//判空
void enqueue(Queue *q, int data);//入列
int dequeue(Queue *q);//出列

int main()
{
    Queue *q;
    init(q);
    int x;
    for(int i = 1; i < 10; i++){
        enqueue(q, i);
        printf("%d is been enqueued!\n", i);
    }
    for(int i = 1; i < 10; i++){
        x = dequeue(q);
        printf("%d is been dequeued!\n", x);
    }
    return 0;
}


void init(Queue *q){
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(Queue *q, int data){
    struct Node *newnode = (struct Node*)(malloc(sizeof(struct Node)));
    if(!newnode){
        printf("Memory ERROR!\n");
        return ;
    }
    newnode->data = data;
    newnode->next = NULL;
    if(q->head == NULL && q->tail == NULL){
        q->head = newnode;
        q->tail = newnode;
        return ;
    }
    q->tail->next = newnode;
    q->tail = newnode;
}

int isempty(Queue *q){
    return (q->head == q->tail && NULL == q->tail);
}

int dequeue(Queue *q){
    if(isempty(q)){
        printf("The queue is empty!\n");
        return -1;
    }
    struct Node *temp = q->head;
    int x = q->head->data;
    if(q->head == q->tail){
        q->head = NULL;
        q->tail = NULL;
        free(temp);
        return x;
    }
    q->head = q->head->next;
    free(temp);
    return x;
}