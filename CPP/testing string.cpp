#include <iostream>
using namespace std;
int main()
{
	//��Ŀ1
	string s1("");
	s1.append("ABCDEFG", 3, 2); 
	cout << s1; 
	cout<<endl;
	//��Ŀ2 
	string s2("");
	s2.append("ABCDEFG", 4); 
	cout << s2;
	return 0;
} 
