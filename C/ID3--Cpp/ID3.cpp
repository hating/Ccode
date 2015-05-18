/*
 Read raw data from test.txt

 Powered by fenglinglu.

*/
#include <iostream>//标准输入输出函数库 
#include <fstream>//文件输入输出库 
#include <sstream>
#include <string>//字符串库 
#include <vector>//容器 
#include <algorithm>// 不明白 
#include <cmath>//数学函数 
#include <map>
#include "ID3.h"
using namespace std;


void show_data(const My_Data &data)
{
    for(vector<string>::const_iterator iter = data.attributes.begin();iter != data.attributes.end();++iter)//输出arrtibutes，每个不同的arrtibute之间分割一个“ ”，输出完成后，换行。 
        cout <<*iter<<" ";
    cout<<endl;
    cout<<data.col<<endl;//输出行数 
    for(vector< vector<string> >::const_iterator iter1=data.items.begin();iter1!=data.items.end();++iter1)//双重嵌套循环，就是为了把item输出来。 
    {
        for(vector<string>::const_iterator iter2 = (*iter1).begin();iter2 != (*iter1).end();++iter2)
            cout<<*iter2<<" ";
        cout<<endl;//换行 
    }
    cout<<data.row<<endl;//输出行数 
}
vector<string> att_val(const string &att,const My_Data &data)
{
    vector<string> val;
    string value;
    vector<string>::const_iterator iter_temp;
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//遍历每一条数据 
    {
        iter_temp=find(data.attributes.begin(),data.attributes.end(),att);//找到想找的attribute类型 
        value=(*iter)[iter_temp-data.attributes.begin()];//计算这个类型与arributes头部的距离 
        if(find(val.begin(),val.end(),value)==val.end())//如果没有这种属性，那就push到val容器中 
            val.push_back(value);
    }
    return val;//返回val容器 
}
My_Data read_data(const string &fname)//读取文件函数 
{
    My_Data my_data; //建立一个My_Data的结构体，名称是my_data 
    ifstream data_file;	//建立一个ifstream类的data_file，用于从文件中读取数据，可以用FILE替代（这一段都可以自己重新实现） 
    data_file.open(fname.c_str(),ios::in);//使用ifstream的成员函数读取文件 ，string.c_str返回的是fname的首字符地址，函数原型void open (const   char* filename,  ios_base::openmode mode = ios_base::in);
    if(!data_file)//如果data_file没有东西的话，就做出错处理 
        cout << "ERROR!" <<endl;
    else
    {
        string line,word;//建立line和word的string 
        getline(data_file,line);//从data_file里面找到标志所在行的字符串 
        istringstream stream(line);// istringstream对象可以绑定一行字符串，然后以空格为分隔符把该行分隔开来。http://blog.csdn.net/xiayang05/article/details/5933893
        while(stream>>word)//从流中读取word，直到流中没有数据 
            my_data.attributes.push_back(word);//把word推入到My_Data的vector容器中 
        my_data.col = my_data.attributes.size();//完成attributes的推入后，计算行数 
        while(getline(data_file,line))//读取剩下的每一行 
        {
            vector<string> v_str;//建立一个临时的vector<string> 
            istringstream stream(line);//把当前行字符拆开 
            while(stream>>word)//如果流中还有字符 
                v_str.push_back(word);//塞进v_str中 
            my_data.items.push_back(v_str);//等v_str塞完，就塞到my_data中去 
        }
        my_data.row = my_data.items.size();//读取列数 
        data_file.close();//关闭文件 
    }
    return my_data;//返回my_data这个结构体 
}
My_Data pick_items(const string &att,const string &val,const My_Data &data)//筛选出符合条件的数据组成新的数据 
{
    My_Data new_data;
    vector<string> item;
    vector<string>::const_iterator iter_temp;
    iter_temp=find(data.attributes.begin(),data.attributes.end(),att);
    if(iter_temp==data.attributes.end())//错误处理 
        cout<<"ERROR!"<<endl;
    else
    {
        int num=iter_temp-data.attributes.begin();//计算所筛选的attribute与attribute的距离 
        for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//遍历旧data 
            if((*iter)[num]==val)//如果与val相等 
                new_data.items.push_back(*iter);//加到新data上面去 
        new_data.attributes=data.attributes;//完成复制 
        new_data.col=data.col;//完成复制 
        new_data.row=new_data.items.size();//这里是与旧data不同的地方 
    }
    return new_data;
}

