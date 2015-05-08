#include <stdio.h>
#include <string.h>
int main()
{
	char input[20];
	char output[20];
//	scanf("%s",input);
	gets(input);
	input[strlen(input)-1]='\0';
//	printf("%s",input);
	int n;
	scanf("%d",&n);
	int i;
	int cnt=0;
	for(i=strlen(input)-n;i<strlen(input);i++)
	{
		output[cnt]=input[i];
		cnt++;
	}
	for(i=0;i<strlen(input)-n;i++)
	{
		output[cnt]=input[i];
		cnt++;
	}
	printf("%s\n",output);
	
    return 0;
}

