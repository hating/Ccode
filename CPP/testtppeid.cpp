#include <iostream>
using namespace std;
void func(char *s1, char *s2)
{
	int n;
    for(n=0;s1[n]!='\0';n++)
    	;
 //   n++;
    cout<<n<<endl;
//    n=3;
     for(int i=0;i<n;i++)
    {
        s2[i]=s1[i];
    }
    int temp=0;
//    n--;
    for(int j=1;j<n-1;j++)
    {
        for(int k=1;k<n-2;k++)
        {
           if(s2[k]<s2[k+1])
           {
               temp=s2[k];
               s2[k]=s2[k+1];
               s2[k+1]=temp;
           }
        }
    }
	cout<<s2<<endl;           
}
int main()
{
	char s2[100];
	func("246135",s2);
}
