#include <iostream>
int swap ( int& x, int& y, int& z);  //����������Ϊ��������
int swap ( int* x, int* y, int* z); //����������Ϊָ������
int main()
{
	int a=0,b=0,c=0,result=0;
	std::cin>>a>>b>>c;
	result=swap(&a,&b,&c);
	result=swap(a,b,c);
	std::cout<<result<<" "<<a<<" "<<b<<" "<<c<<std::endl;
} 
int swap ( int& x, int& y, int& z)
{
	int temp=z;
	z=y;
	y=x;
	x=temp;
	int max=x;
	if(max<y)max=y;
	if(max<z)max=z;
	return max;
}
int swap ( int* x, int* y, int* z)
{
	int temp=*z;
	*z=*y;
	*y=*x;
	*x=temp;
	int max=*x;
	if(max<*y)max=*y;
	if(max<*z)max=*z;
	return max;
	
}
