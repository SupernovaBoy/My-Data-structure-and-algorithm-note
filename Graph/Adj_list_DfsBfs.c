#include <stdio.h>
#include <stdlib.h>
#define MAX 20


typedef struct k{//定义【边】结点
	int v;
	struct k* next;
}eNode;


typedef struct{//定义【点】结点
	int v;
	eNode* firstNode;
}vNode;


typedef struct{//定义邻接表
	vNode v[MAX];
	int vNum, eNum;//注：因结点从0~n-1顺次输入，因此vNum也可作为表长
}Adjlist;


typedef struct{//队列
    int data[MAX];//存储图中的结点，即结点入队/出队
    int f,r;
}queue;


void initQueue(queue *q){
	q->f=q->r=0;
}


int isEmpty(queue *q){
	 return (q->f==q->r)? 1: 0;
}


void enQueue(queue *q,eNode* x){ //入队
    q->data[q->r]=x;
	q->r=(q->r+1)%MAX;
}


eNode* outQueue(queue *q){ //出队
    eNode* x=q->data[q->f];
	q->f=(q->f+1)%MAX;
    return x;
    //注意：不能写成q->f=(q->f+1)%MAX; return q->data[q->f-1];，why?
}


void insertEdge(vNode *v, eNode *e){//将结点e插入到v指向队列的尾部
	eNode *tail;
	if (v->firstNode==NULL){
		v->firstNode=e;
		return;
	}
	for(tail=v->firstNode; tail->next!=NULL; tail=tail->next);
	tail->next=e;
}



void insertEdgeH(vNode *v, eNode *e){//用头插法将结点e插入到v指向队列
    e->next=v->firstNode;
    v->firstNode=e;
}


void creatGraph(Adjlist *g){//创建邻接表
	int i,a,b,vNum, eNum;
	eNode *p;

	printf("请输入结点数和边数：");
	scanf("%d",&vNum);
	scanf("%d",&eNum);
	g->vNum=vNum;
	g->eNum=eNum;
	for(i=0; i<vNum; i++){
		g->v[i].v=i; 
		g->v[i].firstNode=NULL;
	}
	fflush(stdin);

	printf("\n请输入边，如(1,2)表示从1发出一条边到2：\n");
	for(i=0; i<eNum; i++){
		scanf("(%d,%d)",&a,&b);
		p=(eNode *)malloc(sizeof(eNode));
		p->v=b;
		p->next=NULL;
		insertEdge(&(g->v[a]),p);
        //加入下面两行语句，就是无向图的邻接表，即a到b有边，b到a也有边
		// p=(eNode *)malloc(sizeof(eNode));
		// p->v=a;
		// p->next=NULL;
		// insertEdge(&(g->v[b]),p);
	}
}


int degree(Adjlist *g, int v){//计算g中结点v的度数（出度+入度）
	int i,outDegree, inDegree;
	eNode *p;
	outDegree=0;
	inDegree=0;
	for(p=g->v[v].firstNode;p!=NULL; p=p->next)//计算出度
		outDegree++;
	for(i=0; i<g->vNum; i++)//计算入度
		for(p=g->v[i].firstNode;p!=NULL; p=p->next)
			if(p->v==v) inDegree++;

	return outDegree+inDegree;
}


void printLine(vNode *h){//打印邻接表中h为头的一行
	eNode *p;
	printf("\n\t %d",h->v);
	if(h->firstNode==NULL){printf("^"); return;}
	for(p=h->firstNode; p!=NULL; p=p->next){
		printf("->%2d", p->v);
	}
	printf("^ ");
}


void printGraph(Adjlist *g){//输出邻接表
	int i;
	printf("\n图中有 %d 个点, %d 条边.\n",g->vNum,g->eNum);
	for(i=0; i<g->vNum; i++)
		printLine(&(g->v[i]));
}


void DfsOne(Adjlist *g, int v, int visited[]){//对图g从v点开始进行深度优先遍历，其中visited是临时数组
    //注意：v点必定存在，且未被访问过
    //另外，之所以将visited放在参数中，是因为DFS是递归算法，若放在DFS中定义，每个栈帧将会有不同的visited数组空间
    //DFS类似树的深度优先遍历，只不过新增了visited数组及其使用，why?
    eNode *p;
    printf("%d ",v);  visited[v]=1;//访问v  ----类似处理树根
    for(p=g->v[v].firstNode; p!=NULL; p=p->next)//遍历v的所有邻接点-----类似处理根的各棵【未被访问】的子树
        if(visited[p->v]==0)//即p->v未被访问过
            DfsOne(g,p->v,visited);
}


void DfsGraph(Adjlist *g){//对整个图g进行【深度优先遍历】，注：图可以是非连通图
    int visited[MAX];
    int v;
    for(v=0; v<g->vNum;v++)visited[v]=0; //visited[v]对应结点v，0表示尚未被访问
    for(v=0; v<g->vNum;v++)
        if(visited[v]==0)DfsOne(g,v,visited);
}


void BfsOne(Adjlist *g, int v, int visited[]){//对图g从v点开始进行广度优先遍历，其中visited是临时数组
    //注意：v点必定存在，且未被访问过
    eNode *p; queue q;
    initQueue(&q);
    enQueue(&q, v); visited[v]=1; //v入队，入队即表示已纳入访问序列了，故visited[v]=1
    while(isEmpty(&q)==0){//当队列不空
        v=outQueue(&q); printf("%d ",v);//访问v
        for(p=g->v[v].firstNode; p!=NULL; p=p->next)//将p结点所有未纳入访问序列的邻接点加入队列（类似所有孩子入队）
            if(visited[p->v]==0){//若结点未被访问过
                enQueue(&q, p->v); visited[p->v]=1; //注意：纳入序列，对应的visited[p->]应置为1
            }
    }
}


void BfsGraph(Adjlist *g){//对整个图g进行【广度优先遍历】，注：图可以是非连通图
    int visited[MAX];
    int v;
    for(v=0; v<g->vNum;v++)visited[v]=0; //visited[v]对应结点v，0表示尚未被访问
    for(v=0; v<g->vNum;v++)
        if(visited[v]==0)BfsOne(g,v,visited);
}


int main(){
	Adjlist g; int v;
	printf("\n开始创建图...\n");
	creatGraph(&g);
	printGraph(&g);
	//printf("\n 请输入点v，用于计算v的度数: ");
	//scanf("%d",&v);
	//printf("degree of v: %d.",degree(&g,v));
	printf("\n从0结点开始的深度优先遍历序列为: ");
	DfsGraph(&g);
	printf("\n从0结点开始的广度优先遍历序列为: ");
	BfsGraph(&g);
	return 0;
}
//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//下面是第17页的无向图
//8 9
//(0,1)(0,2)(1,3)(1,4)(2,5)(2,6)(3,7)(4,7)(5,6)