/**
为了精确地定义信息增益，我们先定义信息论中广泛使用的一个度量标准，称为熵（entropy），它刻画了任意样例集的纯度（ purity）。
给定包含关于某个目标概念的正反样例的样例集S ，那么S 相对这个布尔型分类的熵为： 
Entropy(S ) =-P⊕log2P⊕-PΘlog2PΘ 
其中P⊕ 是在S 中正例的比例，PΘ是在S 中负例的比例。在有关熵的所有计算中我们定义0 log0 为0 。
举例说明，假设S 是一个关于某布尔概念的有 14 个样例的集合，它包括 9 个正例和5 个反例（我们采用记号[9+ ，5 -]来概括这样的数据样例）。
那么S 相对于这个布尔分类的熵（Entropy）为： 
Entropy([9+,5-]) =-(9/14)log2(9/14) - (5/14)log2(5/14)
 **/ 
double val_entropy(const My_Data &data)//以const方式传入data ，返回计算的熵值 
{
    vector<string> S;//建立了一个S的容器，用处在后头 
    vector<string>::const_iterator iter_temp;//iter_temp也不知道有什么用 
    vector<int> S_Count;//熵值的计算？ 
    int S_Sum=data.items.size();//S_Sum里存的是全部item的数量 
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)//iter是一个二重vector的指针，循环扫描每一行的数据 
    {
        iter_temp=find(S.begin(),S.end(),(*iter)[data.col-1]);// 在S.begin到S.end之间找到(*iter)[data.col-1]，这个是Yes/No
        if(iter_temp==S.end())//如果没有找到(*iter)[data.col-1] 
        {
            S.push_back((*iter)[data.col-1]);//把(*iter)[data.col-1]塞到S中（这样子下次就可以找到了） 
            S_Count.push_back(1);//记录第一个S_Count 
        }
        else
            ++S_Count[iter_temp-S.begin()];//计算Yes和No的数量 
    }
    vector<double> P(S_Count.size(),0.0);
    double I=0.0;
    for(int i=0;i!=P.size();++i)
    {
        P[i]=static_cast<double>(S_Count[i])/S_Sum;//P[i] 
        I=I-P[i]*log2(P[i]);
    }
    return I;//I=0.9402，这究竟是谁的熵值呢？ 
}
double att_entropy(const string &att,const My_Data &data)//计算attribute的熵值的函数 
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
    Decision_Tree tree,tree_temp;//建立了两个Decision_Tree，一个是真的tree,另外一个是temp 
    double entropy=val_entropy(data);//entropy是熵的意思， 谁的熵？ 
    double gain,Att_E,temp=0.0;//gain的作用是，Att_E的作用是保存attribute的熵，temp的作用是 
    for(vector<string>::const_iterator iter=data.attributes.begin();iter!=data.attributes.end()-1;++iter)//attribute的循环 
    {
        Att_E=att_entropy(*iter,data);//太复杂，待完成 
        gain=entropy-Att_E;// 用的是3.1.2用信息增益度量期望的熵降低的方法， http://www.cnblogs.com/dztgc/archive/2013/04/22/3036529.html
        if(gain>temp)//类似于找到最大的数，这里找到熵最大的值，作为根节点 
        {
            temp=gain;
            tree.set_root(*iter);
        }
    }
    if(tree.get_root()!="ROOT")//如果ROOT节点已经存在 
    {
        vector<string> branchs=att_val(tree.get_root(),data);
        for(vector<string>::const_iterator iter=branchs.begin();iter!=branchs.end();++iter)
        {
            My_Data new_data=pick_items(tree.get_root(),*iter,data);
            tree_temp=ID3(new_data);//递归调用ID3 
            tree.set_branch(*iter,tree_temp);
        }
    }
    else
    {
        tree.set_leaf(true);
        tree.set_root((data.items[0])[data.col-1]);
    }
    return tree;
}

int main()
{
    My_Data data=read_data("test.txt");//从test.txt读取数据 
    show_data(data);
    Decision_Tree tree=ID3(data);//创建决策树 
    tree.show();
    return 1;
}
