#include <stdio.h>
#include <stdlib.h>
#define max 20


struct Enode{
    int value;
    struct Enode *next;
};
struct Vnode{
    int value;
    struct Enode *firstnode;
};
struct graph{
    int V;
    int E;
    struct Vnode v[max];
};
struct queue{
    int data[max];
    int f, r;
};


void printfgraph(struct graph *G);
void printline(struct Vnode *temp);
void creat_graph(struct graph *G);
void insert(struct Vnode *V, struct Enode *E);
void degree(struct graph *g, int vertex);
int dequeue(struct queue *q);
void enqueue(struct queue *q, int data);
int isempty(struct queue *q);
void DFS_graph(struct graph *g);
void DFS_one(struct graph *g, int v, int visit[]);
void BFS_one(struct graph *g, int v, int visit[]);
void BFS_graph(struct graph *g);






int main(){
    struct graph node;
    creat_graph(&node);
    printfgraph(&node);
    DFS_graph(&node);
    BFS_graph(&node);
    return 0;
}


void init_queue(struct queue *q){
    q->r = q->f = 0;
} 


int isempty(struct queue *q){
    return (q->f == q->r);
}


void enqueue(struct queue *q, int data){
    q->data[q->r] = data;
    q->r = (q->r+1)%max;
}


int dequeue(struct queue *q){
    int x = q->data[q->f];
    q->f = (q->f+1)%max;
    return x;
}


void insert(struct Vnode *V, struct Enode *E){
    if(!V->firstnode){
        V->firstnode  = E;
        return ;
    }
    struct Enode *tail;
    for(tail = V->firstnode; tail->next !=NULL; tail = tail->next);
    tail->next = E;
}


void creat_graph(struct graph *G){
    int i, a, b, vnode, enode;
    printf("Please input Vertex and Edge.\n");
    scanf("%d %d", &vnode, &enode);
    G->V = vnode;
    G->E = enode;
    for(i=0; i<G->V; i++){
        G->v[i].value = i;
        G->v[i].firstnode = NULL;
    }
    printf("Please input Edges.\n");
    printf("Example: (1,2) is the edge from 1 to 2.\n");
    fflush(stdin);
    for(i=0; i<G->E; i++){
        scanf("(%d,%d)", &a, &b);
        struct Enode *temp = (struct Enode *)malloc(sizeof(struct Enode));
        temp->value = b;
        temp->next = NULL;
        insert(&G->v[a], temp);
    }
}


void printline(struct Vnode *temp){
    printf("\n\t%d", temp->value);
    struct Enode *edge =temp->firstnode;
    for(; edge !=NULL; edge = edge->next)
        printf("-->%d", edge->value);
    printf("^");
}


void printfgraph(struct graph *G){
    int i;
    for(i=0; i<G->V; i++)
        printline(&G->v[i]);
    printf("\n");
}


void degree(struct graph *g, int vertex){
    int i, outdegree, indgree;
    struct Enode *temp = g->v[vertex].firstnode;
    for(outdegree = 0; temp != NULL; temp = temp->next)
        outdegree++;
    for(i=0, indgree=0; i<g->V; i++)
        for(temp=g->v[i].firstnode; temp!=NULL; temp=temp->next)
            if(temp->value == vertex)
                indgree++;
    printf("\nThe vertex %d\'s degree is %d.\nOutdegree: %d Indegree: %d \n", vertex, outdegree+indgree, outdegree, indgree);
}


void DFS_graph(struct graph *g){
    int visit[max];
    int i;
    printf("DFS: ");
    for(i=0; i<g->V; i++)
        visit[i] = 0;
    for(i=0; i<g->V; i++){
        if(visit[i]==0)
            DFS_one(g, i, visit);
    }
    printf("\n");
}


void DFS_one(struct graph *g, int v, int visit[]){
    struct Enode *temp ;
    printf("%d ",v);
    visit[v] = 1;
    for(temp = g->v[v].firstnode; temp!=NULL; temp = temp->next)
        if(visit[temp->value] == 0)
            DFS_one(g, temp->value, visit);
}


void BFS_graph(struct graph *g){
    int visit[max];
    int i;
    printf("BFS: ");
    for(i=0; i<g->V; i++)
        visit[i] = 0;
    for(i=0; i<g->V; i++){
        if(visit[i]==0)
            BFS_one(g, i, visit);
    }
    printf("\n");
}


void BFS_one(struct graph *g, int v, int visit[]){
    struct queue q;
    struct Enode *temp;
    init_queue(&q);
    enqueue(&q, v);
    visit[v] = 1;
    while(!isempty(&q)){
        v=dequeue(&q);
        printf("%d ", v);
        for(temp = g->v[v].firstnode; temp!=NULL; temp = temp->next)
            if(visit[temp->value]==0){
                enqueue(&q, temp->value);
                visit[temp->value] = 1;
            }
    }
}

//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//8 8
//(0,1)(0,2)(0,3)(1,3)(3,5)(3,4)(4,6)(6,7)






































