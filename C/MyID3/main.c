#include <iostream>
#include "id3.h"

void interface(void)
{
	printf("********************************\n");	
	printf("1-------------ѵ������¼��\n");
	printf("2-------------��������¼��\n");
	printf("3-------------������ʾ\n");
	printf("4-------------���Խ����ʾ\n");
	printf("5-------------ͳ��\n");	
	printf("6-------------�˳�\n");
	printf("********************************\n");
}


void inputDrillSample(void)
{
	printf("This is function inputDrillSample,it is not yeat completed\n");
	//Unfinished
}
void inputTestSample(void)
{
	printf("This is function inputTestSample,it is not yeat completed\n");
	//Unfinished	
}
void showRules(void)
{
	printf("This is function showRules,it is not yeat completed\n");
	//Unfinished		
}
void showTestResult(void)
{
	printf("This is function showTestResult,it is not yeat completed\n");
	//Unfinished		
}
void statistics(void)
{
	printf("This is function statistics,it is not yeat completed\n");
	//Unfinished		
}
void exitProgram(void)
{
	printf("You terminated the program.See ya!\n");
	exit(1);
}


void functionChoose(void)
{
loop:
	int choose=0;
	scanf("%d",&choose);
	switch (choose)
	{
		case 1:
			inputDrillSample();
			break;
		case 2:
			inputTestSample();
			break;
		case 3:
			showRules();
			break;
		case 4:
			showTestResult();
			break;
		case 5:
			statistics();
			break;
		case 6:
			exitProgram();
			break;
		default:
			printf("There is something wrong with your number,please input again:\n");
	}
	goto loop;
}


int main(int argc, char** argv) {
	interface();
	functionChoose();
	
	return 0;
}
