//该文件Orderstruct list.c是顺序表的相关操作

#include <stdio.h>
#include <stdlib.h>
#define max 10
void init(struct list** p);
void input(struct list* p);
void print(struct list* p);/*
int insert(struct list* p, int k, int x);
int delete(struct list* p, int k);
void sort_up(struct list* p);
void sort_down(struct list* p);
void even_odd(struct list* p);
int order_sort(struct list* p, int x);
void delete_number(struct list* p, int x);
void delete_triphase(struct list* p);
void merge_list_up_print(struct list *A, struct list *B);*/


struct list{
    int data[max];
    int length;
};

int main()
{
    struct list p;
    p.length = 0;
    input(&p);
    print(&p);
}


void init(struct list** p){
    (*p)->length =0;
}

void input(struct list* p){
    for(int i=0; p->data[i-1]!=-1; i++){
        scanf("%d", &p->data[i]);
        p->length++;
    }
    p->length--;
}

void print(struct list* p){
    for(int i=0; p->data[i] !=-1; i++)
        printf("%d ", p->data[i]);
    printf("\n");
}
/*
int insert(struct list* p, int k, int x){
    if(k<0 || k > (p->length)+2 ||p->length == max) return 0;
    else{
        for(int i=(p->length)+1; i>=k; i--)
            p->data[i+1] = p->data[i];
        p->data[k] = x;
        return 1;
    }
}

int delete(struct list* p, int k){
    if(k<1 || k>p->length) return 0;
    else{
        for(int i = k; i <= p->length; i++)
            p->data[i] = p->data[i+1];
        return 1;
    }
}

void sort_up(struct list* p){
    int temp;
    for(int i = 0; i<p->length-1; i++){
        for(int j = p->length-1; j>i; j--){
            if(p->data[i]>p->data[j]){
                temp = p->data[i];
                p->data[i]  =p->data[j];
                p->data[j] = temp;
            }
        }
    }
}


void sort_down(struct list* p){
    int temp;
    for(int i = 0; i<p->length-1; i++){
        for(int j = p->length-1; j>i; j--){
            if(p->data[i]<p->data[j]){
                temp = p->data[i];
                p->data[i]  =p->data[j];
                p->data[j] = temp;
            }
        }
    }
}

void even_odd(struct list* p){
    int even[50],odd[50];
    int i=0,j=0,k=0;
    for(; p->data[i] != -1; i++){
        if(p->data[i] % 2 == 0){
            even[j] = p->data[i];
            j++;
        }
        else{
            odd[k] = p->data[i];
            k++;
        }
    }
    even[j] = -1;
    odd[k] = -1;
    i = j = k =0;
    while((p->data[i++] = even[j++])!=-1);
    p->data[i--] = 1;
    while((p->data[i++] = odd[k++])!=-1);
}

int order_sort(struct list* p, int x){
    if(p->data[0] < p->data[p->length-1]){
        int i;
        for(i=0; i<p->length; i++)
            if(x<p->data[i]) break;
        insert(p, i, x);
    }
    if(p->data[0]>p->data[p->length-1]){
        int i;
        for(i=0; i<p->length; i++)
            if(x>p->data[i]) break;
        insert(p, i, x);
    }
}

void delete_number(struct list* p, int x){
    int i = 0;
    int j = 0;
    int cnt = 0;
    for(; i<p->length; i++)
        if(p->data[i]!=x)
            p->data[j++] = p->data[i];
        else cnt++;
    p->length -= cnt;
}

void delete_triphase(struct list* p){
    int i=0;
    int j=0;
    int cnt=0;
    for(; i<p->length ; i++)
        if(p->data[i] % 3 != 0)
            p->data[j++] = p->data[i];
        else cnt++;
    p->length-=cnt;
}


void merge_list_up_print(struct list *A, struct list *B){
    struct list *temp;
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    while((temp->data[i++] = A->data[j++])!=-1);
    temp->data[i--] = 1;
    while((temp->data[i++] = B->data[k++])!=-1);
    sort_up(temp);
    print(temp);
}
*/