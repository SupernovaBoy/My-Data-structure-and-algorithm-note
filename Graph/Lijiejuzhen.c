#include <stdio.h>
#define m 10
typedef struct {
	int v[m];   //图中的点集
	int e[m][m];//图中的边集，即邻接矩阵
	int vNum, eNum; //图中的点数和边数
}graph;
void creatGraph(graph *g){
	int i,j,a,b,vNum, eNum;
	printf("请输入结点数和边数：");
	scanf("%d",&vNum);
	scanf("%d",&eNum);
	g->vNum=vNum;
	g->eNum=eNum;
	for(i=0; i<vNum; i++)
		g->v[i]=i;//初始化点集
	for(i=0; i<vNum; i++)//初始化边集
		for(j=0; j<vNum; j++)g->e[i][j]=0;
	fflush(stdin);//清空缓存，避免意外错误
	printf("\n请输入边，如(1,2)表示从1发出一条边到2：\n");
	for(i=0; i<eNum; i++){
		scanf("(%d,%d)",&a,&b);
		g->e[a][b]=1;g->e[b][a]=1;
	}
}


void printGraph(graph *g){
	int i,j;
	printf("\n图中有 %d 个点, %d 条边.\n",g->vNum,g->eNum);
	for(i=0; i<(g->vNum); i++){
		printf("\t");
		for(j=0; j<(g->vNum); j++)
			printf("%d  ",g->e[i][j]);
		printf("\n");
	}
}


main(){
	graph g;
	printf("\n开始创建图...\n");
	creatGraph(&g);
	printGraph(&g);
}//4 5
//(0,1)(0,2)(0,3)(1,2)(2,3)
