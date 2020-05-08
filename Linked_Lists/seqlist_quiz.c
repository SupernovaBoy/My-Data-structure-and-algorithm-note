#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
typedef struct{
    int *a;
    int length;
} seqlist;
int get_length(int number[]);//获得数组长度-
void init_list(seqlist *list);//初始化顺序表-
void input_list(seqlist *list);//输入顺序表-
void print_list(seqlist *list);//输出顺序表-
void list_insert(seqlist *list, int i, int x);//在顺序表i处插入x值-
void delete_list_sub(seqlist *list, int i);//删除顺序表i处的值-
void sort_up(seqlist *list);//将顺序表升序排列-
void sort_down(seqlist *list);//将顺序表降序排列-
void even_odd(seqlist *list);//将顺序表偶数排列在前，奇数排列在后-
void order_insert(seqlist *list, int x);//在顺序表插入x值，使其保持有序状态-
void delete_number(seqlist *list, int x);//删除顺序表中所有的x-
void delete_triphase(seqlist *list);//删除顺序表中所有3的倍数-
void merge_list_up_print(seqlist *A, seqlist *B);//合并顺序表并升序排列输出
void merge_list_down_print(seqlist *A, seqlist *B);//合并顺序表并降序排列输出



//顺序表初始化
void init_list(seqlist *list){
    list->a = (int *)malloc(maxsize*sizeof(int));
    list->length = 0;
}

void input_list(seqlist *list){
    int *p;
    for(p=list->a; p < list->a + maxsize ; p++){
        scanf("%d",p);
        if(*p == -1) break;
        list->length ++;
    }
}

void print_list(seqlist *list){
    int *p;
    for(p=list->a; p < list->a + list->length && *p != -1; p++){
        printf("%d ",*p);
    }
}

int get_length(int number[]){
    int index;
    for(index=0; ; index++)
        if(number[index] == -1)
            break;
    return index;
}

void list_insert(seqlist *list, int i, int x){
    if( i < 1 || i > list->length-1 )
        printf("ERROR list insert, the \'i\' is invalid.\n");
    else{
        int *p, *q;
        p = list->a + list->length -1;
        q = list->a + i -1;
        for(; p>=q; p--)
            *(p+1) = *(p);
        *(p+1) = x;
    }
    list->length++;
}

void delete_list_sub(seqlist *list, int i){
    if(i<1||i>list->length-1)
        printf("ERROR list delete, the \'i\' is invalid.\n");
    else{
        int *p,x;
        p = list->a + i-1;
        x=*p;
        for(; p < list->a + list->length -1; p++)
            *p = *(p+1);
        list->length--;
        printf("%d have been deleted.\n",x);
    }
}

void sort_up(seqlist *list){
    int *p, temp;
    p = list->a;
    for(; p<list->a + list->length-1; p++){
        for(int *q = list->a + list->length-1; q>p; q--){
            if(*q<*p){
                temp = *p;
                *p = *q;
                *q = temp;
            }
        }
    }
}

void sort_down(seqlist *list){
    int *p, temp;
    p = list->a;
    for(; p<list->a + list->length-1; p++){
        for(int *q = list->a + list->length-1; q>p; q--){
            if(*q>*p){
                temp = *p;
                *p = *q;
                *q = temp;
            }
        }
    }
}

void sort_up_number(int number[]){
    int i, j, temp;
    for(i = 0; number[i] != -1; i++){
        for(j = get_length(number)-1; j > i; j--){
            if(number[j] < number[j-1]){
                temp = number[j];
                number[j] = number[j-1];
                number[j-1] = temp;
            }
        }
    }
}

void sort_down_number(int number[]){
    int i, j, temp;
    for(i = 0; number[i] != -1; i++){
        for(j = get_length(number)-1; j > i; j--){
            if(number[j] > number[j-1]){
                temp = number[j];
                number[j] = number[j-1];
                number[j-1] = temp;
            }
        }
    }
}

//奇数偶数排序
void even_odd(seqlist *list){
    int *p = list->a;
    int i, j;
    int even[50], odd[50];
    for(i=j=0; p<list->a + list->length -1; p++){
        if(*p % 2 ==0)
            even[i++] = *p;
        else
            odd[j++] = *p;
    }
    even[i] = odd[j] = -1;
    p = list->a;
    i = j = 0;
    while((*(p++) = even[i++]) != -1);
    for(p--; odd[j]!=-1; j++){
        *(p++) = odd[j];
    }
}

void order_insert(seqlist *list, int x){
    int *p = list->a;
    int temp1 = *p;
    int temp2 = *(p+list->length-1);
    int cnt=0;
    for(; p<list->a + list->length-1;p++){
        if(temp1<temp2){
            if(*p > x) break;
            cnt++;
        }
        else{
            if(*p < x) break;
            cnt++;
        }
    }
    cnt++;
    int *m, *n;
    m = list->a + list->length -1;
    n = list->a + cnt -1;
    for(; m>=n; m--)
        *(m+1) = *(m);
    *(m+1) = x;
    list->length++;
}

void delete_number(seqlist *list, int x){
    int *p = list->a;
    int *q = list->a;
    int cnt=0;
    for(; p<list->a + list->length ; p++)
        if(*p != x)
            *(q++) = *p;
        else cnt++;
    list->length-=cnt;
}

void delete_triphase(seqlist *list){
    int *p = list->a;
    int *q = list->a;
    int cnt=0;
    for(; p<list->a + list->length ; p++)
        if(*p % 3 != 0)
            *(q++) = *p;
        else cnt++;
    list->length-=cnt;
}

void merge_list_up_print(seqlist *A, seqlist *B){
    int temp[100];
    int i, *j, *k;
    i = 0;
    j = A->a;
    k = B->a;
    while((temp[i++] = *(j++)) != -1);
    for(i--; *k != -1; k++)
        temp[i++] = *k;
    temp[i] = -1;
    sort_up_number(temp);
    for(i = 0; temp[i]!=-1; i++)
        printf("%d ",temp[i]);
    printf("\n");
}

void merge_list_down_print(seqlist *A, seqlist *B){
    int temp[100];
    int i, *j, *k;
    i = 0;
    j = A->a;
    k = B->a;
    while((temp[i++] = *(j++)) != -1);
    for(i--; *k != -1; k++)
        temp[i++] = *k;
    temp[i] = -1;
    sort_down_number(temp);
    for(i = 0; temp[i]!=-1; i++)
        printf("%d ",temp[i]);
    printf("\n");
}