#include <stdio.h>
int function()
{
	    float fnum;
	    double dnum;
	    int i,j,model;
	    int dsize = sizeof(double),fsize = sizeof(float);
	    char *pc,ch;
	    printf("������һ��ʵ����");
	    scanf("%lf",&dnum);
	
	    fnum = (float)dnum;
	    printf("double�͵�%lf���ڴ��д洢���£�\n",dnum);
	    pc = (char *)&dnum + dsize - 1;
	    for(i = 0; i < dsize; ++i,--pc) {
	    for(j = 0; j < 8; ++j)
	        printf("%d",(*pc >> (8 - 1 - j)) & 1);
	    printf(",");
	    }
	    printf("\b \n\n");
	    fnum = (float)dnum;
	    printf("float�͵�%f���ڴ��д洢���£�\n",fnum);
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
	char marker=0;
	while(1){
		printf("�Ƿ�������򣿣�y/n��\n"); 
		if(marker=='y'){
			return 1;
		}
		else if(marker=='n'){
			printf("����\n");
			return 0;
		}
		printf("Debug\n");
		{
			printf("ֻ������y��n\n");
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

