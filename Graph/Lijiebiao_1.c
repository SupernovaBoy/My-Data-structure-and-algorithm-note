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
}Linjiebiao;

void insertEdge(vNode *v, eNode *e){//�����e���뵽vָ����е�β��
	eNode *tail;
	if (v->firstNode==NULL){ v->firstNode=e; return; }
	for(tail=v->firstNode; tail->next!=NULL; tail=tail->next);
	tail->next=e;
}
void insertEdgeH(vNode *v, eNode *e){//��ͷ�巨�����e���뵽vָ�����
    e->next=v->firstNode;
    v->firstNode=e;
}

void creatGraph(Linjiebiao *g){//�����ڽӱ�
	int i,j,a,b,vNum, eNum;
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
void printLine(vNode *h){//��ӡ�ڽӱ���hΪͷ��һ��
	eNode *p;
	printf("\n\t %d",h->v);
	if(h->firstNode==NULL){printf("^"); return;}
	for(p=h->firstNode; p!=NULL; p=p->next){
		printf("->%2d", p->v);
	}
	printf("^ ");
}
void printGraph(Linjiebiao *g){//����ڽӱ�
	int i,j;
	printf("\nͼ���� %d ����, %d ����.\n",g->vNum,g->eNum);
	for(i=0; i<g->vNum; i++)
		printLine(&(g->v[i]));
}

main(){
	Linjiebiao g; int v;
	printf("\n��ʼ����ͼ...\n");
	creatGraph(&g);
	printGraph(&g);
}
//7 11
//(0,1)(0,3)(0,4)(1,2)(1,4)(1,5)(2,6)(3,4)(4,2)(4,5)(5,6)
//�����ǵ�17ҳ������ͼ
//8 9
//(0,1)(0,2)(1,3)(1,4)(2,5)(2,6)(3,7)(4,7)(5,6)
