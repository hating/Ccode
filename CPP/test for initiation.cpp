#include <iostream>
using namespace std;
void function(void);
int a;
int main (){
	
	cout<<"before initiation a="<<a<<endl;
	a=110;
	cout<<"after initiation a="<<a<<endl;
	
	function();
	return 0;
}
void function(){
	static int a=999;
	cout<<"In function a="<<a<<endl;
}
