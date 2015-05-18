#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "id3.h"

double lg2(double n)
{
	double l=log(n)/log(2);
	if(l<-10000)
	{
		l=0;
	}
    return l;
}

AAA *addNodeAAA(AAA *Ahead,char *s)
{
	AAA *node=(AAA *)malloc(sizeof(AAA));
//Initiliation
	strcpy(node->att,s);
	node->Yes=0;
	node->No=0;
	node->next=NULL;
	if(Ahead->next==NULL)
	{
		Ahead->next=node;
	}
	else 
	{
		AAA *iter=Ahead->next;
		for(;iter->next!=NULL;iter=iter->next)
		{
			;
		}
		iter->next=node;
	}
	return node;
}
AAA *find(char *compare,AAA *source)
{
	
	for(AAA *iterInFind=source;iterInFind!=NULL;iterInFind=iterInFind->next)
	{
		if(!strcmp(compare,iterInFind->att))
		{
			return iterInFind;
		}
	}
	return NULL;
}

void ID3(NodeSample *head)
{
	double 	P_each[4]={0},P_all[4]={0};
	for(int loop=0;loop<4;loop++)
	{
		AAA Ahead,*Atemp=NULL;
		
	//Initiation
		Ahead.next=NULL;
		Ahead.Yes=0;
		Ahead.No=0;
		strcpy(Ahead.att,"\0");
	
		for(NodeSample *iter=head->next;iter!=NULL;iter=iter->next)
		{
			if(Atemp=find(iter->sample.item[loop],&Ahead))
			{
					if(!strcmp(iter->sample.playTennis,"Yes"))
					{
						Atemp->Yes++;
					}
					if(!strcmp(iter->sample.playTennis,"No"))
					{
						Atemp->No++;
					}
			}
			else
			{
					Atemp=addNodeAAA(&Ahead,iter->sample.item[loop]);
	
					if(!strcmp(iter->sample.playTennis,"Yes"))
					{
						Atemp->Yes++;
					}
					if(!strcmp(iter->sample.playTennis,"No"))
					{
						Atemp->No++;
					}
				
			}
		}
	//Test the read result
		
		for(AAA *iter_print=Ahead.next;iter_print!=NULL;iter_print=iter_print->next)
		{
			printf("attribute:%s\nYes:%d\nNo:%d\n",iter_print->att,iter_print->Yes,iter_print->No);
//			P_each[loop]-=(double)iter_print->Yes*lg2((double)iter_print->Yes/(iter_print->Yes+iter_print->No))/(iter_print->Yes+iter_print->No)+
//							(double)iter_print->No*lg2((double)iter_print->No/(iter_print->Yes+iter_print->No))/(iter_print->Yes+iter_print->No);
		}
//		printf("%f\n\n",P_each[loop]);

		//��ֵ�ļ��㣬�ⲿ��Ҫ�ع��� 
	}

}


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
		printf("û�д�%s�ҵ�ƥ������ݣ����򼴽��˳���\n",file);
		exit(1);
	}
	head.next=&sample[0];
	for(int i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("����%s�ҵ�%d�����ݡ�\n\n",file,number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		printf("��ţ�%d\n",iter->sample.number);
		printf("������%s\n",iter->sample.item[0]);
		printf("�¶ȣ�%s\n",iter->sample.item[1]);
		printf("ʪ�ȣ�%s\n",iter->sample.item[2]);
		printf("������%s\n",iter->sample.item[3]);
		printf("�Ƿ����ë��%s\n\n",iter->sample.playTennis);		
		iter=iter->next;
	}	
	

}
void inputDrillSample(void)
{
//	printf("This is function inputDrillSample,it is HALF completed\n");
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
//		printf("��ţ�");
//		scanf("%d",&sample[i].sample.number); 
		sample[i].sample.number=i+1;
		printf("����(Sunny\\Overcast\\Rain)��");
		scanf("%s",sample[i].sample.item[0]);
		printf("�¶�(Hot\\Mild\\Cool)��");
		scanf("%s",sample[i].sample.item[1]);
		printf("ʪ��(High\\Normal)��");
		scanf("%s",sample[i].sample.item[2]);
		printf("����(Strong\\Weak)��");
		scanf("%s",sample[i].sample.item[3]);
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
		sample[i].sample.number=i+1;
		printf("����(Sunny\\Overcast\\Rain)��");
		scanf("%s",sample[i].sample.item[0]);
		printf("�¶�(Hot\\Mild\\Cool)��");
		scanf("%s",sample[i].sample.item[1]);
		printf("ʪ��(High\\Normal)��");
		scanf("%s",sample[i].sample.item[2]);
		printf("����(Strong\\Weak)��");
		scanf("%s",sample[i].sample.item[3]);
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
	FILE *stream;
	stream=fopen("drill.dat","r");
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
	
	printf("����drill.dat�ҵ�%d�����ݡ�\n",number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		iter=iter->next;
	}
	ID3(&head);
}
void showTestResult(void)
{
	printf("This is function showTestResult,it is not yeat completed\n");
	//Unfinished		
}
void statistics(void)
{
	FILE *stream;
	stream=fopen("drill.dat","r");
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

	printf("There are %d items in drill.dat.\n",number/sizeof(struct Sample));
	stream=fopen("test.dat","r");
	if(stream==NULL)
	{
		printf("�ļ�δ�ܴ򿪣����򼴽��˳���\n");
		exit(1);
	}
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);	
	printf("There are %d items in test.dat.\n",number/sizeof(struct Sample));

}
void exitProgram(void)
{
	printf("You terminated the program.See ya!\n");
	exit(1);
}

int main(int argc, char** argv) 
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
	return 0;
}
