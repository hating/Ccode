#include<stdio.h>
#include<math.h>
int main()
{
	float x,m,n,a;
	printf("Please input a int:");
	scanf("%f",&x);
//	while(fabs(m-n)>=1e-5)
//	{
//		n=x;
//		m=n+a/n;
//		x=(1/2)*m;
//	}
	do{
		n=x;
		m=n+x/n;
		x=0.5*m;		
	} while(fabs(m-n)>=0.00001);
	printf("The result is:");
	printf("%8.6f\n",x);
	return 0;
}
