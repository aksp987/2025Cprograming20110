#include<stdio.h>
int n;
void f(){
    printf("*");
    return;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    f();
    return 0;
}