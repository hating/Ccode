#include<stdio.h>
//#include<iostream.h>
//#include<fstream.h>
#include<stdlib.h>  
#include <string.h> 
#include<math.h>

#define maxsize 20

struct tree_node
{
	int attrib_col;          // ��ǰ�ڵ��Ӧ����
	int value;              // ��Ӧ��ֵ
	struct tree_node*  left_node;    // ����
	struct tree_node*  right_node;    //  ͬ�������ڵ�
	int isleaf;          // �Ƿ�Ҷ�ӽڵ�
	int classno;            // ��Ӧ������
};

typedef struct tree_node s_tree;

double compute_pi(double pi)
{
   if (pi<=0)
   return 0;
   if (pi>=1)
   return 0;
   return 0-pi*log(pi)/log(2);
}

int getposition(int *data,int datasize,int value)
{
	int i;
	for (i=0;i<datasize;i++) 
	if (data[i]==value) 
	return i;
	return  -1;
}

double Compute_InforGain(int **data,int record_num,int col_no,int num_attrib)
{
   int *differentvalue;
   int total_differentvalue;
   int s[maxsize][maxsize],classsum,a[maxsize],b[maxsize];
   int sj;
   int i,j,flag;
   int cu[maxsize];
   classsum=0;
   for(i=0;i<maxsize;i++)
  b[i]=0;

      a[classsum]=data[0][num_attrib-1];//��Ķ�Ӧ��ʶ
      b[classsum]++;//ÿ�����Ŀ
      classsum++;   //һ���ж�����
  
  for(i=1;i<record_num;i++)
  {
  flag=0;
      for(int k=0;k<classsum;k++)
  {
         if(data[i][num_attrib-1]==a[k])
			{
				flag=1;
				b[k]++;
			}
  }
	  if(flag==0)
		  {
			a[classsum]=data[i][num_attrib-1];
			b[classsum]++;
			classsum++;
		  }
  }
  for(i=0;i<maxsize;i++)
           for(j=0;j<maxsize;j++)
   				s[i][j]=0;

differentvalue=(int*)malloc(maxsize*sizeof(int));
      total_differentvalue=0;
	  j=0;
      for (i=0;i<record_num;i++)
  {
        j=getposition(differentvalue,total_differentvalue,data[i][col_no]);
        if(j<0) 
{
        differentvalue[total_differentvalue]=data[i][col_no];
   for(int k=0;k<classsum;k++)
   {
	   if(a[k]==data[i][num_attrib-1])
	   s[k][total_differentvalue]++;
   }
	    total_differentvalue++;

}
else
{
           for(int k=0;k<classsum;k++)
			   {
				   if(a[k]==data[i][num_attrib-1])
				   s[k][j]++;
			   }
}
  }
  for(i=0;i<total_differentvalue;i++)
  cu[i]=0;
      for(i=0;i<total_differentvalue;i++)
  for(j=0;j<classsum;j++)
     cu[i]+=s[j][i];
       double total_I=0;
       for (i=0;i<classsum;i++)
   {
          total_I+=compute_pi((double)b[i]/record_num);
   }
        double EA=0;
for(i=0;i<classsum;i++)
{  
sj=0;
for(j=0;j<total_differentvalue;j++)
        EA+=(double)cu[i]/record_num*compute_pi((double)s[j][i]/cu[i]);
}
       return  (total_I-EA);
}

