#include<stdio.h>
int main(){
	double x1,y1,r1,x2,y2,r2;
	double d;
	scanf("%lf %lf %lf",&x1,&y1,&r1);
	scanf("%lf %lf %lf",&x2,&y2,&r2);
	d=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	if (d<=(r1+r2)*(r1+r2))printf("overlapped\n");
	else printf("not overlapped\n");
	return 0;
}
