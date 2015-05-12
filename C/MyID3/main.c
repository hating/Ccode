#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id3.h"

void interface(void)
{
	printf("********************************\n");	
	printf("1-------------ѵ������¼��\n");
	printf("2-------------��������¼��\n");
	printf("3-------------������ʾ\n");
	printf("4-------------���Խ����ʾ\n");
	printf("5-------------ͳ��\n");	
	printf("6-------------ѵ��������ʾ\n");	
	printf("7-------------����������ʾ\n");	
	printf("8-------------�˳�\n");
	printf("********************************\n\n");
}

void readDrillorTestSample(char *file)
{
	FILE *stream;
	stream=fopen(file,"r");
	if(stream==NULL)
	{
		printf("�ļ�δ�ܴ򿪣����򼴽��˳���\n");
		exit(1);
	}
//��ȡ�ļ��ĳ��� 
	int number;
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);//���ļ���λ���ļ�ͷ	


	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("û�д�drill.dat�ҵ�ƥ������ݣ����򼴽��˳���\n");
		exit(1);
	}
	head.next=&sample[0];
	for(int i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("����drill.dat�ҵ�%d�����ݡ�\n\n",number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		printf("��ţ�%d\n",iter->sample.number);
		printf("������%s\n",iter->sample.outlook);
		printf("�¶ȣ�%s\n",iter->sample.temperate);
		printf("ʪ�ȣ�%s\n",iter->sample.humidity);
		printf("������%s\n",iter->sample.wind);
		printf("�Ƿ����ë��%s\n\n",iter->sample.playTennis);		
		iter=iter->next;
	}	
	

}
void inputDrillSample(void)
{
	printf("This is function inputDrillSample,it is HALF completed\n");
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
}
void inputTestSample(void)
{
	printf("This is function inputTestSample,it is not yeat completed\n");
	//Unfinished
	FILE * fp=NULL ;
	fp=fopen("test.dat","a+");
	if(fp==NULL)
	{
		printf("û���ҵ�test.dat�����򼴽��˳���\n");
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
//		printf("�Ƿ�������(Yes\\No)��");
//		scanf("%s",sample[i].sample.playTennis);
		strcpy(sample[i].sample.playTennis,"UNKNOWN");
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
	interface();
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
			readDrillorTestSample("drill.dat");
			break;
		case 7:
			readDrillorTestSample("test.dat");
			break;
		case 8:
			exitProgram();
			break;
		default:
			printf("There is something wrong with your number,please input again:\n");
			break;
	}
	goto loop;
}


int main(int argc, char** argv) {
	functionChoose();
	
	return 0;
}
