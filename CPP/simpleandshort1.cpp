#include<stdio.h>
int max(int x,int y);//这里是函数声明 
int main()
{
int a,b,c;
scanf("%d,%d",&a,&b);//注意，你之前的代码 scanf("%d,%d,&a,&b");你看看错在哪 
c=max(a,b);
printf("max=%d\n",c);
return 0;
}

int max(int a,int b) //这部分是判断哪个大的函数，思路很简单 
{
	int max=a;// 
	if(b>a)
	{
		max=b;
	} 
	return max;
} 
