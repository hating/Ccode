#include <stdio.h>
#include <stdlib.h>
#define MAXNAME 40
struct student{
	char *name=(char *)malloc(MAXNAME);
	int age;
	int score;
}; 
int main (){
	struct student student1;
	scanf("%s",student1.name);
	scanf("%d",&student1.age);
	scanf("%d",&student1.score);
	printf("Name:%s\nAge:%d\nScore%d\n",student1.name,student1.age,student1.score);
	printf("The amount of memory of student1 is:\n%d\n",sizeof(student1));
	return 0;
} 
