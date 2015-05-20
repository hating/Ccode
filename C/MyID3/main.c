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

double val_entropy(NodeSample *head)
{
		AAA Ahead,*Atemp=NULL;
		int dataCnt=0;
	//Initiation
		Ahead.next=NULL;
		Ahead.Yes=0;
		Ahead.No=0;
		strcpy(Ahead.att,"\0");
	
		for(NodeSample *iter=head->next;iter!=NULL;iter=iter->next)
		{
			
					if(!strcmp(iter->sample.playTennis,"Yes"))
					{
						Ahead.Yes++;
					}
					if(!strcmp(iter->sample.playTennis,"No"))
					{
						Ahead.No++;
					}
			dataCnt++;
		}
	//Test the read result
	printf("Yes:%d\tNo:%d\n",Ahead.Yes,Ahead.No);
	double I=0.0;
	I=-1.0*Ahead.Yes/dataCnt*lg2(1.0*Ahead.Yes/dataCnt)-1.0*Ahead.No/dataCnt*lg2(1.0*Ahead.No/dataCnt);
	printf("%f\n",I);
	return I;
};
int att_val(char branchs[][20],NodeSample *head,char *attrid)
{
	int X=99,i=0;;
	if(!strcmp(attrid,"Outlook")) X=0;
	if(!strcmp(attrid,"Temperature")) X=1;
	if(!strcmp(attrid,"Humidity")) X=2;
	if(!strcmp(attrid,"Windy")) X=3;
	
	for(NodeSample *iter=head->next;iter!=NULL;iter=iter->next)
	{
		
		for(i=0;branchs[i][0]!='\0';i++)
		{
			if(!strcmp(iter->sample.item[X],branchs[i]))
			{
				break;
			}
		}
		if(branchs[i][0]=='\0')
		{
			strcpy(branchs[i],iter->sample.item[X]);
			i++;
		}
	}
	return i;	
}

double att_entropy(int loop,NodeSample *head)//Pass the name of the attribute,and my data.
{
	//Something maybe added to here. ( att_val(att,data) )
//	char val[4][LENGTH];
//	att_val(att,head,val);
//	NodeSample new_data;
//	double I=0.0,Val_E=0.0;
//	double 	P_each[4]={0},P_all[4]={0};
//	for(int loop=0;loop<4;loop++)
//	{
		double I=0.0;
		AAA Ahead,*Atemp=NULL;
		int dataCnt=0;
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
			dataCnt++;
		}
	//Test the read result
		
		for(AAA *iter_print=Ahead.next;iter_print!=NULL;iter_print=iter_print->next)
		{
			printf("attribute:%s\nYes:%d\nNo:%d\n",iter_print->att,iter_print->Yes,iter_print->No);
		}
		
		for(AAA *iter_calc=Ahead.next;iter_calc!=NULL;iter_calc=iter_calc->next)
		{
			I-=iter_calc->Yes* lg2( 1.0*iter_calc->Yes/(iter_calc->Yes+iter_calc->No) ) + iter_calc->No *lg2( 1.0*iter_calc->No/(iter_calc->Yes+iter_calc->No) );
		}
//	}
	
	
//	for(int i=0;i<4;i++)
//	{
//		P_each[i]/=14;
		printf("%f\n",I/dataCnt);
//	}
	return  I/dataCnt;
}
NodeSample *pick_items(char *attrid,char *branchs,NodeSample *head)
{
	int i=0,X=99;
	if(!strcmp(attrid,"Outlook")) X=0;
	if(!strcmp(attrid,"Temperature")) X=1;
	if(!strcmp(attrid,"Humidity")) X=2;
	if(!strcmp(attrid,"Windy")) X=3;
	
	NodeSample *new_head=(NodeSample *)malloc(sizeof(NodeSample));
	NodeSample *iter_node=new_head;
	
	for(NodeSample* iter=head->next;iter!=NULL;iter=iter->next)
	{
		if(!strcmp(iter->sample.item[X],branchs))
		{
			NodeSample *node=(NodeSample *)malloc(sizeof(NodeSample));
			node->sample.number=0;
			for(int i=0;i<4;i++)
			{
				strcpy(node->sample.item[i],iter->sample.item[i]);	
			}
			strcpy(node->sample.playTennis,iter->sample.playTennis);
			node->next=NULL;
			iter_node->next=node;
			iter_node=node;
		}
	}
	return new_head;
}

Tree_Node ID3(NodeSample *head)
{
	Tree_Node tree,tree_temp;
	char attrid[4][20]={"Outlook","Temperature","Humidity","Windy"};
	double entropy=val_entropy(head);
	double gain,Att_E,temp=0.0;
	//Initiation
	strcpy(tree.attrid,"UNKNOWN");
	strcpy(tree.attrvalue,"UNKNOWN");
	strcpy(tree.Yes_or_No,"UNKNOWN");
	tree.childNode[0]=NULL;
	tree.childNode[1]=NULL;
	tree.childNode[2]=NULL;
	tree.childNode[3]=NULL;
	
	for(int i=0;i<4;i++)
	{
		tree.childNode[i]=NULL;
	}
	
	for(int i=0;i<4;i++)
	{
		Att_E=att_entropy(i,head);
		gain=entropy-Att_E;
		if(gain>temp)
		{
			temp=gain;
			strcpy(tree.attrid,attrid[i]);
		}
	}
	if(strcmp(tree.attrid,"UNKNOWN"))
	{
		char branchs[4][20]={"\0","\0","\0","\0",};
		int numberLoop=att_val(branchs,head,tree.attrid)+1;//Ѱ���ڸ�attribute���ж����ֲ�ͬ������ 
		for(int i=0;i<numberLoop;i++)
		{
			NodeSample *new_head=pick_items(tree.attrid,branchs[i],head);
			printf("\n****************\n");
			tree_temp=ID3(new_head);
			for(int i=0;i<4;i++)//������ӽڵ� 
			{
				if(tree.childNode[i]==NULL)
				{
					tree.childNode[i]=&tree_temp;
					break;
				}
			}
		}
	}
	
	else
	{
		printf("\n***************\n");
		strcpy(tree.attrid,"Leaf");
		strcpy(tree.Yes_or_No,head->next->sample.playTennis);
	}
	return tree;
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
void printResult(Tree_Node *Result)
{
	printf("Yes_or_No:%s\n",Result->Yes_or_No);
	printf("attrid:%s\n",Result->attrid);
	printf("attrvalue:%s\n",Result->attrvalue);
	printf("\n\n");
	for(int i=0;i<4&&Result->childNode[i]!=NULL;i++)
	{
		printResult(Result->childNode[i]);
	}
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
	Tree_Node Result=ID3(&head);
	Tree_Node *pResult=&Result;
	printResult(pResult);
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
