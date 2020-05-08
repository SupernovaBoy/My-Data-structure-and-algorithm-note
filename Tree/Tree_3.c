#include <stdio.h>
#include <stdlib.h>
#define m 3
#define MAX 100
#define newNode (tree *)malloc(sizeof(tree))
//本节课，以int型数据 完成求树高、求最大值、两棵树的相加、层次遍历
typedef struct k{
    int data;
    struct k *c[m];
}tree;
typedef struct{//数组+队首、队尾指针
    tree* data[MAX];//注意：后续队列应用中，需要使用到出队元素的孩子，故队列中存储的只能是tree*类型
    int f,r;
}queue;
void init(queue *q){q->f=0; q->r=0; }//初始化
void enQueue(queue *q, tree *x){//入队
    q->data[q->r]=x;
    q->r=(q->r+1)%MAX;
}
tree *outQueue(queue *q){//出队
    tree *x;
    x=q->data[q->f];
    q->f=(q->f+1)%MAX;
    return x;
}
int isEmpty(queue *q){//判空
    if(q->f==q->r) return 1;
    else return 0;
}
tree *creatTree(){
    int c; tree *t; int i;
    scanf("%d",&c);
    //建树=造结点，结点有两种情况：空、不空
    //if(c=='0')return NULL; //此种改法有错，'0'是char型，不是int型
    if(c==0)return NULL; //针对空
    t=newNode; //不空，先造结点，继而给所有域【赋值】
    t->data=c;
    for(i=0; i<m; i++)
        t->c[i]=creatTree(); //即造一颗树，将树根交给t->c[i]，即子树t->c[i]
    return t;
}
void pre(tree *t){//先根后子树
    int i;
    if(t==NULL)return;
    printf("%d ",t->data);
    for(i=0; i<m; i++) pre(t->c[i]);
}

void post(tree *t){ int i; //先根后子树
    if(t==NULL)return;
    for(i=0; i<m; i++) post(t->c[i]);
    printf("%d ",t->data);
}
int high(tree *t){//求树的树高
    int i,max=0,maxC=0;
    if(t==NULL) return 0;
    //策略：最高子树的树高+1，初始条件：NULL的树高为0
    for(i=0; i<m; i++){
        maxC=high(t->c[i]); //即第i棵子树的树高
        if(max<maxC)max=maxC;
    }//出循环后，max即最高子树的树高
    return max+1;
}
void level(tree *t){//层次遍历
    /*策略：利用队列先进先出的特点，
    1、根入队；
    2、while(队列不空){
       p=出队元素，
       访问p;
       p的所有非空孩子依次入队
    }
    */
    tree *p; int i;
    queue q; init(&q);//创建并初始化队列
    enQueue(&q,t);//对应1、根入队
    while( isEmpty(&q)!=1 ){
        p=outQueue(&q);
        printf("%d ",p->data);
        for(i=0; i<m; i++)
            if(p->c[i]!=NULL)enQueue(&q, p->c[i]);
    }
}
tree* max(tree *t){//求树中的最大值，算法与求树高类似
    //策略：空树返回NULL；否则，t与各子树的最大值结点比较，取最大的
    int i; tree *maxNode, *maxC;
    if(t==NULL) return NULL; //初始条件
    //走到此处，说明t不空
    maxNode=t;
    for(i=0; i<m; i++){
        maxC=max(t->c[i]); //即maxC就是子树t->c[i]的最大值结点，注maxC可能为NULL
        if(maxC!=NULL && maxC->data> maxNode->data)
            maxNode=maxC;
    }//出循环后，max即最高子树的树高
    return maxNode;
}
tree* add(tree *a, tree *b){//将a、b两棵树相加，返回新数的根，注：不会造新节点
    int i; tree *t;
    if(a==NULL) return b; //初始条件
    if(b==NULL) return a; //初始条件
    //走到此处，说明a、b均不空，后续的操作，框架与建树类似
    t=a;//t是新树的树根
    t->data=a->data+b->data;
    for(i=0; i<m; i++)
        t->c[i]=add(a->c[i],b->c[i]);
    return t;
}

main(){ tree *t ,*a, *b,*c; int x,y,z;
    printf("请输入结点，0表示NULL：");
    a=creatTree();
    printf("\n pre= "); pre(a);
    printf("\npost= "); post(a);

    printf("\n请输入结点，0表示NULL：");
    b=creatTree();
    printf("\n pre= "); pre(b);
    printf("\npost= "); post(b);
    t=add(a,b);//将a、b相加
    printf("\n\n pre= "); pre(t);
    printf("\npost= "); post(t);

    printf("\n层次遍历结果为：\n");
    level(t); //注意：需要将level(t)放在t=max(t)之上，因为后者会更改t的值
    printf("\n树高为：%d.",high(t));
    t=max(t);
    if(t==NULL)printf("\n最大值为：NULL.");
    printf("\n最大值为：%d.",t->data);

}
//测试示例：3度树
//1 2 5 0 0 0 0 0 3 0 0 0 4 0 0 8 0 0 0
//1 2 0 0 6 0 0 0 3 0 0 0 4 7 9 0 0 0 10 0 0 0 11 0 0 0 0 8 0 0 0
/*总结：
   1、求树高、求最大值，关键是：假设已知各子树的树高、最大值，如何求整棵树的树高、最大值
   2、两棵树的相加：实际上就是和建树类似，即先处理根，然后对应子树进行相加（这里面要考虑空树）
*/
