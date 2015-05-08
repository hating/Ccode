#include <stdio.h>
int function()
{
	    float fnum;
	    double dnum;
	    int i,j,model;
	    int dsize = sizeof(double),fsize = sizeof(float);
	    char *pc,ch;
	    printf("请输入一个实数：");
	    scanf("%lf",&dnum);
	
	    fnum = (float)dnum;
	    printf("double型的%lf在内存中存储如下：\n",dnum);
	    pc = (char *)&dnum + dsize - 1;
	    for(i = 0; i < dsize; ++i,--pc) {
	    for(j = 0; j < 8; ++j)
	        printf("%d",(*pc >> (8 - 1 - j)) & 1);
	    printf(",");
	    }
	    printf("\b \n\n");
	    fnum = (float)dnum;
	    printf("float型的%f在内存中存储如下：\n",fnum);
	    pc = (char *)&fnum + fsize - 1;
	    for(i = 0; i < fsize; ++i,--pc) {
	    for(j = 0; j < 8; ++j)
	        printf("%d",(*pc >> (8 - 1 - j)) & 1);
	    printf(",");
	    }
	    printf("\b \n\n");
	return 0;
}
int check(void)
{
	char input=0;
	while(1){
		printf("是否继续程序？（y/n）\n"); 
		scanf("%c",&input);
		if(input=='y'){
			return 1;
		}
		else if(input=='n'){
			return 0;
		}
		else {
			printf("只能输入y或n\n");
		}
	}
}

int main() 
{ while(check()==1)
	{
	function();
	}	
	return 0;
}