s_tree *Build_ID3(int **data,int record_num,int num_attrib)
{
   int i,p,a[maxsize],b[maxsize],classsum;
   s_tree *p2=(s_tree *)malloc(sizeof(s_tree));
   s_tree *root=NULL;
   int flag,flag2;
   int attrib[maxsize];
   classsum=0;
   for(i=0;i<maxsize;i++)
  b[i]=0;
      a[classsum]=data[0][num_attrib-1];//��Ķ�Ӧ��ʶ
      b[classsum]++;//ÿ�����Ŀ
      classsum++;   //һ���ж�����  1
  for(i=1;i<record_num;i++)
  {
  flag=0;
      for(int k=0;k<classsum;k++)
  {
         if(data[i][num_attrib-1]==a[k])
{
flag=1;
b[k]++;
}
  }
  if(flag==0)
  {
        a[classsum]=data[i][num_attrib-1];
b[classsum]++;
        classsum++;
  }
  }
   if(record_num==0) 
   return NULL;  

   int temp_num_attrib=0;
   for(i=0;i<num_attrib-1;i++) 
   {
     if(data[0][i]>=0)
{
attrib[temp_num_attrib]=i;
temp_num_attrib++;  
}
   }
   root=p2;
   p2->attrib_col=-1;          
   p2->value=-1;              
   p2->left_node=NULL;    
   p2->right_node=NULL;    
   p2->isleaf=-1;          
   p2->classno=-1;    
   if(classsum==1)
   {
         p2->classno=a[classsum-1];
         p2->isleaf=1;
         p2->left_node=NULL;
p2->right_node=NULL;
         return root;
    }
   if(temp_num_attrib==0)
   {
   int max=b[0];
   for(i=0;i<classsum;i++)
   {
           if(b[i]>max)
   {
   max=b[i];
   p=i;
   }
   }
         p2->classno=a[p];
         p2->isleaf=1;
         p2->left_node=NULL;
p2->right_node=NULL;
         return root;
   }   

    double inforgain=0;
    int currentcol=-1;
    for(i=0;i<temp_num_attrib;i++)
{
double tempgain=Compute_InforGain(data,record_num,attrib[i],num_attrib);
      if(inforgain<tempgain)
  { 
   inforgain=tempgain; 
       currentcol=attrib[i];
  }
}
      p2->attrib_col=currentcol;
      int j=0;
      int value_no=0;
      int diferentvalue[maxsize];
      while(j<record_num)
  {
         flag2=0;
         for (int k=0;k<value_no;k++) 
{
        if (diferentvalue[k]==data[j][currentcol]) 
            flag2=1;
}
         if(flag2==0)
{ 
        diferentvalue[value_no]=data[j][currentcol];
        value_no++;	  
}
        j++;
  }
int **subdata,k;
subdata=(int**)malloc(record_num*sizeof(int*));           //��subdata�����ڴ�
for(i=0;i<record_num;i++)
{
subdata[i]=(int*)malloc(num_attrib*sizeof(int));
}
for(i=0;i<value_no;i++)
{
    k=0;
   for (int x=0;x<record_num;x++)
   {
     if (data[x][currentcol]==diferentvalue[i])
        {	   
           for(int i1=0;i1<num_attrib;i1++)
   {
    if(i1!=currentcol)
subdata[k][i1]=data[x][i1];
                else 
subdata[k][i1]=-1;
   }
    k++;
         }
   }
   p2->attrib_col=currentcol;
   p2->value=diferentvalue[i];
   p2->isleaf=0;
   p2->classno=-1;
   p2->left_node=Build_ID3(subdata,k,num_attrib);
   p2->right_node=(s_tree *)malloc(sizeof(s_tree));
   p2=p2->right_node;
   p2->attrib_col=-1;          
   p2->value=-1;             
   p2->left_node=NULL;    
   p2->right_node=NULL;    
   p2->isleaf=0;          
   p2->classno=-1;    
}
return root;
}

int outputrule(s_tree *p,int *data)
{
int col_no,class_no=-1;
int flag1=0,flag2=0;
int count=0;
while(flag1==0)
{

col_no=p->attrib_col;
while(flag2==0)
{
if(data[col_no]!=p->value&&p->right_node!=NULL)
p=p->right_node;
else
flag2=1;

} 
if(p->classno!=-1)
{
class_no=p->classno;
flag1=1;
}
if(p->left_node!=NULL&&flag1==0)
{
p=p->left_node;
flag2=0;
}

if(count>9)
flag1=1;
count++;
}
return class_no;
}

double ID3(int **array,int **data,int n,int r_n,int m)
{
s_tree *p=NULL;
int i,j,num=0,temp;
int rs[maxsize][maxsize];
int cla=0,class_temp[maxsize];
//������ĸ���
for(j=0;j<n;j++)
{
if(data[j][m-1]>cla)
cla=data[j][m-1];
}
cla++;
//��rs������ֵ����ֵ
for(i=0;i<cla;i++)
{
for(j=0;j<cla;j++)
{
rs[i][j]=0;
}
}
p=Build_ID3(array,r_n,m);
for(i=0;i<n;i++)
{
temp=outputrule(p,data[i]);
if(temp==data[i][m-1])
num++;
rs[data[i][m-1]][temp]++;
}
printf("\n���μ��㾫�ȱ�");
//������ĸ���
cla=0;
for(j=0;j<n;j++)
{
if(data[j][m-1]>cla)
cla=data[j][m-1];
}
cla++;
for(i=0;i<cla;i++)
{
printf("\n");
for(j=0;j<cla;j++)
printf("%d\t",rs[i][j]);
}
printf("\nID3׼ȷ��:%f\n",(double)num/n);
return (double)num/n;
}

