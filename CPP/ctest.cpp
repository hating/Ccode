#include <stdio.h>
#include <malloc.h>
int func (int *,int *);
int main ()
{
	int a[10];
	int *p=(int *)malloc(40);
	printf("in main()\nsizeof a[10]=%d \t sizeof *p=%d \n",sizeof(a),sizeof(p));
	func(a,p);
	return 0;
	free(p);
} 
int func(int *a,int *p)
{
	printf("in func():\nsizeof a[10]=%d \t sizeof *p=%d \n",sizeof(a),sizeof(p));
	return 0;
}
