#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int n=10, d[11];
int main(){
    int i, j,t;
    srand((unsigned int)time(NULL));
    for(i=1;i<=n;i++){
        d[i]=rand()%n+1;
    }
    for(i=1;i<=n;i++){
        printf("%d ",d[i]);
    }
    printf("\n");
    for(i=0;i<n;i++){
        for(j=2;j<=n;j++){
            if(d[j]<d[j-1]){
                t=d[j-1];
                d[j-1]=d[j];
                d[j]=t;
            }
        }
    }
    for(i=1;i<=n;i++){
        printf("%d ",d[i]);
    }
}