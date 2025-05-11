#include <stdio.h>
int n,m,d[20][20],dt[20][20];
int main(){
    scanf("%d %d",&n, &m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&d[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dt[i][j]=d[i][j]+dt[i-1][j]+dt[i][j-1]-dt[i-1][j-1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            printf("%d ",dt[i][j]);
            printf("\n");
    }
    return 0;
}