#include <stdio.h>
#include <stdlib.h>

struct btree{
    int data;
    struct btree *l, *r;
};

struct linklist{
    struct btree *data;
    struct linklist *next;
};

struct queue{
    struct linklist *f;
    struct linklist *r;
};

struct stack {
    int top;
    int capacity;
    int *array;
};



struct queue *creatqueue();
struct stack *createstack(int capacity);
void push(struct stack *s, int data);
void enqueue(struct queue *Q, struct btree *node);
int isemptyqueue(struct queue *Q);
struct btree *dequeue(struct queue *Q);
void deletequeue(struct queue *Q);
void printqueue(struct queue *Q);
struct btree *creat_tree(int data);
int findmaxlevelorder(struct btree *node);
int pop(struct stack *s);
int isemptystack(struct stack *s);
int isFullstack(struct stack *S);
void doubleStack(struct stack *S);
void preorderprint(struct btree *t);
int findinbtreeusingrecursion(struct btree *node, int data);
int findbtreeusinglevelorder(struct btree *node, int data);
void insertnodeinbtree(struct btree *node, int data);
int sizeofbtree_recursion(struct btree *node);
int sizeofofbtree_levelorder(struct btree *node);
void levelorderinreverse(struct btree *node);
void deletebtree(struct btree *node);
int heightofbtree(struct btree *node);
int heightofbtree_norecrusion(struct btree *node);
int findlevelsinbtree(struct btree *node);
int findfullnodeinbtree(struct btree *node);
int widenofbtree(struct btree *node);
void inOrder(struct btree* root);
int sumnode(struct btree *root, int *two);




int main(){
    int max, height, level, full;
    int two;
    struct btree *root;
    root = creat_tree(1);
    root->l = creat_tree(2);
    root->r = creat_tree(3);
    root->l->l = creat_tree(4);
    root->l->r = creat_tree(5);
    root->r->l = creat_tree(6);
    root->r->r = creat_tree(7);
    root->l->l->l = creat_tree(8);
    root->l->l->r = creat_tree(9);
    root->l->r->l = creat_tree(10);
    root->l->r->r = creat_tree(11);
    root->r->l->l = creat_tree(12);
    root->r->l->r = creat_tree(13);
    root->r->r->l = creat_tree(14);
    root->r->r->r = creat_tree(15);
    sumnode(root, &two);
    inOrder(root);
    printf("\ntwo = %d", two);
}





struct queue *creatqueue(){
    struct queue *Q;
    Q = (struct queue *)malloc(sizeof(struct queue));
    if(!Q){
        printf("creat error!\n");
        return NULL;
    }
    Q->f = Q->r = NULL;
    return Q;
}

struct stack *createstack(int capacity){
    struct stack *s = malloc(sizeof(struct stack));
    if(!s) 
        return NULL;
    s->capacity = capacity;
    s->top = -1;
    s->array= malloc(s->capacity * sizeof(int));
    if(!s->array) 
        return NULL;
    return s;
}


void push(struct stack *s, int data){
    if(isFullstack(s)) 
        doubleStack(s); 
    s->array[++s->top] = data;   
}


int pop(struct stack *s){
    /* S->top == - 1 indicates empty stack*/
    if(isemptystack(s)){	
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    else 
        return (s->array[s->top--]); 
}


int isemptystack(struct stack *s) {
    return (s->top == -1);  	// if the condition is true then 1 is returned else 0 is returned
}

int isFullstack(struct stack *S){
    //if the condition is true then 1 is returned else 0 is returned
    return (S->top == S->capacity - 1); 
}

void doubleStack(struct stack *S){
    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity * sizeof(int));
}

void enqueue(struct queue *Q, struct btree *node){
    struct linklist *temp;
    temp = (struct linklist *)malloc(sizeof(struct linklist));
    temp->data = node;
    temp->next = NULL;
    if(Q->r == NULL)
        Q->f = Q->r = temp;
    else {
        Q->r->next = temp;
        Q->r = temp;
    }
}
int isemptyqueue(struct queue *Q){
    if(Q->f == Q->r && Q->f == NULL)
        return 1;
    else
        return 0;
}

struct btree *dequeue(struct queue *Q){
    struct linklist *temp;
    if(!Q->f){
        printf("The Queue is empty!\n");
        return NULL;
    }
    else{
        temp = Q->f;
        Q->f = Q->f->next;
        if(Q->f == NULL)
            Q->r = NULL;
    }
    return temp->data;
}


void deletequeue(struct queue *Q){
    struct linklist *temp;
    while(Q->f){
        temp = Q->f;
        //printf("The element %d has been deleted", temp->data->data);
        Q->f = Q->f->next;
        free(temp);
    }
}


void printqueue(struct queue *Q){
    if(Q->f == Q->r && Q->r == NULL){
        printf("The queue is empty!\n");
        return ;
    }
    struct linklist *temp;
    temp = Q->f;
    while(temp){
        printf("%d\n", temp->data->data);
        temp = temp->next;
        if(!temp)
            printf("-->");
    }
}


