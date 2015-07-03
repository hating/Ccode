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

/**
Initiliation
**/
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
	AAA *iterInFind=source;
	for(iterInFind=source;iterInFind!=NULL;iterInFind=iterInFind->next)
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

		AAA Ahead;
		NodeSample *iter=NULL;
		int dataCnt=0;
		double I=0.0;
/**
	//Initiation
**/
		Ahead.next=NULL;
		Ahead.Yes=0;
		Ahead.No=0;
		strcpy(Ahead.att,"\0");
		iter=head->next;
		for(iter=head->next;iter!=NULL;iter=iter->next)
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
	I=0.0;
	I=-1.0*Ahead.Yes/dataCnt*lg2(1.0*Ahead.Yes/dataCnt)-1.0*Ahead.No/dataCnt*lg2(1.0*Ahead.No/dataCnt);
	return I;
};
int att_val(char branchs[][20],NodeSample *head,char *attrid)
{
	int X=99,i=0;
	NodeSample *iter=NULL;
	if(!strcmp(attrid,"Outlook")) X=0;
	if(!strcmp(attrid,"Temperature")) X=1;
	if(!strcmp(attrid,"Humidity")) X=2;
	if(!strcmp(attrid,"Windy")) X=3;
	iter=head->next;
	for(iter=head->next;iter!=NULL;iter=iter->next)
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
/**
//Pass the name of the attribute,and my data.
**/
double att_entropy(int loop,NodeSample *head)
{
		double I=0.0;
		AAA Ahead,*Atemp=NULL;
		int dataCnt=0;
		NodeSample *iter=NULL;
		AAA *iter_calc=NULL;
/**
	//Initiation
**/
		Ahead.next=NULL;
		Ahead.Yes=0;
		Ahead.No=0;
		strcpy(Ahead.att,"\0");
		iter=head->next;
		for(iter=head->next;iter!=NULL;iter=iter->next)
		{
			
			if((Atemp=find(iter->sample.item[loop],&Ahead))!=NULL)
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
		iter_calc=Ahead.next;
		for(iter_calc=Ahead.next;iter_calc!=NULL;iter_calc=iter_calc->next)
		{
			I-=iter_calc->Yes* lg2( 1.0*iter_calc->Yes/(iter_calc->Yes+iter_calc->No) ) + iter_calc->No *lg2( 1.0*iter_calc->No/(iter_calc->Yes+iter_calc->No) );
		}
	return  I/dataCnt;
}
NodeSample *pick_items(char *attrid,char *branchs,NodeSample *head)
{
/**
	int i=0;
**/
	int X=99;
	NodeSample *new_head=NULL;
	NodeSample *iter_node=NULL;
	NodeSample *iter=NULL;
	int i=0;
	if(!strcmp(attrid,"Outlook")) X=0;
	if(!strcmp(attrid,"Temperature")) X=1;
	if(!strcmp(attrid,"Humidity")) X=2;
	if(!strcmp(attrid,"Windy")) X=3;
	
	new_head=(NodeSample *)malloc(sizeof(NodeSample));
	iter_node=new_head;
	
	iter=head->next;
	for(iter=head->next;iter!=NULL;iter=iter->next)
	{
		if(!strcmp(iter->sample.item[X],branchs))
		{
			NodeSample *node=(NodeSample *)malloc(sizeof(NodeSample));
			node->sample.number=0;
			
			for(i=0;i<4;i++)
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
	int i=0;
	int loop=0;
	int numberLoop=0;
	int i_second=0;
/**
	//Initiation
**/
	strcpy(tree->leaf,"false");
	strcpy(tree->root,"root");
	tree->childNode[0]=NULL;
	tree->childNode[1]=NULL;
	tree->childNode[2]=NULL;
	tree->childNode[3]=NULL;
	
	
	for(i=0;i<4;i++)
	{
		strcpy(tree->branch_name[i],"UNKNOWN");
		tree->childNode[i]=NULL;
	}
	
	for(i=0;i<4;i++)
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
		numberLoop=att_val(branchs,head,tree->root)+1;
		
		for(loop=0;loop<numberLoop;loop++)
		{
			NodeSample *new_head=pick_items(tree->root,branchs[loop],head);
			tree_temp=ID3(new_head);
			

			for(i_second=0;i_second<4;i_second++)
/**
//Insert the child node. 
**/
			{
				if(tree->childNode[i_second]==NULL)
				{
					strcpy(tree->branch_name[loop],branchs[loop]);
					tree->childNode[loop]=tree_temp;
					break;
				}
			}
		}
	}
	
	else
	{
		strcpy(tree->leaf,"true");
		strcpy(tree->root,head->next->sample.playTennis);
	}
	return tree;
}


void interface(void) 
{
	printf("********************************\n");	
	printf("1-------------Input drill samples to drill.dat\n");
	printf("2-------------Input test samples to test.dat\n");
	printf("3-------------Show the Iterative Dichotomiser 3 tree\n");
	printf("4-------------Show The test result\n");
	printf("5-------------Statictics in drill.dat and in test.dat\n");	
	printf("6-------------Show the drill samples\n");	
	printf("7-------------show the test samples\n");	
	printf("8-------------Exit the program\n");
	printf("********************************\n\n");
}

void readDrillorTestSample(char *file)
{
	FILE *stream;
	int number=0;
	NodeSample* iter=NULL;
	int i=0;
	stream=fopen(file,"r");
	if(stream==NULL)
	{
		printf("Faild to open the file.Program terminated\n");
		exit(1);
	}
/**
//Get the length of the file.
**/
	
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);	

	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("Faild to fetch data in %s.Program terminated\n",file);
		exit(1);
	}
	head.next=&sample[0];
	
	for(i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("Found %d item(s) in file %s.\n\n",number/sizeof(head.sample),file);

	iter=head.next;
	
	for(i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		printf("Number:%d\n",iter->sample.number);
		printf("Weather:%s\n",iter->sample.item[0]);
		printf("Temperature:%s\n",iter->sample.item[1]);
		printf("Humidity:%s\n",iter->sample.item[2]);
		printf("Windy:%s\n",iter->sample.item[3]);
		printf("Play tennis or no:%s\n\n",iter->sample.playTennis);		
		iter=iter->next;
	}	
	

}
void inputDrillSample(void)
{
	FILE * fp=NULL ;
	int number=0;
	int i=0;
	NodeSample* iter=NULL;
	fp=fopen("drill.dat","a+");
	if(fp==NULL)
	{
		printf("Faild to open drill.dat.Program terminated.\n");
		getchar();
		exit(1);
	}
	if(fp!=NULL)
	{
		printf("Open the file successfully.\n");
	}
	
	printf("Please input the number of item(s) you wanna input.\n");
	scanf("%d",&number);

	if(number<=0)
	{
		printf("You input the wrong number.Program terminated\n");
		exit(1);
	}

	NodeSample head;

	NodeSample sample[number];

	head.next=&sample[0];
/**
//下一个版本进行输入数据的检测 
**/
/**
//数据录入到内存中,并建立链表
**/

	for(i=0;i<number;i++) 
	{
		printf("Now you are imputing item %d :\n",i+1);
/**
//		printf("编号：");
//		scanf("%d",&sample[i].sample.number); 
**/
		sample[i].sample.number=i+1;
		printf("Weather(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.item[0]);
		printf("Temperature(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.item[1]);
		printf("Humidity(High\\Normal)：");
		scanf("%s",sample[i].sample.item[2]);
		printf("Windy(Strong\\Weak)：");
		scanf("%s",sample[i].sample.item[3]);
		printf("Play tennis or not(Yes\\No)：");
		scanf("%s",sample[i].sample.playTennis);
		if(i<number-1)
		{
			sample[i].next=&sample[i+1];
		}
	}
 	iter=head.next;
	for(iter=head.next;iter!=NULL;iter=iter->next)
	{
		fwrite(&iter->sample,sizeof(iter->sample),1,fp);
	}
	printf("All the item(s) saved.\n");
	fclose(fp);
/**
	finish:
		;
**/
}
void inputTestSample(void)
{
	FILE * fp=NULL ;
	int i=0;
	NodeSample* iter=NULL;
	int number=0;
	fp=fopen("test.dat","a+");
	if(fp==NULL)
	{
		printf("Faild to find test.dat.Program terminated\n");
		getchar();
		exit(1);
	}
	if(fp!=NULL)
	{
		printf("File open successfully\n");
	}
	
	printf("Please enter the number of item(s) you wanna input:\n");
	scanf("%d",&number);
	if(number<=0)
	{
		printf("You input the wrong number.Program terminated\n");
		exit(1);
	}
	NodeSample head;
/**
	NodeSample sample[number];
**/
	NodeSample *sample=(NodeSample *)calloc(number,sizeof(NodeSample));
	head.next=&sample[0];
/**		
//下一个版本进行输入数据的检测 
**/
	
	for(i=0;i<number;i++) 
	{
		printf("Now you are inputing the  %d item:\n",i+1);
		sample[i].sample.number=i+1;
		printf("Weather(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.item[0]);
		printf("Temperature(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.item[1]);
		printf("Humidity(High\\Normal)：");
		scanf("%s",sample[i].sample.item[2]);
		printf("Windy(Strong\\Weak)：");
		scanf("%s",sample[i].sample.item[3]);
		strcpy(sample[i].sample.playTennis,"UNKNOWN");
		if(i<number-1)
		{
			sample[i].next=&sample[i+1];
		}
	}
 	iter=head.next;
	for(iter=head.next;iter!=NULL;iter=iter->next)
	{
		fwrite(&iter->sample,sizeof(iter->sample),1,fp);
	}
	printf("All the item(s) saved.\n");
	fclose(fp);
/**
	finish:
	;	
**/
}
void printResult(Tree_Node *Result,int num)
{
	char temp[20]="      ";
	int i=0;
	int itemp=0;
	if(!strcmp(Result->leaf,"true"))
	{
		
		for(i=0;i!=2+num;i++)
		{
			printf("%s",temp);
		}
		printf("+----Leaf:%s\n",Result->root);
	}
	else
		{
			
			for(i=0;i!=0+num;i++)
			{
				printf("%s",temp);
				
			}
			printf("+---Attribute:%s\n",Result->root);
			for(i=0;Result->childNode[i]!=NULL;i++)
			{
				
				for(itemp=0;itemp!=1+num;itemp++)
				{
					printf("%s",temp);
				}
				printf("+---Branch:%s\n",Result->branch_name[i]);
				printResult(Result->childNode[i],num+2);
			}
		}
}
Tree_Node *showRules(void)

{
	FILE *stream;
	int number=0;
	int i=0;
	Tree_Node *Result=NULL;
	NodeSample* iter=NULL; 
	stream=fopen("drill.dat","r");
	if(stream==NULL)
	{
		printf("Faild to open the file.Program terminated\n");
		exit(1);
	}
	
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);


	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("Faild to fetch item in drill.dat.Program terminated\n");
		exit(1);
	}
	head.next=&sample[0];
	
	for(i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	iter=head.next;
	for(i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		iter=iter->next;
	}
	Result=ID3(&head);
	printResult(Result,0);
	return Result;
}
void match(NodeSample *node,Tree_Node *tree)
{
	char attrid[4][20]={"Outlook","Temperature","Humidity","Windy"};
	int mark=0;
	int i=0;
	if(!strcmp(tree->leaf,"true"))
	{
		printf("\t\tPlayTennis:%s\n\n",tree->root);
	}
	else 
	{ 
		while(strcmp(tree->root,attrid[mark++]))
			{
				;
			}
		mark--;
		
		for(i=0;tree->childNode[i]!=NULL;i++)
		{
			if(!strcmp(node->sample.item[mark],tree->branch_name[i]))
			{
				match(node,tree->childNode[i]);
			}
		}
	}
}
void showTestResult(Tree_Node *tree)
{
	FILE *stream;
	int number;
	int i=0;
	NodeSample* iterloop=NULL;
	NodeSample* iter=NULL;
	stream=fopen("test.dat","r");
	if(stream==NULL)
	{
		printf("Faild to open the file.Program terminated\n");
		exit(1);
	}
	
	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);
	fseek(stream,0,SEEK_SET);


	NodeSample head;
	NodeSample sample[number/sizeof(head.sample)];
	if(number/sizeof(head.sample)<=0)
	{
		printf("Faild to fetch item in test.dat.Program terminated\n");
		exit(1);
	}
	head.next=&sample[0];
	
	for(i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
		if(i==number/sizeof(head.sample)-2)
		{
			sample[i].next->next=NULL;
		}
	}
	iterloop=head.next;
	for(i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iterloop->sample,sizeof(head.sample),1,stream);
		iterloop=iterloop->next;
	}
/**	
//	printf("%d item found\n",number/sizeof(head.sample));
**/	
	iter=head.next;
	for(iter=head.next;iter!=NULL;iter=iter->next)
	{
		printf("Number:%d\n",iter->sample.number);
		printf("Weather:%s\n",iter->sample.item[0]);
		printf("Temperature:%s\n",iter->sample.item[1]);
		printf("Humidity:%s\n",iter->sample.item[2]);
		printf("Windy:%s\n",iter->sample.item[3]);
		match(iter,tree);
		
	}		
}
void statistics(void)
{
	FILE *stream;
	int number;
	stream=fopen("drill.dat","r");
	if(stream==NULL)
	{
		printf("Faild to open the file.Program terminated\n");
		exit(1);
	}
 

	fseek(stream,0,SEEK_SET);
	fseek(stream,0,SEEK_END);
	number=ftell(stream);

	printf("There are %d items in drill.dat.\n",number/sizeof(struct Sample));
	stream=fopen("test.dat","r");
	if(stream==NULL)
	{
		printf("Faild to open the file.Program terminated\n");
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

int main() 
{
	Tree_Node *tree=NULL;
	int choose=0;
loop:
	interface();
	
	choose=getchar();
	switch (choose)
	{
		case '1':
			inputDrillSample();
			break;
		case '2':
			inputTestSample();
			break;
		case '3':
			tree=showRules();
			break;
		case '4':
			if(tree==NULL)
			{
				tree=showRules();
			}
			showTestResult(tree);
			break;
		case '5':
			statistics();
			break;
		case '6':
			readDrillorTestSample("drill.dat");
			break;
		case '7':
			readDrillorTestSample("test.dat");
			break;
		case '8':
			exitProgram();
			break;
		default:
			printf("There is something wrong with your number,please input again:\n");
			break;
	}
	printf("\nFUNCTION COMPLETED.NOW RETURN TO MENU.\n");
	getchar();
	goto loop;
	return 0;
}
