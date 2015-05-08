#include <iostream>
#include <windows.h>
#define MaxSubject 20
using namespace std;
int main ()
{

	cout<<"这个程序用于计算平均学分"<<endl;
	cout<<"Powered by PJJ"<<endl;
	cout<<"_________________________"<<endl;
	int score[MaxSubject];
	double average_mark[MaxSubject],mark[MaxSubject];
	double sum_mark=0,total_average_mark=0;
	for(int i=0;i<MaxSubject;i++)
	{
		score[i]=mark[i]=average_mark[i]=0;
	} 

//对数组进行初始化
	int i=-1;

	while((int)mark[i++]!=-1)
	{
		cout<<"请输入第"<<i+1<<"科 成绩 学分，输入-1 -1退出。（例：89 2.0）:\t"<<endl;
		cin>>score[i]>>mark[i]; 
		
	} 
	i=0;
	while((int)mark[i]!=-1)
	{
		sum_mark+=mark[i];
		i++;
	}
	i=0;
	while((int)mark[i]!=-1)
	{
		average_mark[i]=(score[i]*1.0/10-5)*mark[i]/sum_mark; 
		total_average_mark+=average_mark[i];
		i++;
	}
	cout<<"你的平均绩点是："<<total_average_mark<<endl;
	cout<<"欢迎继续使用。"<<endl; 
	system("pause");
}
