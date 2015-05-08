#include<stdio.h>
int main()
{
int power(int x,int y);
int sum,x,y;
printf("input x^y:");
scanf("x=%d,y=%d",&x,&y);
sum=power(x,y);
printf("%d^%d=%d\n",x,y,sum);
return 0;
}

int power(int x,int y)
{int sum;
if(y==1)
sum=x;
else
sum=x*power(x,y-1);
return sum;
}

