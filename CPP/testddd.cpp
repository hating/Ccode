#include <stdio.h>
#include <string.h>
char src[80], des[80];
int main(int argc, char ** argv)
{
 int i, len;
 scanf("%s %s",&src,&des);
 len = strlen(des);
 for(i = 0; src[i] != '\0';)
 {
  if(strncmp(&src[i], des, len) == 0)
   i += len;
  else
  {
   putchar(src[i]);
   i++;
  } 
 }
 return 0;
}
