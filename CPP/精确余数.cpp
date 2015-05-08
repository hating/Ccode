#include <stdio.h>
int main ()
{
	int a[200];
	for(int i=0;i<200;i++)
	{
		a[i]=-1;
	} 
	//对数组a进行初始化
	int up=0,down=0;
	scanf("%d/%d",&up,&down);
	for(int i=0;i<200;i++){
		
		 up*=10;//将分子乘以10，使得分子大于分母 
		 a[i]=up/down;//将up中大于down的部分提出来
		 up=up%down;//使上一步的余数取出来，成为up
		 if(!up)break; 
	}//可以了，全部都过了 
	printf("0.");
	for(int i=0;i<200;i++){
		if(a[i]==-1){
			break;
		}
		printf("%d",a[i]);
		
	} //这一段是输出程序
	printf("\n");//题目要求的回车
	return 0; 
}
