#include <stdio.h>
#include <stdlib.h>
#define max 10
struct seqlist{
    int data[max];
    int size;
};


int find_x(struct seqlist q, int l, int r, int x);
void print1(int x, int m);
void print2(int x, int m);
void even_odd(struct seqlist *q, int l, int r);
int find_min(struct seqlist q, int l, int r);
void input(struct seqlist *q);
void output(struct seqlist *q);



int main(){
    print1(5, 5);
    print2(5, 5);
    return 0;
}



//（1）在顺序表中查找值为x的元素，找到则返回下标，找不到则返回-1
int find_x(struct seqlist q, int l, int r, int x){
    if(l > r)
        return -1;
    if(q.data[l] == x)
        return l;
    find_x(q, l+1, r, x);
}


// （3）打印输出数字三角形1
void print1(int x, int m){
    if(x <= 0)
        return ;
    print1(x-1, m);
    for(int i = 0; i <= m-x; i++)
        printf(" ");
    for(int i = 1; i<=x; i++)
        printf("%d", i);
    printf("\n");
}


//（3）打印输出数字三角形2
void print2(int x, int m){
    if(x <= 0)
        return ;
    print2(x-1, m);
    for(int i = 0; i <= m-x; i++)
        printf(" ");
    for(int i = 1; i<=x; i++)
        printf("%d", i);
    if(x > 1){
        for(int i = x-1; i > 0; i--)
            printf("%d", i);
    }
    printf("\n");
}


// （4）将顺序表中的奇数、偶数分别排在两侧。要求，不得创建新的顺序表空间。
void even_odd(struct seqlist *q, int l, int r){
    if(l >= r)
        return ;
    while(l < r && q->data[l] % 2 != 0)
        l++;
    while(l < r && q->data[r] % 2 == 0)
        r--;
    if(l < r){
        int temp = q->data[l];
        q->data[l] = q->data[r];
        q->data[r] = temp;
        even_odd(q, l+1, r-1);
    }
}


//（2）在顺序表中查找最小值，并返回其下标。空表返回-1
int find_min(struct seqlist q, int l, int r){
    if(l > r)
        return -1;
    if(l == r)
        return l;
    int temp = find_min(q, l+1, r);
    if(q.data[l] < q.data[temp])
        return l;
    else
        return temp;
}

//输入
void input(struct seqlist *q){
    q->size = -1;
    int i;
    for(i = 0; i<max; i++){
        scanf("%d", &q->data[i]);
        if(q->data[i] == -1)
            break;
        q->size++;
    }
}

//输出
void output(struct seqlist *q){
    int i;
    for(i = 0; i<max && q->data[i] != -1; i++)
        printf("%d ", q->data[i]);
    printf("\n");
}
