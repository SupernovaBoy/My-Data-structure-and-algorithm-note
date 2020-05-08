#include <stdio.h>
#include <stdlib.h>

struct heap{
    int *array;
    int size;
    int capacity;
    int heap_type;
};


struct heap *creatheap(int capacity, int heap_type);
int parent(struct heap *node, int i);
int leftchild(struct heap *node, int i);
int rightchild(struct heap *node, int i);
int getmax(struct heap *node);
void PercolateDown(struct heap *node, int i);




struct heap *creatheap(int capacity, int heap_type){
    struct heap *H = (struct heap *)malloc(sizeof(struct heap));
    if(!H)
        return NULL;
    H->heap_type = heap_type;
    H->capacity = capacity;
    H->size = 0;
    H->array = (int *)malloc(sizeof(int) * H->capacity);
    if(!H->array)
        return NULL;
    return H;
}


int parent(struct heap *node, int i){
    if(i <= 0 || i > node->size)
        return -1;
    return (i-1)/2;
}

int leftchild(struct heap *node, int i){
    int left = 2*i+1;
    if(left >= node->size)
        return -1;
    return left;
}


int rightchild(struct heap *node, int i){
    int right = 2*i+2;
    if(right >= node->size)
        return -1;
    return right;
}


int getmax(struct heap *node){
    if(node->size == 0)
        return -1;
    return node->array[0];
}


void PercolateDown(struct heap *node, int i){
    int l, r, max, temp;
    l = leftchild(node, i);
    r = rightchild(node, i);
    if(l != -1 && node->array[l] > node->array[i])
        max = l;
    else
        max = i;
    if(l != -1 && node->array[r] > node->array[max])
        max = r;
    if(max != i){
        temp = node->array[i];
        node->array[i] = node->array[max];
        node->array[max] = temp;
    }
    PercolateDown(node, max);
}


int insert(struct heap *node, int data){
    if(node->size == node->capacity)
        ResizeHeap(node);
    node->size++;
    node->array[node->size] = data;
    PercolateDown(node, node->size-1);
}


void ResizeHeap(struct heap *node){
    int *array_old = node->array;
    node->array = (int *)malloc(sizeof(int) * node->capacity * 2);
    if(!node->array)
        return ;
    for(int i=0; i<node->capacity; i++)
        node->array[i] = array_old[i];
    node->capacity *=2;
    free(array_old);
}


void DeleteHeap(struct heap *node){
    if(!node)
        return ;
    free(node->array);
    free(node);
    node = NULL;
}


