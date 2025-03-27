#include<stdio.h>
int main(){
	int score;
	scanf("%d",&score);
	if (score>=90) printf("A\n");
	else if(score>=80){ printf("B\n");}
	else if(score>=70){ printf("C\n");}
	else { printf("D\n");}
	return 0;	
}
 
