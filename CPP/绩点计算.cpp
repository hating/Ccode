#include <iostream>
#include <windows.h>
#define MaxSubject 20
using namespace std;
int main ()
{

	cout<<"����������ڼ���ƽ��ѧ��"<<endl;
	cout<<"Powered by PJJ"<<endl;
	cout<<"_________________________"<<endl;
	int score[MaxSubject];
	double average_mark[MaxSubject],mark[MaxSubject];
	double sum_mark=0,total_average_mark=0;
	for(int i=0;i<MaxSubject;i++)
	{
		score[i]=mark[i]=average_mark[i]=0;
	} 

//��������г�ʼ��
	int i=-1;

	while((int)mark[i++]!=-1)
	{
		cout<<"�������"<<i+1<<"�� �ɼ� ѧ�֣�����-1 -1�˳���������89 2.0��:\t"<<endl;
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
	cout<<"���ƽ�������ǣ�"<<total_average_mark<<endl;
	cout<<"��ӭ����ʹ�á�"<<endl; 
	system("pause");
}
