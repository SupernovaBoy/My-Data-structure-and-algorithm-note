#include <stdio.h>
#include <stdlib.h>


typedef struct queue{
    int front;
    int rear;
    int capacity;
    int size;
    int *array;
}Queue;

Queue *creatqueue(int data);//创建环形队列
int isEmpty(Queue *q);//判空
int isFull(Queue *q);//判满
void enqueue(Queue *q, int data);//入列
int dequeue(Queue *q);//出列
void delete_queue(Queue *q);//释放队列

int main()
{
    Queue *p;
    p = creatqueue(10);
    int x;
    for(int i = 1; i <= 10; i++){
        enqueue(p, i);
        printf("%d is been enqueued.\n",i);
    }
    for(int i = 1; i <= 10; i++){
        x = dequeue(p);
        printf("%d is been dequeued.\n",x);
    }
    delete_queue(p);
    return 0;
}

Queue *creatqueue(int data){
    Queue *q = malloc(sizeof(Queue));
    if(!q){
        printf("Queue Memory ERROR!\n");
        return NULL;
    }
    q->capacity = data;
    q->front = q->rear = -1;
    q->size = 0;
    q->array = malloc(q->capacity * sizeof(int));
    if(!(q->array)){
        printf("Array memory %d ERROR!\n", data);
        return NULL;
    }
    return q;
}


int isEmpty(Queue *q){
    return (q->size == 0);
}


int isFull(Queue *q){
    return (q->size == q->capacity);
}


void enqueue(Queue *q, int data){
    if(isFull(q)){
        printf("The queue is full!\n");
        return ;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = data;
    if(q->front == -1)
        q->front = q->rear;
    q->size++;
}


int dequeue(Queue *q){
    int data = INT_MIN;
    if(isEmpty(q)){
        printf("The queue is empty!\n");
        return data;
    }
    data = q->array[q->front];
    if(q->front == q->rear){
        q->front = q->rear = -1;
        return data;
    }
    else{
        q->front = (q->front + 1) % q->capacity;
        q->size--;
        return data;
    }
}


void delete_queue(Queue *q){
    if(q){
        if(q->array)
            free(q->array);
        free(q);
    }
}
