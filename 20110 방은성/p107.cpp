#include<stdio.h>
int n;
int f(int k){
int s=0;
for(int i=1;i<=k;i++)
s+=i;
return s;
}
int main(){
    int res;
    scanf("%d",&n);
    res=f(n);
    printf("%d\n",res);
}