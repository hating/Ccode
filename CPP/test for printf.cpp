#include <stdio.h>//≤‚ ‘printf()
#include <iostream>
using namespace std;
int printf(char *p);
int main (){
	cout<<"Say the word you want to know"<<endl;
	char p[40];
	gets(p);
	printf(*p);
	return 0;
} 
int printf(char p){
	cout<<"In printf function";
	cout<<p;
}
