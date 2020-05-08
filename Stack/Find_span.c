#include <stdio.h>
#include <stdlib.h>

void find(int a[], int n, int b[]){
    int i, j;
    for(i=0; i<n; i++){
        j = 1;
        while (j <= i && a[i] > a[i-j])
            j++;
        b[i] = j;
    }
}
int main()
{
    int a[10];
    int b[10];
    for(int i = 0; i<10; i++)
        scanf("%d", &a[i]);
    find(a, 10, b);
    for(int i = 0; i<10; i++)
        printf("%d ", b[i]);
    return 0;
}