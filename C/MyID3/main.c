#include <stdio.h>
#include <stdlib.h>
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
	printf("This is function inputDrillSample,it is HALF completed\n");
	//Unfinished
	FILE * fp=NULL ;
	fp=fopen("drill.dat","a+");
	if(fp==NULL)
	{
		printf("û���ҵ�drill.dat�����򼴽��˳���\n");
		getchar();
		exit(1);
	}
	if(fp!=NULL)
	{
		printf("�ɹ����ļ���\n");
	}
	int number=0;
	printf("����������Ҫ���������������\n");
	loop:
	scanf("%d",&number);
	if(number==0)
	{
		printf("������������������:\n");
		goto loop;
	}
	NodeSample head;
	NodeSample sample[number];
	head.next=&sample[0];	
//��һ���汾�����������ݵļ�� 
	for(int i=0;i<number;i++)//����¼�뵽�ڴ���,���������� 
	{
		printf("����������ǵ� %d ������:\n",i+1);
		printf("��ţ�");
		scanf("%d",&sample[i].sample.number); 
		printf("����(Sunny\\Overcast\\Rain)��");
		scanf("%s",sample[i].sample.outlook);
		printf("�¶�(Hot\\Mild\\Cool)��");
		scanf("%s",sample[i].sample.temperate);
		printf("ʪ��(High\\Normal)��");
		scanf("%s",sample[i].sample.humidity);
		printf("����(Strong\\Weak)��");
		scanf("%s",sample[i].sample.wind);
		printf("�Ƿ�������(Yes\\No)��");
		scanf("%s",sample[i].sample.playTennis);
		if(i<number-1)
		{
			sample[i].next=&sample[i+1];
		}
	}
 
	for(NodeSample* iter=head.next;iter!=NULL;iter=iter->next)//���ļ�¼�뵽�ļ���ȥ 
	{
		fwrite(&iter->sample,sizeof(iter->sample),1,fp);
	}
	//Write
	printf("�ļ�¼����ɣ�\n");
	fclose(fp);
	interface();
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
//Bug:��������ַ��ͻ�����ѭ�����������scanf��䡣 
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
			break;
	}
	goto loop;
}


int main(int argc, char** argv) {
	interface();
	functionChoose();
	
	return 0;
}
