#include <stdio.h>
#define m 10
typedef struct {
	int v[m];   //ͼ�еĵ㼯
	int e[m][m];//ͼ�еı߼������ڽӾ���
	int vNum, eNum; //ͼ�еĵ����ͱ���
}graph;
void creatGraph(graph *g){
	int i,j,a,b,vNum, eNum;
	printf("�����������ͱ�����");
	scanf("%d",&vNum);
	scanf("%d",&eNum);
	g->vNum=vNum;
	g->eNum=eNum;
	for(i=0; i<vNum; i++)
		g->v[i]=i;//��ʼ���㼯
	for(i=0; i<vNum; i++)//��ʼ���߼�
		for(j=0; j<vNum; j++)g->e[i][j]=0;
	fflush(stdin);//��ջ��棬�����������
	printf("\n������ߣ���(1,2)��ʾ��1����һ���ߵ�2��\n");
	for(i=0; i<eNum; i++){
		scanf("(%d,%d)",&a,&b);
		g->e[a][b]=1;g->e[b][a]=1;
	}
}


void printGraph(graph *g){
	int i,j;
	printf("\nͼ���� %d ����, %d ����.\n",g->vNum,g->eNum);
	for(i=0; i<(g->vNum); i++){
		printf("\t");
		for(j=0; j<(g->vNum); j++)
			printf("%d  ",g->e[i][j]);
		printf("\n");
	}
}


main(){
	graph g;
	printf("\n��ʼ����ͼ...\n");
	creatGraph(&g);
	printGraph(&g);
}//4 5
//(0,1)(0,2)(0,3)(1,2)(2,3)
