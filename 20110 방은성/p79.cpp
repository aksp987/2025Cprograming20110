#include<stdio.h>
int n, d[10001];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d  ",&d[i]);
    for(int i=1;i<=n;i++)
    printf("%d  ",d[i]);
    printf("\n");
    return 0;
}