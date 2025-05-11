#include<stdio.h>
struct point{
    int x;
    int y;
};
int main(){
    point p1,p2;
    int d=0;
    scanf("%d%d",&p1.x,&p1.y);
    scanf("%d%d",&p2.x,&p2.y);
    d+=(p1.x>p2.x)?(p1.x-p2.x):(p2.x-p1.x);
    d+=(p1.y>p2.y)?(p1.y-p2.y):(p2.y-p1.y);
    printf("%d\n",d);
    return 0;
}