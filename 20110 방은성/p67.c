#include <stdio.h>
int i, n;
int main(){
    scanf("%d",&n);
    for(i=2;i<n;i++){
        if(n%i!=0)
        continue;
        else
        break;
    }
    printf("%s\n",i==n?"prime":"composite");
    return 0;
