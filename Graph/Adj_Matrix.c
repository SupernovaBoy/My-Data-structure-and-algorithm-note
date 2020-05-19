#include <stdio.h>
#include <stdlib.h>
#define max 20
typedef struct Graph{
    int V;
    int E;
    int m[max][max];
} graph;

typedef struct Queue{
    int data[max];
    int f, r;
} queue;

graph *creat_graph();
void init_queue(queue *Q);
int isempty(queue *q);
void enqueue(queue *q, int data);
int dequeue(queue *q);
void DFS_one(graph *g, int v, int visit[]);
void DFS_graph(graph *g);
void BFS_one(graph *g, int v, int visit[]);
void BFS_graph(graph *g);
void print_graph(graph *g);


int main(){
    graph *g;
    g = creat_graph();
    print_graph(g);
    DFS_graph(g);
    BFS_graph(g);
    return 0;
}


void init_queue(queue *q){
    q->f = q->r = 0;
}


void enqueue(queue *q, int data){
    q->data[q->r] = data;
    q->r = (q->r+1)%max;
}


int dequeue(queue *q){
    int data = q->data[q->f];
    q->f = (q->f+1)%max;
    return data;
}


int isempty(queue *q){
    return (q->f == q->r);
}


graph *creat_graph(){
    int i, j, k, V, E;
    graph *G = (graph *)malloc(sizeof(graph));
    if(!G)
        return NULL;
    printf("Please input vertex and edge numbers.\neg:  vertex edge\n");
    scanf("%d %d", &V, &E);
    G->V = V;
    G->E = E;
    for(i=0; i<G->V; i++)
        for(j=0; j<G->E; j++)
            G->m[i][j] = 0;
    printf("Please input Edges.\n");
    printf("Example: (1,2) is the edge from 1 to 2.\n");
    fflush(stdin);
    for(k=0; k<G->E; k++){
        scanf("(%d,%d)", &i, &j);
        G->m[i][j] = 1;
    }
    return G;
}


void DFS_graph(graph *g){
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


void DFS_one(graph *g, int v, int visit[]){
    printf("%d ",v);
    visit[v] = 1;
    for(int i=0; i<g->V; i++)
        if(g->m[v][i] == 1 && visit[i]==0)
            DFS_one(g, i, visit);
}


void BFS_graph(graph *g){
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


void BFS_one(graph *g, int v, int visit[]){
    queue q;
    init_queue(&q);
    enqueue(&q, v);
    visit[v] = 1;
    while(!isempty(&q)){
        v=dequeue(&q);
        printf("%d ", v);
        for(int i=0; i<g->V; i++)
            if(visit[i]==0 && g->m[v][i]==1){
                enqueue(&q, i);
                visit[i] = 1;
            }
    }
}


void print_graph(graph *g){
    int i, j;
    for(i=0; i<g->V; i++){
        for(j=0; j<g->V; j++)
            printf("%d ", g->m[i][j]);
        printf("\n");
    }
}
//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//8 9
//(0,1)(0,2)(1,3)(1,4)(2,5)(2,6)(3,7)(4,7)(5,6)
//8 8
//(0,1)(0,2)(0,3)(1,3)(3,5)(3,4)(4,6)(6,7)
