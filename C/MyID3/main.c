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

Tree_Node *ID3(NodeSample *head)
{
	Tree_Node *tree=(Tree_Node *)malloc(sizeof(Tree_Node)),*tree_temp=(Tree_Node *)malloc(sizeof(Tree_Node));
	char attrid[4][20]={"Outlook","Temperature","Humidity","Windy"};
	double entropy=val_entropy(head);
	double gain,Att_E,temp=0.0;
	//Initiation
	strcpy(tree->leaf,"false");
	strcpy(tree->root,"root");
//	strcpy(tree->attrvalue,"UNKNOWN");
	tree->childNode[0]=NULL;
	tree->childNode[1]=NULL;
	tree->childNode[2]=NULL;
	tree->childNode[3]=NULL;
	
	for(int i=0;i<4;i++)
	{
		strcpy(tree->branch_name[i],"UNKNOWN");
		tree->childNode[i]=NULL;
	}
	
	for(int i=0;i<4;i++)
	{
		Att_E=att_entropy(i,head);
		gain=entropy-Att_E;
		if(gain>temp)
		{
			temp=gain;
			strcpy(tree->root,attrid[i]);
		}
	}
	if(strcmp(tree->root,"root"))
	{
		char branchs[4][20]={"\0","\0","\0","\0",};
		int numberLoop=att_val(branchs,head,tree->root)+1;//寻找在该attribute中有多少种不同的属性 
		for(int loop=0;loop<numberLoop;loop++)
		{
			NodeSample *new_head=pick_items(tree->root,branchs[loop],head);
			printf("\n****************\n");
			tree_temp=ID3(new_head);
			for(int i=0;i<4;i++)//插入儿子节点 
			{
				if(tree->childNode[i]==NULL)
				{
//					Branch *branch=(Branch *)malloc(sizeof(Branch));
					strcpy(tree->branch_name[loop],branchs[loop]);
//					strcpy(branch->branch_name,branchs[loop]);
//					branch->childNode=tree_temp;
					tree->childNode[loop]=tree_temp;
					break;
				}
			}
		}
	}
	
	else
	{
//		printf("\n***************\n");
		strcpy(tree->leaf,"true");
		strcpy(tree->root,head->next->sample.playTennis);
	}
	return tree;
}


void interface(void) 
{
	printf("********************************\n");	
	printf("1-------------训练样本录入\n");
	printf("2-------------测试样本录入\n");
	printf("3-------------规则集显示\n");
	printf("4-------------测试结果显示\n");
	printf("5-------------统计\n");	
	printf("6-------------训练样本显示\n");	
	printf("7-------------测试样本显示\n");	
	printf("8-------------退出\n");
	printf("********************************\n\n");
}

