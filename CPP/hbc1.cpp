#include<stdio.h>
int main()
{
	int fac(int n);
	int m;
	double sum=0;
	for(m=1;(1.0/fac(m))>=0.00001;m++)
	{
		sum+=1.0/fac(m);
	}
	printf("The sum is %f\n",sum);
	return 0;
}
int fac(int n)
{
 int s,i;
 if(n<0)
 printf("error.Please enter an integer number.");
 if(n==0||n==1)
 s=1;
 else 
	 for(i=1,s=1;i<=n;i++)
		 s=s*i;
 return s;
}

