#include <stdio.h>
int n, d[20][20];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&d[i][j]);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        printf("%d",d[i][j]);
        printf("\n");
    }
    return 0;
}