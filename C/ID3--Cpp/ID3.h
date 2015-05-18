#ifndef ID3_H
#define ID3_H

#include <string>
#include <vector>
#include <map>
struct My_Data
{
    std::vector<std::string> attributes; //属性,是一个vector类的容器，可以塞进多个类型 
    std::vector< std::vector<std::string> > items;	//物品 ，同上 
    int row = 0;//行
    int col = 0;//列
};
class Decision_Tree
{
public:
    int set_leaf(bool val)//设置叶子 
    {
        leaf=val;
        return 1;
    }
    int set_root(std::string str)//设置根 
    {
        root=str;
        return 1;
    }
    int set_branch(std::string str,Decision_Tree tree)//设置分支 
    {
        branchs.insert(std::pair<std::string,Decision_Tree>(str,tree));
        return 1;
    }
    std::string get_root()//获得根 
    {
        return root;
    }
    int show(int num=0) const //显示整个决策树 
    {
        std::string temp="      ";
        if(leaf)
        {
            for(int i=0;i!=2+num;++i)//输出空白 
                std::cout<<temp;
            std::cout<<"+---Leaf: "<<root<<std::endl;
        }
        else
        {
            for(int i=0;i!=0+num;++i)
                std::cout<<temp;
            std::cout<<"+---Attribute:"<<root<<std::endl;//属性 
            for(std::map<std::string,Decision_Tree>::const_iterator iter=branchs.begin();iter!=branchs.end();++iter)
            {
                for(int i=0;i!=1+num;++i)
                    std::cout<<temp;
                std::cout<<"+---Branch:"<<iter->first<<std::endl;//分支 
                (iter->second).show(2+num);//采用递归 
            }
        }
        return 1;
    }
private:
    bool leaf=false;//默认设置不是叶子 
    std::string root="ROOT";
    std::map<std::string,Decision_Tree> branchs;//这种用法不太懂 
};
void show_data(const My_Data &data);//显示数据 
std::vector<std::string> att_val(const std::string &att,const My_Data &data);//返回vector类型的string 
My_Data read_data(const std::string &fname);//读取文件数据 
My_Data pick_items(const std::string &att,const std::string &val,const My_Data &data);//不懂 
double val_entropy(const My_Data &data);//不懂 
double att_entropy(const std::string &att,const My_Data &data);//不懂 
Decision_Tree ID3(const My_Data &data);//返回一个决策树 
#endif // ID3_H
