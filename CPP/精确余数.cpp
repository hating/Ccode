#include <stdio.h>
int main ()
{
	int a[200];
	for(int i=0;i<200;i++)
	{
		a[i]=-1;
	} 
	//������a���г�ʼ��
	int up=0,down=0;
	scanf("%d/%d",&up,&down);
	for(int i=0;i<200;i++){
		
		 up*=10;//�����ӳ���10��ʹ�÷��Ӵ��ڷ�ĸ 
		 a[i]=up/down;//��up�д���down�Ĳ��������
		 up=up%down;//ʹ��һ��������ȡ��������Ϊup
		 if(!up)break; 
	}//�����ˣ�ȫ�������� 
	printf("0.");
	for(int i=0;i<200;i++){
		if(a[i]==-1){
			break;
		}
		printf("%d",a[i]);
		
	} //��һ�����������
	printf("\n");//��ĿҪ��Ļس�
	return 0; 
}
