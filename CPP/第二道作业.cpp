#include <stdio.h>
#define ARRAYX 3
#define ARRAYY 4
void input(int array[][ARRAYY],int x,int y)
{
	printf("Please input %d lines of number,each line contains %d numbers.\n",x,y);
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			scanf("%d",&array[i][j]);
		}
	}
	//Need a output to ensure the input is right.
}
void search(int array[][ARRAYY],int x,int y)
{
	int max=array[0][0],min=array[0][0],minX=0,minY=0,maxX=0,maxY=0;
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			if(max<array[i][j])
			{
				max=array[i][j];
				maxX=j;
				maxY=i;
			}
			if(min>array[i][j])
			{
				min=array[i][j];
				minX=j;
				minY=i;
			}
		}
	}
	printf("The max nmuber is %d .It is located at the %d lines and the %d number.\n",max,maxY,maxX);
	printf("The min nmuber is %d .It is located at the %d lines and the %d number.\n",min,minY,minX);
}
int main()
{
	int array[ARRAYX][ARRAYY];
	input(array,ARRAYX,ARRAYY);
	search(array,ARRAYX,ARRAYY);
	
	
}
