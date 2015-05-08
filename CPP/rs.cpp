#include <stdio.h>
int main ()
{
	int a,r,s;
	scanf("%d",&a);
	char *rr[]={
	"unreadable",
	"barely readable, occasional words distinguishable",
	"readable with considerable difficulty",
	"readable with practically no difficulty",
	"perfectly readable"};
	char *ss[]={
	"Faint signals, barely perceptible",
	"Very weak signals",
	"Weak signals",
	"Fair signals",
	"Fairly good signals",
	"Good signals",
	"Moderately strong signals",
	"Strong signals",
	"Extremely strong signals",} ;
	s=a%10;
	a/=10;
	printf("%s, %s.",*(ss+s-1),*(rr+a-1));
	return 0;
	
} 
