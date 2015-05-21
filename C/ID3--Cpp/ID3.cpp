/*
 Read raw data from test.txt

 Powered by fenglinglu.

*/
#include <iostream>//��׼������������� 
#include <fstream>//�ļ���������� 
#include <sstream>
#include <string>//�ַ����� 
#include <vector>//���� 
#include <algorithm>// ������ 
#include <cmath>//��ѧ���� 
#include <map>
#include "ID3.h"
using namespace std;


void show_data(const My_Data &data)
{
    for(vector<string>::const_iterator iter = data.attributes.begin();iter != data.attributes.end();++iter)//���arrtibutes��ÿ����ͬ��arrtibute֮��ָ�һ���� ���������ɺ󣬻��С� 
        cout <<*iter<<" ";
    cout<<endl;
    cout<<data.col<<endl;//������� 
    for(vector< vector<string> >::const_iterator iter1=data.items.begin();iter1!=data.items.end();++iter1)//˫��Ƕ��ѭ��������Ϊ�˰�item������� 
    {
        for(vector<string>::const_iterator iter2 = (*iter1).begin();iter2 != (*iter1).end();++iter2)
            cout<<*iter2<<" ";
        cout<<endl;//���� 
    }
    cout<<data.row<<endl;//������� 
}
vector<string> att_val(const string &att,const My_Data &data)
{
    vector<string> val;
    string value;
    vector<string>::const_iterator iter_temp;
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//����ÿһ������ 
    {
        iter_temp=find(data.attributes.begin(),data.attributes.end(),att);//�ҵ����ҵ�attribute���� 
        value=(*iter)[iter_temp-data.attributes.begin()];//�������������arributesͷ���ľ��� 
        if(find(val.begin(),val.end(),value)==val.end())//���û���������ԣ��Ǿ�push��val������ 
            val.push_back(value);
    }
    return val;//����val���� 
}
My_Data read_data(const string &fname)//��ȡ�ļ����� 
{
    My_Data my_data; //����һ��My_Data�Ľṹ�壬������my_data 
    ifstream data_file;	//����һ��ifstream���data_file�����ڴ��ļ��ж�ȡ���ݣ�������FILE�������һ�ζ������Լ�����ʵ�֣� 
    data_file.open(fname.c_str(),ios::in);//ʹ��ifstream�ĳ�Ա������ȡ�ļ� ��string.c_str���ص���fname�����ַ���ַ������ԭ��void open (const   char* filename,  ios_base::openmode mode = ios_base::in);
    if(!data_file)//���data_fileû�ж����Ļ������������� 
        cout << "ERROR!" <<endl;
    else
    {
        string line,word;//����line��word��string 
        getline(data_file,line);//��data_file�����ҵ���־�����е��ַ��� 
        istringstream stream(line);// istringstream������԰�һ���ַ�����Ȼ���Կո�Ϊ�ָ����Ѹ��зָ�������http://blog.csdn.net/xiayang05/article/details/5933893
        while(stream>>word)//�����ж�ȡword��ֱ������û������ 
            my_data.attributes.push_back(word);//��word���뵽My_Data��vector������ 
        my_data.col = my_data.attributes.size();//���attributes������󣬼������� 
        while(getline(data_file,line))//��ȡʣ�µ�ÿһ�� 
        {
            vector<string> v_str;//����һ����ʱ��vector<string> 
            istringstream stream(line);//�ѵ�ǰ���ַ��� 
            while(stream>>word)//������л����ַ� 
                v_str.push_back(word);//����v_str�� 
            my_data.items.push_back(v_str);//��v_str���꣬������my_data��ȥ 
        }
        my_data.row = my_data.items.size();//��ȡ���� 
        data_file.close();//�ر��ļ� 
    }
    return my_data;//����my_data����ṹ�� 
}
My_Data pick_items(const string &att,const string &val,const My_Data &data)//ɸѡ��������������������µ����� 
{
    My_Data new_data;
    vector<string> item;
    vector<string>::const_iterator iter_temp;
    iter_temp=find(data.attributes.begin(),data.attributes.end(),att);
    if(iter_temp==data.attributes.end())//������ 
        cout<<"ERROR!"<<endl;
    else
    {
        int num=iter_temp-data.attributes.begin();//������ɸѡ��attribute��attribute�ľ��� 
        for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//������data 
            if((*iter)[num]==val)//�����val(Sunny,Wind,Overcast)��� 
                new_data.items.push_back(*iter);//�ӵ���data����ȥ 
        new_data.attributes=data.attributes;//��ɸ��� 
        new_data.col=data.col;//��ɸ��� 
        new_data.row=new_data.items.size();//���������data��ͬ�ĵط� 
    }
    return new_data;
}