void readDrillorTestSample(char *file)
{
	FILE *stream;
	stream=fopen(file,"r");
	if(stream==NULL)
	{
		printf("文件未能打开，程序即将退出。\n");
		exit(1);
	}
//获取文件的长度 
	int number;
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);//将文件定位到文件头	


	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("没有从%s找到匹配的数据，程序即将退出。\n",file);
		exit(1);
	}
	head.next=&sample[0];
	for(int i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("共从%s找到%d份数据。\n\n",file,number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		printf("编号：%d\n",iter->sample.number);
		printf("天气：%s\n",iter->sample.item[0]);
		printf("温度：%s\n",iter->sample.item[1]);
		printf("湿度：%s\n",iter->sample.item[2]);
		printf("风力：%s\n",iter->sample.item[3]);
		printf("是否打羽毛球：%s\n\n",iter->sample.playTennis);		
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
		printf("没有找到drill.dat，程序即将退出！\n");
		getchar();
		exit(1);
	}
	if(fp!=NULL)
	{
		printf("成功打开文件！\n");
	}
	int number=0;
	printf("请输入你需要输入的数据数量：\n");
	loop:
	scanf("%d",&number);
	if(number==0)
	{
		printf("输入有误，请重新输入:\n");
		goto loop;
	}
	NodeSample head;
	NodeSample sample[number];
	head.next=&sample[0];	
//下一个版本进行输入数据的检测 
	for(int i=0;i<number;i++)//数据录入到内存中,并建立链表 
	{
		printf("现在输入的是第 %d 份数据:\n",i+1);
//		printf("编号：");
//		scanf("%d",&sample[i].sample.number); 
		sample[i].sample.number=i+1;
		printf("天气(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.item[0]);
		printf("温度(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.item[1]);
		printf("湿度(High\\Normal)：");
		scanf("%s",sample[i].sample.item[2]);
		printf("风力(Strong\\Weak)：");
		scanf("%s",sample[i].sample.item[3]);
		printf("是否玩网球(Yes\\No)：");
		scanf("%s",sample[i].sample.playTennis);
		if(i<number-1)
		{
			sample[i].next=&sample[i+1];
		}
	}
 
	for(NodeSample* iter=head.next;iter!=NULL;iter=iter->next)//将文件录入到文件中去 
	{
		fwrite(&iter->sample,sizeof(iter->sample),1,fp);
	}
	//Write
	printf("文件录入完成！\n");
	fclose(fp);
}
void inputTestSample(void)
{
	
	printf("This is function inputTestSample,it is not yeat completed\n");
	FILE * fp=NULL ;
	fp=fopen("test.dat","a+");
	if(fp==NULL)
	{
		printf("没有找到test.dat，程序即将退出！\n");
		getchar();
		exit(1);
	}
	if(fp!=NULL)
	{
		printf("成功打开文件！\n");
	}
	int number=0;
	printf("请输入你需要输入的数据数量：\n");
	loop:
	scanf("%d",&number);
	if(number==0)
	{
		printf("输入有误，请重新输入:\n");
		goto loop;
	}
	NodeSample head;
	NodeSample sample[number];
	head.next=&sample[0];	
//下一个版本进行输入数据的检测 
	for(int i=0;i<number;i++)//数据录入到内存中,并建立链表 
	{
		printf("现在输入的是第 %d 份数据:\n",i+1);
		sample[i].sample.number=i+1;
		printf("天气(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.item[0]);
		printf("温度(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.item[1]);
		printf("湿度(High\\Normal)：");
		scanf("%s",sample[i].sample.item[2]);
		printf("风力(Strong\\Weak)：");
		scanf("%s",sample[i].sample.item[3]);
		strcpy(sample[i].sample.playTennis,"UNKNOWN");
		if(i<number-1)
		{
			sample[i].next=&sample[i+1];
		}
	}
 
	for(NodeSample* iter=head.next;iter!=NULL;iter=iter->next)//将文件录入到文件中去 
	{
		fwrite(&iter->sample,sizeof(iter->sample),1,fp);
	}
	//Write
	printf("文件录入完成！\n");
	fclose(fp);
	interface();	
}
void printResult(Tree_Node *Result,int num)
{
//	printf("\n");
//	printf("root:%s\n",Result->root);
//	printf("isleaf:%s\n",Result->leaf);
//	for(int i=0;i<4&&Result->childNode[i]!=NULL;i++)
//	{
//		printf("Fatheris:%s\nBranchs:%s\n",Result->root,Result->branch_name);
//		printResult(Result->childNode[i]);
//	}
//	static int num=0;
	char temp[20]="      ";
	if(!strcmp(Result->leaf,"true"))
	{
		for(int i=0;i!=2+num;i++)
		{
			printf("%s",temp);
		}
		printf("+----Leaf:%s\n",Result->root);
	}
	else
		{
			for(int i=0;i!=0+num;i++)
			{
				printf("%s",temp);
				
			}
			printf("+---Attribute:%s\n",Result->root);
			for(int i=0;Result->childNode[i]!=NULL;i++)
			{
				for(int itemp=0;itemp!=1+num;itemp++)
				{
					printf("%s",temp);
				}
				printf("+---Branch:%s\n",Result->branch_name[i]);
				printResult(Result->childNode[i],num+2);
			}
		}
}
void showRules(void)

{
	FILE *stream;
	stream=fopen("drill.dat","r");
	if(stream==NULL)
	{
		printf("文件未能打开，程序即将退出。\n");
		exit(1);
	}
//获取文件的长度 
	int number;
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);//将文件定位到文件头	


	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("没有从drill.dat找到匹配的数据，程序即将退出。\n");
		exit(1);
	}
	head.next=&sample[0];
	for(int i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("共从drill.dat找到%d份数据。\n",number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		iter=iter->next;
	}
	Tree_Node *Result=ID3(&head);
//	Tree_Node *pResult=&Result;
	printResult(Result,0);
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
		printf("文件未能打开，程序即将退出。\n");
		exit(1);
	}
//获取文件的长度 
	int number;
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);

	printf("There are %d items in drill.dat.\n",number/sizeof(struct Sample));
	stream=fopen("test.dat","r");
	if(stream==NULL)
	{
		printf("文件未能打开，程序即将退出。\n");
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
<<<<<<< HEAD
	choose=getchar();
	switch (ch
			{
				printf("The tree is not built yet. Please run function 3 first.\n");
			}
			showTestResult(tree);
=======
//Bug:如果输入字符就会无限循环，不会进入scanf语句。 
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
>>>>>>> parent of adfee2e... Changing language to English.
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
