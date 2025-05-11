#include<stdio.h>
int n;
void f(int k){
    for(int i=1;i<=k;i++)
    printf("*");
    printf("\n");
    return;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    f(i);
    return 0;
}