double bayes(int **data,int **record,int n,int m,int r_n)
{
int i,j,k,t;
int class_temp[maxsize],temp,count_temp=0,k_temps;
double **temps,max_temps;
int rs[maxsize][maxsize];
int *classs;
int ***count;  //ĳ�����Եĸ���;��������Ԫ����� 
int sign,num=0;
//��������������
classs=(int*)malloc(r_n*sizeof(int));   //��classs�����ڴ�
for(i=0;i<m;i++)
{
temp=0;
classs[i]=0;
for(j=0;j<r_n;j++)
{
if(record[j][i]>temp)
temp=record[j][i];
}
classs[i]=temp+1;
if(classs[i]>count_temp)
count_temp=classs[i]+1;
}
//	printf("%d",classs[m-1]);
//�������Ÿ���
for(k=0;k<classs[m-1];k++)
{
class_temp[k]=0;
for(i=0;i<r_n;i++)
{
if(record[i][m-1]==k)
class_temp[k]++;
} 
//	printf("\t%d",class_temp[k]);
}
//����������Զ�Ӧ������
count=(int***)malloc(m*sizeof(int**));                  //��count�����ڴ�
for(i=0;i<m;i++)
{
count[i]=(int**)malloc(count_temp*sizeof(int*));
for(j=0;j<count_temp;j++)
{
count[i][j]=(int*)malloc(classs[m-1]*sizeof(int));
}
}
temps=(double**)malloc(r_n*sizeof(double*));           //��temps�����ڴ�
for(i=0;i<r_n;i++)
{
temps[i]=(double*)malloc(classs[m-1]*sizeof(double));
}
for(k=0;k<classs[m-1];k++)
{
for(i=0;i<m-1;i++)
{
for(t=0;t<classs[i];t++)
{
count[i][t][k]=0;
for(j=0;j<n;j++)
{
if(record[j][i]==t&&record[j][m-1]==k)
count[i][t][k]++;
}
}
} 
}
for(i=0;i<n;i++)
{
for(k=0;k<classs[m-1];k++)
{
temps[i][k]=1;
for(j=0;j<m-1;j++)
{
temps[i][k]*=(double)count[j][data[i][j]][k]/class_temp[k];
}
temps[i][k]*=(double)class_temp[k]/r_n;
}
}
//��rs����������ֵ����ֵ
for(i=0;i<classs[m-1];i++)
{
for(j=0;j<classs[m-1];j++)
{
rs[i][j]=0;
}
}
//����׼ȷ��
for(i=0;i<n;i++)
{
max_temps=-1;
k_temps=-1;
for(k=0;k<classs[m-1];k++)
{
if(temps[i][k]>max_temps)
{
max_temps=temps[i][k];
k_temps=k;
}
}
sign=k_temps;
rs[data[i][m-1]][sign]++;
if(data[i][m-1]==sign)
{
num=num+1;
} 
}
//������Ƚ��
printf("\n���μ��㾫�ȱ�");
for(i=0;i<classs[m-1];i++)
{
printf("\n");
for(j=0;j<classs[m-1];j++)
printf("%d\t",rs[i][j]);
}
printf("\nbayes׼ȷ��%f\n",(double)num/n);
return (double)num/n;

//�ͷ��ڴ� 
free(classs);                 //��classs�ͷ��ڴ�

for(i=0;i<m-1;i++)              //��count�ͷ��ڴ�
{ 
for(j=0;j<count_temp;j++)
{
free(count[i][j]);
}
}
for(i=0;i<m-1;i++)
{ 
free(count[i]);
} 
free(count);   

for(i=0;i<r_n;i++)               //��temps�ͷ��ڴ�
{
free(temps[i]);
}
free(temps);
}

