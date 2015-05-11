#ifndef ID3_H
#define ID3_H

#include <string>
#include <vector>
#include <map>
struct My_Data
{
    std::vector<std::string> attributes; //���� 
    std::vector< std::vector<std::string> > items;	//��Ʒ 
    int row = 0;//��
    int col = 0;//��
};
class Decision_Tree
{
public:
    int set_leaf(bool val)//����Ҷ�� 
    {
        leaf=val;
        return 1;
    }
    int set_root(std::string str)//���ø� 
    {
        root=str;
        return 1;
    }
    int set_branch(std::string str,Decision_Tree tree)//���÷�֧ 
    {
        branchs.insert(std::pair<std::string,Decision_Tree>(str,tree));
        return 1;
    }
    std::string get_root()//��ø� 
    {
        return root;
    }
    int show(int num=0) const //��ʾ���������� 
    {
        std::string temp="      ";
        if(leaf)
        {
            for(int i=0;i!=2+num;++i)//����հ� 
                std::cout<<temp;
            std::cout<<"+---Leaf: "<<root<<std::endl;
        }
        else
        {
            for(int i=0;i!=0+num;++i)
                std::cout<<temp;
            std::cout<<"+---Attribute:"<<root<<std::endl;//���� 
            for(std::map<std::string,Decision_Tree>::const_iterator iter=branchs.begin();iter!=branchs.end();++iter)
            {
                for(int i=0;i!=1+num;++i)
                    std::cout<<temp;
                std::cout<<"+---Branch:"<<iter->first<<std::endl;//��֧ 
                (iter->second).show(2+num);//���õݹ� 
            }
        }
        return 1;
    }
private:
    bool leaf=false;//Ĭ�����ò���Ҷ�� 
    std::string root="ROOT";
    std::map<std::string,Decision_Tree> branchs;//�����÷���̫�� 
};
void show_data(const My_Data &data);//��ʾ���� 
std::vector<std::string> att_val(const std::string &att,const My_Data &data);//����vector���͵�string 
My_Data read_data(const std::string &fname);//��ȡ�ļ����� 
My_Data pick_items(const std::string &att,const std::string &val,const My_Data &data);//���� 
double val_entropy(const My_Data &data);//���� 
double att_entropy(const std::string &att,const My_Data &data);//���� 
Decision_Tree ID3(const My_Data &data);//����һ�������� 
#endif // ID3_H
