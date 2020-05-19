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
}Linjiebiao;

void insertEdge(vNode *v, eNode *e){//将结点e插入到v指向队列的尾部
	eNode *tail;
	if (v->firstNode==NULL){ v->firstNode=e; return; }
	for(tail=v->firstNode; tail->next!=NULL; tail=tail->next);
	tail->next=e;
}
void insertEdgeH(vNode *v, eNode *e){//用头插法将结点e插入到v指向队列
    e->next=v->firstNode;
    v->firstNode=e;
}

void creatGraph(Linjiebiao *g){//创建邻接表
	int i,j,a,b,vNum, eNum;
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
void printLine(vNode *h){//打印邻接表中h为头的一行
	eNode *p;
	printf("\n\t %d",h->v);
	if(h->firstNode==NULL){printf("^"); return;}
	for(p=h->firstNode; p!=NULL; p=p->next){
		printf("->%2d", p->v);
	}
	printf("^ ");
}
void printGraph(Linjiebiao *g){//输出邻接表
	int i,j;
	printf("\n图中有 %d 个点, %d 条边.\n",g->vNum,g->eNum);
	for(i=0; i<g->vNum; i++)
		printLine(&(g->v[i]));
}

main(){
	Linjiebiao g; int v;
	printf("\n开始创建图...\n");
	creatGraph(&g);
	printGraph(&g);
}
//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//下面是第17页的无向图
//8 9
//(0,1)(0,2)(1,3)(1,4)(2,5)(2,6)(3,7)(4,7)(5,6)
