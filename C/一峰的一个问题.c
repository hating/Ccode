#include<stdio.h>
#include<math.h>
int main()
{
	int a;
	double b,c;
	scanf("%d",&a);
	b=1,c=0;
	for(;fabs(b-c)>=1e-5;)
	{
	    c=1.0/2*(b+a*1.0/b);
	    b=1.0/2*(c+a*1.0/c);
	}
	printf("%lf,%lf",c,b);
	return 0;
}

#include<stdio.h>
#include<math.h>
int main()
{
	float x=0,m=0,n=0,a;
	printf("������һ��������");
	scanf("%f",&a);
	do
	{
		n=x;
		m=n+a/n;
		x=(1/2)*m;
	}while(fabs(m-n)>=1e-5);
	printf("ƽ����Ϊ��");
	printf("%8.6f\n",x);
	return 0;
}