struct btree *creat_tree(int data){
    struct btree *node;
    node = (struct btree *)malloc(sizeof(struct btree));
    if(!node){
        printf("Memory ERROR!\n");
        return NULL;
    }
    node->data = data;
    node->l = NULL;
    node->r = NULL;
    return node;
}


void preorderprint(struct btree *t){//先根后子树
    if(t==NULL)
        return ;
    printf("%d ",t->data);
    preorderprint(t->l);
    preorderprint(t->r);
}


void inOrder(struct btree* root){
     if (root == NULL) // or if (!root)
          return;
     
     inOrder(root->l);  
     printf("%d ", root->data);  
     inOrder(root->r);
} 


int sumnode(struct btree *root, int *two){//统计二度节点
    if(!NULL)
        return 0;
    two += sumnode(root->l, two);
    two += sumnode(root->r, two);
    if(!root->l && !root->r)
        return two+1;
}


int findmaxlevelorder(struct btree *node){
    struct btree *temp;
    int max = INT_MIN;
    struct queue *Q;
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(max < temp->data)
            max = temp->data;
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
    }
    deletequeue(Q);
    return max;
}

int findinbtreeusingrecursion(struct btree *node, int data){
    int temp;
    if(!node)
        return 0;
    else{
        if(data == node->data)
            return 1;
        else{
            temp = findinbtreeusingrecursion(node->l, data);
            if(temp == 1)
                return temp;
            else
                return findinbtreeusingrecursion(node->r, data);
        }
    }
    return 0;
}

int findbtreeusinglevelorder(struct btree *node, int data){
    struct btree *temp;
    struct queue *Q;
    if(!node)
        return 0;
    Q = creatqueue();
    enqueue(Q, node);
    if(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(data = temp->data)
            return 1;
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
    }
    deletequeue(Q);
    return 0;
}

void insertnodeinbtree(struct btree *node, int data){
    struct btree *temp;
    struct queue *Q;
    struct btree *newnode;
    newnode = (struct btree *)malloc(sizeof(struct btree));
    if(!newnode)
        return ;
    newnode->data = data;
    newnode->l = NULL;
    newnode->r = NULL;
    if(!node){
        node = newnode;
        return;
    }
    Q = creatqueue();
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(temp->l)
            enqueue(Q, temp->l);
        else{
            temp->l = newnode;
            deletequeue(Q);
            return ;
        }
        if(temp->r)
            enqueue(Q, temp->r);
        else{
            temp->r = newnode;
            deletequeue(Q);
            return ;
        }
    }
    deletequeue(Q);
}


int sizeofbtree_recursion(struct btree *node){
    if(!node)
        return 0;
    else
        return (sizeofbtree_recursion(node->l) + sizeofbtree_recursion(node->r) + 1);
}

int sizeofofbtree_levelorder(struct btree *node){
    if(!node)
        return 0;
    struct btree *temp;
    struct queue *Q = creatqueue();
    int count = 0;
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(temp)
            count++;
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
    }
    deletequeue(Q);
    return count;
}

void levelorderinreverse(struct btree *node){
    if(!node)
        return ;
    struct queue *Q = creatqueue();
    struct stack *S = createstack(10);
    struct btree *temp;
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
        push(S, temp->data);
    }
    while(!isemptystack(S))
        printf("%d ", pop(S));
    printf("\n");
}


void deletebtree(struct btree *node){
    if(!node)
        return ;
    deletebtree(node->l);
    deletebtree(node->r);
    free(node);
}


int heightofbtree(struct btree *node){
    if(!node)
        return 0;
    int count = 0;
    int l, r;
    l = heightofbtree(node->l);
    r = heightofbtree(node->r);
    count = (l>r) ? l : r;
    return count+1;
}


int heightofbtree_norecrusion(struct btree *node){
    if(!node)
        return 0;
    int level = 0;
    struct queue *Q = creatqueue();
    enqueue(Q, node);
    enqueue(Q, NULL);
    while(!isemptyqueue(Q)){
        node = dequeue(Q);
        if(node == NULL){
            level++;
            if(!isemptyqueue(Q))
                enqueue(Q, NULL);
        }
        if(node->l)
            enqueue(Q, node->l);
        if(node->r)
            enqueue(Q, node->r);
    }
    return level;
}


int findlevelsinbtree(struct btree *node){
    if(!node)
        return 0;
    int count = 0;
    struct queue *Q = creatqueue();
    struct btree *temp;
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(!temp->l && !temp->r)
            count++;
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
    }
    deletequeue(Q);
    return count;
}


int findfullnodeinbtree(struct btree *node){
    if(!node)
        return 0;
    int count = 0;
    struct queue *Q = creatqueue();
    struct btree *temp;
    enqueue(Q, node);
    while(!isemptyqueue(Q)){
        temp = dequeue(Q);
        if(temp->l && temp->r)
            count++;
        if(temp->l)
            enqueue(Q, temp->l);
        if(temp->r)
            enqueue(Q, temp->r);
    }
    deletequeue(Q);
    return count;
}


// int widenofbtree(struct btree *node){
    
// }









