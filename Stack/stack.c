#include <stdio.h>
#include <stdlib.h>


struct stack{
    int *data;
    int capacity;
    int top;
};

void init(struct stack* p, int capacity){
    p->data = (struct stack *)malloc(sizeof(capacity));
    p->capacity = capacity;
    p->top = 0;
}

int is_full(struct stack* p){
    return (p->top == p->capacity);
}

int is_empty(struct stack* p){
    return (p->top == -1);
}

int push(struct stack* p, int x){
    if(is_full(p)) return 0;
    else{
        p->data[p->top++] = x;
        return 1;
    }
}

int pop(struct stack* p){
    if(is_empty(p)) return 0;
    else
        return p->data[--p->top];
}

void delete_stack(struct stack* p){
    if(p){
        if(p->data){
            free(p->data);
            free(p);
        }
    }
}

int top(struct stack* p){
    if(is_full(p)){
        return p->data[p->top-1];
    }
    else return 0;
}
int size(struct stack* p){
    return p->top-1;
}

int main()
{
    struct stack sss;
    init(&sss, 5);
    return 0;
}