#include <stdio.h>
#include <stdlib.h>
#define MAX 20


typedef struct k{//���塾�ߡ����
	int v;
	struct k* next;
}eNode;


typedef struct{//���塾�㡿���
	int v;
	eNode* firstNode;
}vNode;


typedef struct{//�����ڽӱ�
	vNode v[MAX];
	int vNum, eNum;//ע�������0~n-1˳�����룬���vNumҲ����Ϊ��
}Adjlist;


typedef struct{//����
    int data[MAX];//�洢ͼ�еĽ�㣬��������/����
    int f,r;
}queue;


void initQueue(queue *q){
	q->f=q->r=0;
}


int isEmpty(queue *q){
	 return (q->f==q->r)? 1: 0;
}


void enQueue(queue *q,eNode* x){ //���
    q->data[q->r]=x;
	q->r=(q->r+1)%MAX;
}


eNode* outQueue(queue *q){ //����
    eNode* x=q->data[q->f];
	q->f=(q->f+1)%MAX;
    return x;
    //ע�⣺����д��q->f=(q->f+1)%MAX; return q->data[q->f-1];��why?
}


void insertEdge(vNode *v, eNode *e){//�����e���뵽vָ����е�β��
	eNode *tail;
	if (v->firstNode==NULL){
		v->firstNode=e;
		return;
	}
	for(tail=v->firstNode; tail->next!=NULL; tail=tail->next);
	tail->next=e;
}



void insertEdgeH(vNode *v, eNode *e){//��ͷ�巨�����e���뵽vָ�����
    e->next=v->firstNode;
    v->firstNode=e;
}


void creatGraph(Adjlist *g){//�����ڽӱ�
	int i,a,b,vNum, eNum;
	eNode *p;

	printf("�����������ͱ�����");
	scanf("%d",&vNum);
	scanf("%d",&eNum);
	g->vNum=vNum;
	g->eNum=eNum;
	for(i=0; i<vNum; i++){
		g->v[i].v=i; 
		g->v[i].firstNode=NULL;
	}
	fflush(stdin);

	printf("\n������ߣ���(1,2)��ʾ��1����һ���ߵ�2��\n");
	for(i=0; i<eNum; i++){
		scanf("(%d,%d)",&a,&b);
		p=(eNode *)malloc(sizeof(eNode));
		p->v=b;
		p->next=NULL;
		insertEdge(&(g->v[a]),p);
        //��������������䣬��������ͼ���ڽӱ���a��b�бߣ�b��aҲ�б�
		// p=(eNode *)malloc(sizeof(eNode));
		// p->v=a;
		// p->next=NULL;
		// insertEdge(&(g->v[b]),p);
	}
}


int degree(Adjlist *g, int v){//����g�н��v�Ķ���������+��ȣ�
	int i,outDegree, inDegree;
	eNode *p;
	outDegree=0;
	inDegree=0;
	for(p=g->v[v].firstNode;p!=NULL; p=p->next)//�������
		outDegree++;
	for(i=0; i<g->vNum; i++)//�������
		for(p=g->v[i].firstNode;p!=NULL; p=p->next)
			if(p->v==v) inDegree++;

	return outDegree+inDegree;
}


void printLine(vNode *h){//��ӡ�ڽӱ���hΪͷ��һ��
	eNode *p;
	printf("\n\t %d",h->v);
	if(h->firstNode==NULL){printf("^"); return;}
	for(p=h->firstNode; p!=NULL; p=p->next){
		printf("->%2d", p->v);
	}
	printf("^ ");
}


void printGraph(Adjlist *g){//����ڽӱ�
	int i;
	printf("\nͼ���� %d ����, %d ����.\n",g->vNum,g->eNum);
	for(i=0; i<g->vNum; i++)
		printLine(&(g->v[i]));
}


void DfsOne(Adjlist *g, int v, int visited[]){//��ͼg��v�㿪ʼ����������ȱ���������visited����ʱ����
    //ע�⣺v��ض����ڣ���δ�����ʹ�
    //���⣬֮���Խ�visited���ڲ����У�����ΪDFS�ǵݹ��㷨��������DFS�ж��壬ÿ��ջ֡�����в�ͬ��visited����ռ�
    //DFS��������������ȱ�����ֻ����������visited���鼰��ʹ�ã�why?
    eNode *p;
    printf("%d ",v);  visited[v]=1;//����v  ----���ƴ�������
    for(p=g->v[v].firstNode; p!=NULL; p=p->next)//����v�������ڽӵ�-----���ƴ�����ĸ��á�δ�����ʡ�������
        if(visited[p->v]==0)//��p->vδ�����ʹ�
            DfsOne(g,p->v,visited);
}


void DfsGraph(Adjlist *g){//������ͼg���С�������ȱ�������ע��ͼ�����Ƿ���ͨͼ
    int visited[MAX];
    int v;
    for(v=0; v<g->vNum;v++)visited[v]=0; //visited[v]��Ӧ���v��0��ʾ��δ������
    for(v=0; v<g->vNum;v++)
        if(visited[v]==0)DfsOne(g,v,visited);
}


void BfsOne(Adjlist *g, int v, int visited[]){//��ͼg��v�㿪ʼ���й�����ȱ���������visited����ʱ����
    //ע�⣺v��ض����ڣ���δ�����ʹ�
    eNode *p; queue q;
    initQueue(&q);
    enQueue(&q, v); visited[v]=1; //v��ӣ���Ӽ���ʾ��������������ˣ���visited[v]=1
    while(isEmpty(&q)==0){//�����в���
        v=outQueue(&q); printf("%d ",v);//����v
        for(p=g->v[v].firstNode; p!=NULL; p=p->next)//��p�������δ����������е��ڽӵ������У��������к�����ӣ�
            if(visited[p->v]==0){//�����δ�����ʹ�
                enQueue(&q, p->v); visited[p->v]=1; //ע�⣺�������У���Ӧ��visited[p->]Ӧ��Ϊ1
            }
    }
}


void BfsGraph(Adjlist *g){//������ͼg���С�������ȱ�������ע��ͼ�����Ƿ���ͨͼ
    int visited[MAX];
    int v;
    for(v=0; v<g->vNum;v++)visited[v]=0; //visited[v]��Ӧ���v��0��ʾ��δ������
    for(v=0; v<g->vNum;v++)
        if(visited[v]==0)BfsOne(g,v,visited);
}


int main(){
	Adjlist g; int v;
	printf("\n��ʼ����ͼ...\n");
	creatGraph(&g);
	printGraph(&g);
	//printf("\n �������v�����ڼ���v�Ķ���: ");
	//scanf("%d",&v);
	//printf("degree of v: %d.",degree(&g,v));
	printf("\n��0��㿪ʼ��������ȱ�������Ϊ: ");
	DfsGraph(&g);
	printf("\n��0��㿪ʼ�Ĺ�����ȱ�������Ϊ: ");
	BfsGraph(&g);
	return 0;
}
//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//�����ǵ�17ҳ������ͼ
//8 9
//(0,1)(0,2)(1,3)(1,4)(2,5)(2,6)(3,7)(4,7)(5,6)
