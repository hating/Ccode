#include<stdio.h>
int max(int x,int y);//�����Ǻ������� 
int main()
{
int a,b,c;
scanf("%d,%d",&a,&b);//ע�⣬��֮ǰ�Ĵ��� scanf("%d,%d,&a,&b");�㿴�������� 
c=max(a,b);
printf("max=%d\n",c);
return 0;
}

int max(int a,int b) //�ⲿ�����ж��ĸ���ĺ�����˼·�ܼ� 
{
	int max=a;// 
	if(b>a)
	{
		max=b;
	} 
	return max;
} 
