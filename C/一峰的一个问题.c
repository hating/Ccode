#include<stdio.h>
#include<math.h>
int main()
{
	float x,m,n,a;
	printf("请输入一个正数：");
	scanf("%f",&x);
	while(fabs(m-n)>=0.00001)
	{
		n=x;
		m=n+a/n;
		x=(1/2)*m;
	}
	printf("平方根为：");
	printf("%8.6f\n",x);
	return 0;
}

