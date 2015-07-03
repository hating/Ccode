#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long  fun(char s[],int n)
{
	long long0;
  //--ksstart£¨×¢ÊÍ²»ÄÜÉ¾³ı£¡ª
 //¿¼Éú´úÂë´Ó´Ë¿ªÊ¼±àĞ´
  int i=0;
 long0=0;
 for(i=0;i<n-1;i++)
 {
	 if(s[i]>s[i+1])
	 {
	 	printf("%c %c\n",s[i],s[i+1]);
		long0++;		 
   	}
 }
 //--ksend---  
	return long0;
}

main()
{  char  s[]="a1Ab1D2";
   int  n=strlen(s);
   long cnt=0; 
   printf("%s\n",s);
   cnt=fun(s,n);
   printf("cnt=%ld\n",cnt);   
}