/**
Ϊ�˾�ȷ�ض�����Ϣ���棬�����ȶ�����Ϣ���й㷺ʹ�õ�һ��������׼����Ϊ�أ�entropy�������̻��������������Ĵ��ȣ� purity����
������������ĳ��Ŀ����������������������S ����ôS �����������ͷ������Ϊ�� 
Entropy(S ) =-P��log2P��-P��log2P�� 
����P�� ����S �������ı�����P������S �и����ı��������й��ص����м��������Ƕ���0 log0 Ϊ0 ��
����˵��������S ��һ������ĳ����������� 14 �������ļ��ϣ������� 9 ��������5 �����������ǲ��üǺ�[9+ ��5 -]������������������������
��ôS ������������������أ�Entropy��Ϊ�� 
Entropy([9+,5-]) =-(9/14)log2(9/14) - (5/14)log2(5/14)
 **/ 
double val_entropy(const My_Data &data)//��const��ʽ����data �����ؼ������ֵ 
{
    vector<string> S;//������һ��S���������ô��ں�ͷ 
    vector<string>::const_iterator iter_temp;//iter_tempҲ��֪����ʲô�� 
    vector<int> S_Count;//��ֵ�ļ��㣿 
    int S_Sum=data.items.size();//S_Sum������ȫ��item������ 
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//iter��һ������vector��ָ�룬ѭ��ɨ��ÿһ�е����� 
    {
        iter_temp=find(S.begin(),S.end(),(*iter)[data.col-1]);// ��S.begin��S.end֮���ҵ�(*iter)[data.col-1]�������Yes/No
        if(iter_temp==S.end())//���û���ҵ�(*iter)[data.col-1] 
        {
            S.push_back((*iter)[data.col-1]);//��(*iter)[data.col-1]����S�У��������´ξͿ����ҵ��ˣ� 
            S_Count.push_back(1);//��¼��һ��S_Count 
        }
        else
            ++S_Count[iter_temp-S.begin()];//����Yes��No������ 
    }
    vector<double> P(S_Count.size(),0.0);
    double I=0.0;
    for(int i=0;i!=P.size();++i)
    {
        P[i]=static_cast<double>(S_Count[i])/S_Sum;//P[i] 
        I=I-P[i]*log2(P[i]);
    }
    return I;//I=0.9402���⾿����˭����ֵ�أ� 
}
double att_entropy(const string &att,const My_Data &data)//����attribute����ֵ�ĺ��� 
{
    vector<string> val=att_val(att,data);
    My_Data new_data;
    double I=0.0,Val_E=0.0;
    for(vector<string>::const_iterator iter=val.begin();iter!=val.end();++iter)
    {
        new_data=pick_items(att,*iter,data);
        Val_E=val_entropy(new_data);
        I=I+Val_E*new_data.row/data.row;
    }
    return I;
}
Decision_Tree ID3(const My_Data &data)
{
    Decision_Tree tree,tree_temp;//����������Decision_Tree��һ�������tree,����һ����temp 
    double entropy=val_entropy(data);//entropy���ص���˼�� ˭���أ� 
    double gain,Att_E,temp=0.0;//gain�������ǣ�Att_E�������Ǳ���attribute���أ�temp�������� 
    for(vector<string>::const_iterator iter=data.attributes.begin();iter!=data.attributes.end()-1;++iter)//attribute��ѭ�� 
    {
        Att_E=att_entropy(*iter,data);
        gain=entropy-Att_E;// �õ���3.1.2����Ϣ��������������ؽ��͵ķ����� http://www.cnblogs.com/dztgc/archive/2013/04/22/3036529.html
        if(gain>temp)//�������ҵ��������������ҵ�������ֵ����Ϊ���ڵ� 
        {
            temp=gain;
            tree.set_root(*iter);
        }
    }
    if(tree.get_root()!="ROOT")//���root���޸ģ��ҳ����ʵ����ݣ����ҵ���ID3�㷨 
    {
        vector<string> branchs=att_val(tree.get_root(),data);//ѡ����������ӵ�еķ�֧ 
        for(vector<string>::const_iterator iter=branchs.begin();iter!=branchs.end();++iter)//ÿ����֧������һ�飬iter=sunny or wind  
        {
            My_Data new_data=pick_items(tree.get_root(),*iter,data);//�ó�����iter������ 
            tree_temp=ID3(new_data);//�ݹ����ID3 
            tree.set_branch(*iter,tree_temp);//��tree_temp����tree�������� 
        }
    }
    else
    {
        tree.set_leaf(true);//����Ҷ�ӽڵ� 
        tree.set_root((data.items[0])[data.col-1]);//��root���ó�Yes����No 
    }
    return tree;
}

int main()
{
    My_Data data=read_data("test.txt");//��test.txt��ȡ���� 
    show_data(data);
    Decision_Tree tree=ID3(data);//���������� 
    tree.show();
    return 1;
}
