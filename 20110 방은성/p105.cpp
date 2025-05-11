#include<stdio.h>
int n;
int f(){
    int t=123;
    return t;
}
int main(){
    int s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    s=s+f();
    printf("%d\n",s);
    return 0;
}