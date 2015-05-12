#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id3.h"

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
		printf("没有从drill.dat找到匹配的数据，程序即将退出。\n");
		exit(1);
	}
	head.next=&sample[0];
	for(int i=0;i<number/sizeof(head.sample)-1;i++)
	{
		sample[i].next=&sample[i+1];
	}
	
	printf("共从drill.dat找到%d份数据。\n\n",number/sizeof(head.sample));

	NodeSample* iter=head.next;
	for(int i=0;i<number/sizeof(head.sample);i++)
	{
		fread(&iter->sample,sizeof(head.sample),1,stream);
		printf("编号：%d\n",iter->sample.number);
		printf("天气：%s\n",iter->sample.outlook);
		printf("温度：%s\n",iter->sample.temperate);
		printf("湿度：%s\n",iter->sample.humidity);
		printf("风力：%s\n",iter->sample.wind);
		printf("是否打羽毛球：%s\n\n",iter->sample.playTennis);		
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
		printf("编号：");
		scanf("%d",&sample[i].sample.number); 
		printf("天气(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.outlook);
		printf("温度(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.temperate);
		printf("湿度(High\\Normal)：");
		scanf("%s",sample[i].sample.humidity);
		printf("风力(Strong\\Weak)：");
		scanf("%s",sample[i].sample.wind);
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
	//Unfinished
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
		printf("编号：");
		scanf("%d",&sample[i].sample.number); 
		printf("天气(Sunny\\Overcast\\Rain)：");
		scanf("%s",sample[i].sample.outlook);
		printf("温度(Hot\\Mild\\Cool)：");
		scanf("%s",sample[i].sample.temperate);
		printf("湿度(High\\Normal)：");
		scanf("%s",sample[i].sample.humidity);
		printf("风力(Strong\\Weak)：");
		scanf("%s",sample[i].sample.wind);
//		printf("是否玩网球(Yes\\No)：");
//		scanf("%s",sample[i].sample.playTennis);
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
