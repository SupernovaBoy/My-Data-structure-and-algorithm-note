// 第7次抽考试题
// m度树存储int型数据
// 1、求树中的最小值+++++
// 2、求树高+++++
// 3、求层次遍历+++++
// 4、求树中x度结点的个数+++++
// 5、两棵树相加+++++
#include <stdio.h>
#include <stdlib.h>
#define max 3
#define MAX 40
#define newnode (struct tree *)malloc(sizeof(struct tree))

struct tree{
    int data;
    struct tree *c[max];
};

struct queue{
    struct tree *node[MAX];
    int front, rear;
};
//数操作
struct tree *creat_tree();//创建数
int visit(struct tree *n);//访问节点
void pre(struct tree *n);//前驱遍历
void post(struct tree *n);//后驱遍历
int count_m(struct tree *n);//计算m度节点的个数
void parenthsis_notation(struct tree *n);//括号表示法
struct tree *find_min(struct tree *n);//寻找最小值
int tree_high(struct tree *n);//求树高
void level(struct tree *n);//层次遍历
struct tree *tree_add(struct tree *a, struct tree *b);//数相加
//队列操作
void init(struct queue *q);//初始化队列
void enqueue(struct queue *q, struct tree *n);//入队
struct tree *dequeue(struct queue *q);//出队
int is_empty(struct queue *q);//判空
int is_full(struct queue *q);//判满



int main()
{
    struct tree *node;
    printf("Please input tree\'s numbers,\'0\' is NULL.\n");
    node = creat_tree();
    pre(node);
    printf("\n");
    level(node);
    ///printf("\nmin = %d, zero = %d, tree_high = %d.\n", min->data, zero, tree_high(node));
    // printf("\nmin = %d.", min->data);
    // printf("\nzero = %d.", zero);
    // printf("\ntree_high = %d.", tree_high(node));
    return 0;
}




//统计m度节点的个数
int count_m(struct tree *n){
    if(n == NULL)
        return 0;
    int i, count, sum;//i用于标记节点位置，count用于统计子节点个数，sum用于统计m度节点总数
    for(i=0, count=0; i<max; i++)
        if(n->c[i] != NULL)
            count++;
    if(count == 0)
        return 1;//判断该节点是否为m度节点，是则返回1，在sum中加上去
    //到这里说明这不是m度节点
    for(i=0, sum=0; i<max; i++)
        sum += count_m(n->c[i]);
    return sum;
}

//求数的最小值
struct tree *find_min(struct tree *n){
    if(n == NULL)
        return NULL;
    int i;
    struct tree *min_temp, *min;//i用于标记节点位置， min_temp用于临时储存节点值于min做对比，min则表示最小值
    min = n;
    for( i=0; i<max; i++){
        min_temp = find_min(n->c[i]);
        if(min_temp && min_temp->data <= min->data)
            min = min_temp;
    }
    return min;
}
//求数高
int tree_high(struct tree *n){
    if (n == NULL)
        return 0;
    int i, high_temp, high;
    for( i=0, high_temp=0, high=0; i<max; i++){
        high_temp = tree_high(n->c[i]);
        if(high < high_temp)
            high = high_temp;
    }
    return high+1;
}
//层次遍历
void level(struct tree *n){
    struct tree *p;
    struct queue q;
    int i;
    init(&q);
    enqueue( &q, n);
    while(!(is_empty(&q))){
        p = dequeue(&q);
        visit(p);
        for( i=0; i<max; i++)
            if(p->c[i] != NULL)
                enqueue( &q, p->c[i]);
    }
    return ;
}
//数加
struct tree *tree_add(struct tree *a, struct tree *b){
    struct tree *temp;
    if(a == NULL) 
        return b;
    if(b == NULL) 
        return a;
    temp = a;
    temp->data = a->data + b->data;
    for(int i=0; i<max; i++)
        temp = tree_add(a->c[i], b->c[i]);
    return temp;
}




















//建树
struct tree *creat_tree(){
    short int c;
    scanf("%d", &c);
    if(c == 0)
        return NULL;
    struct tree *node = newnode;
    node->data = c;
    for(int i=0; i<max; i++)
        node->c[i] = creat_tree();
    return node;
}
//访问
int visit(struct tree *n){
    printf("%d ", n->data);
}

//遍历
void pre(struct tree *n){
    if(n == NULL)
        return ;
    visit(n);
    for(int i=0; i<max; i++)
        pre(n->c[i]);
}

void post(struct tree *n){
    if(n == NULL)
        return ;
    for(int i=0; i<max; i++)
        post(n->c[i]);
    visit(n);
}

void init(struct queue *q){
    q->front = 0;
    q->rear = 0;
}


void enqueue(struct queue *q, struct tree *n){
    if(is_full(q)){
        printf("The queue is full now!\n");
        return ;
    }
    q->node[q->rear] = n;
    q->rear = (q->rear + 1) % MAX;
}

struct tree *dequeue(struct queue *q){
    if(is_empty(q)){
        printf("The queue is empty now!\n");
        return NULL;
    }
    struct tree *temp = q->node[q->front];//////////////////
    q->front = (q->front + 1) % MAX;
    return temp;
}

int is_empty(struct queue *q){
    if(q->front == q->rear){
        return 1;
    }
    else
        return 0;
}

int is_full(struct queue *q){
    if(q->rear == MAX-1 && q->front == 0)
        return 1;
    else 
        return 0;
}

//括号表示法
void parenthsis_notation(struct tree *n){
    int i;
    if(n == NULL)
        return ;
    printf("%d", n->data);
    for(i=0; i<max; i++)
        if(n->c[i] != NULL)
            break;
    if( i == max)
        return ;
    printf("(");
    parenthsis_notation(n->c[i]);
    for(i=i+1; i<max; i++){
        printf(",");
        parenthsis_notation(n->c[i]);
    }
    printf(")");
}

//1 2 5 0 0 0 0 0 3 0 0 0 4 0 0 8 0 0 0