#include <stdio.h>
int d[7];
int main(){
    int n, t;
    printf("num: ");
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&t);
        d[t]+=1;
    }
    for(int i=1;i<=6;i++)
    printf("%d  ",d[i]);
    printf("\n");
    return 0;
}