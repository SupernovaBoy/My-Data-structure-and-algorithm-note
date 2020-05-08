#include <stdio.h>
#include <stdlib.h>
#define m 3
#define MAX 100
#define newNode (tree *)malloc(sizeof(tree))
//���ڿΣ���int������ ��������ߡ������ֵ������������ӡ���α���
typedef struct k{
    int data;
    struct k *c[m];
}tree;
typedef struct{//����+���ס���βָ��
    tree* data[MAX];//ע�⣺��������Ӧ���У���Ҫʹ�õ�����Ԫ�صĺ��ӣ��ʶ����д洢��ֻ����tree*����
    int f,r;
}queue;
void init(queue *q){q->f=0; q->r=0; }//��ʼ��
void enQueue(queue *q, tree *x){//���
    q->data[q->r]=x;
    q->r=(q->r+1)%MAX;
}
tree *outQueue(queue *q){//����
    tree *x;
    x=q->data[q->f];
    q->f=(q->f+1)%MAX;
    return x;
}
int isEmpty(queue *q){//�п�
    if(q->f==q->r) return 1;
    else return 0;
}
tree *creatTree(){
    int c; tree *t; int i;
    scanf("%d",&c);
    //����=���㣬���������������ա�����
    //if(c=='0')return NULL; //���ָķ��д�'0'��char�ͣ�����int��
    if(c==0)return NULL; //��Կ�
    t=newNode; //���գ������㣬�̶��������򡾸�ֵ��
    t->data=c;
    for(i=0; i<m; i++)
        t->c[i]=creatTree(); //����һ����������������t->c[i]��������t->c[i]
    return t;
}
void pre(tree *t){//�ȸ�������
    int i;
    if(t==NULL)return;
    printf("%d ",t->data);
    for(i=0; i<m; i++) pre(t->c[i]);
}

void post(tree *t){ int i; //�ȸ�������
    if(t==NULL)return;
    for(i=0; i<m; i++) post(t->c[i]);
    printf("%d ",t->data);
}
int high(tree *t){//����������
    int i,max=0,maxC=0;
    if(t==NULL) return 0;
    //���ԣ��������������+1����ʼ������NULL������Ϊ0
    for(i=0; i<m; i++){
        maxC=high(t->c[i]); //����i������������
        if(max<maxC)max=maxC;
    }//��ѭ����max���������������
    return max+1;
}
void level(tree *t){//��α���
    /*���ԣ����ö����Ƚ��ȳ����ص㣬
    1������ӣ�
    2��while(���в���){
       p=����Ԫ�أ�
       ����p;
       p�����зǿպ����������
    }
    */
    tree *p; int i;
    queue q; init(&q);//��������ʼ������
    enQueue(&q,t);//��Ӧ1�������
    while( isEmpty(&q)!=1 ){
        p=outQueue(&q);
        printf("%d ",p->data);
        for(i=0; i<m; i++)
            if(p->c[i]!=NULL)enQueue(&q, p->c[i]);
    }
}
tree* max(tree *t){//�����е����ֵ���㷨������������
    //���ԣ���������NULL������t������������ֵ���Ƚϣ�ȡ����
    int i; tree *maxNode, *maxC;
    if(t==NULL) return NULL; //��ʼ����
    //�ߵ��˴���˵��t����
    maxNode=t;
    for(i=0; i<m; i++){
        maxC=max(t->c[i]); //��maxC��������t->c[i]�����ֵ��㣬עmaxC����ΪNULL
        if(maxC!=NULL && maxC->data> maxNode->data)
            maxNode=maxC;
    }//��ѭ����max���������������
    return maxNode;
}
tree* add(tree *a, tree *b){//��a��b��������ӣ����������ĸ���ע���������½ڵ�
    int i; tree *t;
    if(a==NULL) return b; //��ʼ����
    if(b==NULL) return a; //��ʼ����
    //�ߵ��˴���˵��a��b�����գ������Ĳ���������뽨������
    t=a;//t������������
    t->data=a->data+b->data;
    for(i=0; i<m; i++)
        t->c[i]=add(a->c[i],b->c[i]);
    return t;
}

main(){ tree *t ,*a, *b,*c; int x,y,z;
    printf("�������㣬0��ʾNULL��");
    a=creatTree();
    printf("\n pre= "); pre(a);
    printf("\npost= "); post(a);

    printf("\n�������㣬0��ʾNULL��");
    b=creatTree();
    printf("\n pre= "); pre(b);
    printf("\npost= "); post(b);
    t=add(a,b);//��a��b���
    printf("\n\n pre= "); pre(t);
    printf("\npost= "); post(t);

    printf("\n��α������Ϊ��\n");
    level(t); //ע�⣺��Ҫ��level(t)����t=max(t)֮�ϣ���Ϊ���߻����t��ֵ
    printf("\n����Ϊ��%d.",high(t));
    t=max(t);
    if(t==NULL)printf("\n���ֵΪ��NULL.");
    printf("\n���ֵΪ��%d.",t->data);

}
//����ʾ����3����
//1 2 5 0 0 0 0 0 3 0 0 0 4 0 0 8 0 0 0
//1 2 0 0 6 0 0 0 3 0 0 0 4 7 9 0 0 0 10 0 0 0 11 0 0 0 0 8 0 0 0
/*�ܽ᣺
   1�������ߡ������ֵ���ؼ��ǣ�������֪�����������ߡ����ֵ������������������ߡ����ֵ
   2������������ӣ�ʵ���Ͼ��Ǻͽ������ƣ����ȴ������Ȼ���Ӧ����������ӣ�������Ҫ���ǿ�����
*/
