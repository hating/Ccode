#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
char *mycat(char *a,char *b);
int main ()
{
//	char *a={"This is the head."};
//	char *b={"This is the tail."};
	char *a=(char *)malloc(128);
	gets(a);
	char *b=(char *)malloc(128);;
	gets(b); 
	char *c=mycat(a,b);	
	puts(c);
	return 0;
}
char *mycat(char *a,char *b)
{
	int i=0;
	char *cat=(char *)malloc(strlen(a)+strlen(b)+1);
	for(;i<strlen(a);i++)
	{
		*(cat+i)=a[i]; 
	} 
	for(;i<(strlen(a)+strlen(b));i++)
	{
		*(cat+i)=b[i-strlen(a)]; 
	} 
	*(cat+i)='\0';
	return cat;
}