void files(int n,int m,int cross)
{
FILE *outfile;
FILE *newfile=NULL;
FILE *writefile=NULL;
int file[maxsize];
int i,j,k;
char filename[50],s[maxsize],data[500];
if((outfile=fopen("e:\\a\\table.txt","r"))==NULL) 
{ 
printf("�ļ���ʧ�ܣ������ļ�������\n");
exit(0);
}
//����1-10�ļ�
for(i=0;i<cross;i++)
{
memset(filename, 0, sizeof(filename));
itoa(i+1,s,10);
strcat(filename,"e:\\a\\"); 
strcat(filename,s); 
strcat(filename,".txt"); 
newfile = fopen(filename, "w+");
}
//������������ȡд��1-10��txt�ļ���
for(i=0;i<n;n++)
{	fscanf(outfile,"\n");
while(feof(outfile))
return;
for(j=0;j<cross;j++)
{
memset(data, 0, sizeof(data));
for(k=0;k<m;k++)
{
file[k]=0;
fscanf(outfile,"%d",&file[k]);
strcat(data," "); 
itoa(file[k],s,10);
strcat(data,s); 
}
memset(filename, 0, sizeof(filename));
itoa(j+1,s,10);                          //��ȡ�ļ���
strcat(filename,"e:\\a\\"); 
strcat(filename,s); 
strcat(filename,".txt"); 
strcat(data,"\n"); 
writefile=fopen(filename,"a+");
fputs(data,writefile);
fclose(writefile);
}

}
}

int main ()
{
//ȫ�ֱ���
int i,j,k,t;
int **data,**record;    //data�Լ�,record��ѵ����
int record_num;         //��¼ѵ�����ĸ�����ʱ����
    int n,m,cross;       //ÿ���Ӽ�n������,m������,k������
double num_cross1=0.00,num_cross2=0.00;
//�ļ������������
int lines=0;
FILE *outfile;
char filename[50],s[10];
printf("����������ֵ�ĸ�����");
scanf("%d",&m);
printf("�����뽻��ȷ�Ϸ��������������");
scanf("%d",&cross);
//�Ӷ�ȡ�ļ���������Ŀ
if((outfile=fopen("e:\\a\\table.txt","r"))==NULL) 
{ 
printf("�ļ���ʧ�ܣ������ļ�������\n");
exit(0);
}
while (!feof(outfile))
    {
if (fgetc(outfile)=='\n')
lines++;
}
n=lines/cross;                        //ÿ���Ӽ����������������ļ�������������
fclose(outfile);
//�������
printf("���ڲ�������У����Ժ�...");
//	files(n,m,cross);
//����ѵ��������Լ�
data=(int**)malloc(n*sizeof(int*)); 
for(i=0;i<n; i++)
{
data[i]=(int*)malloc(m*sizeof(int));
} 
record=(int**)malloc(n*cross*sizeof(int*)); 
for(i=0;i<n*cross;i++)
{
record[i]=(int*)malloc(m*sizeof(int));
}

for(i=0;i<cross;i++)
{
record_num=0;
memset(filename, 0, sizeof(filename));
itoa(i+1,s,10);
strcat(filename,"e:\\a\\"); 
strcat(filename,s); 
strcat(filename,".txt"); 
outfile=fopen(filename,"r");
for(j=0;j<n;j++)
{
for(k=0;k<m;k++)
{
fscanf(outfile,"%d",&data[j][k]);               //���Լ�
}
fscanf(outfile,"\n");
}
fclose(outfile);
for(t=0;t<i;t++)
{
memset(filename, 0, sizeof(filename));
itoa(t+1,s,10);
strcat(filename,"e:\\a\\"); 
strcat(filename,s); 
strcat(filename,".txt"); 
outfile=fopen(filename,"r");
for(j=0;j<n;j++)
{
for(k=0;k<m;k++)
{
fscanf(outfile,"%d",&record[record_num][k]); //ѵ����
}
fscanf(outfile,"\n");
record_num++;
}
fclose(outfile);
}
for(t=i+1;t<cross;t++)
{
memset(filename, 0, sizeof(filename));
itoa(t+1,s,10);
strcat(filename,"e:\\a\\"); 
strcat(filename,s); 
strcat(filename,".txt"); 
outfile=fopen(filename,"r");
for(j=0;j<n;j++)
{
for(k=0;k<m;k++)
{
fscanf(outfile,"%d",&record[record_num][k]);  //ѵ����
}
fscanf(outfile,"\n");
record_num++;
}
fclose(outfile);
}
num_cross1+=(double)bayes(data,record,n,m,n*(cross-1));
num_cross2+=(double)ID3(record,data,n,record_num,m);
}
printf("\nbayesƽ��׼ȷ��Ϊ��%f\n",(double)num_cross1/cross);
printf("\nID3ƽ��׼ȷ��Ϊ��%f\n",(double)num_cross2/cross);
}
