#include <iostream>
#include <cstdlib>
#include <cstring>
using std::cout;
using std::cin;
using std::string;
using std::endl;
class Screen 
{
	private:
		//Screen类的构造函数能够接收屏幕的宽和高两个整型参数（以像素为单位）
		//并存储在类的数据域中 
		static int height; //在Screen类中，将保存屏幕宽和高的数据域成员改为static int 类型。 
		static int width;
		string enter;//在Screen类中，添加两个string类型的数据成员enter和leave 
		string leave;
		static Screen* instance;//在Screen类中，增加一个Screen*类型的静态的私有数据成员instance； 
		static void check(int width,int height);
//		void attention(void);
		Screen();
	public:
		Screen(Screen &screen);
		~Screen();
//		void getScreen(void);
		void setScreen(int width,int height);
		static Screen* getInstance(int width,int height);//在Screen类中，增加一个静态公有的getInstance()函数，该函数返回instance的值。两个参数均带有默认值，分别为640，480.
		static void deleteInstance(void); 
};
class MyRectangle
{
	private:
	//MyRectangle类中的数据域有一个唯一与Screen类有关的成员，其类型为 Screen* 类型  
		Screen* myScreen;
		int leftX;
		int leftY;
		int rightX;
		int rightY;	
		int red;
		int green;
		int blue;
		void attention(void);
	public:
		void Draw(void);
		MyRectangle();
		MyRectangle(int leftX,int leftY,int rightX,int rightY);
		void setCoordinations(int leftX,int leftY,int rightX,int rightY);
		void setScreen(Screen&);
		void setColor(int R,int G,int B);
		 
};
class MyCircle
{
	private:
		int red;
		int green;
		int blue;
		int x;
		int y;
		int r;
	public:
		void setColor(int R,int G,int B);
		MyCircle(int x,int y,int r);
		MyCircle();
		MyCircle(MyCircle&);
		void setCenter(int x,int y);
		void setRadius(int r);
		void Draw();
		
};
int Screen::width=640;
int Screen::height=480;
Screen*    Screen::instance=NULL;
Screen::Screen()
{
	height=480;
	width=640;
	enter="enter screen";
	leave="leave screen" ;
	cout<<enter<<endl;
}
void Screen::check(int width,int height)
{
	if(width>1000||height>1000||width<=0||height<=0)
	{
		std::cout<<"invalid screen size"<<std::endl;
		exit(0);
	}
}
//void Screen::getScreen()
//{
//	//个人实现部分 
//	std::cout<<"The width is :\t"<<width<<std::endl;
//	std::cout<<"The height is :\t"<<height<<std::endl;
//	std::cout<<"======================================"<<std::endl;
//}
void Screen::setScreen(int width,int height)
{
	//个人实现部分 
	check(width,height);
	this->width=width;
	this->height=height;
}


//void Screen::attention(void)
//{
	//Screen类的所有构造函数均应输出字符串“screen”并换行 
//	std::cout<<"screen"<<std::endl;
//}
Screen* Screen::getInstance(int width=640,int height=480)
{
	if(instance!=NULL)
	{
		cout<<instance->width<<" "<<instance->height<<endl;
	}
	else {
		check(width,height);
		instance=new Screen;
		instance->height=480;
		instance->width=640;
	}
	return instance;	
 } 
void Screen::deleteInstance(void)
{
	delete instance;
}
Screen::~Screen()
{
	cout<<leave<<endl;
}
void MyRectangle::Draw(void)
{

	cout<<leftX<<" ";
	cout<<leftY<<" ";
	cout<<abs(rightX-leftX)<<" ";
	cout<<abs(rightY-leftY)<<endl;	
	cout<<red<<" "<<green<<" "<<blue<<endl;
}
MyRectangle::MyRectangle()
{
	//MyRectangle类的默认构造函数将对角线两个点的坐标均设置为原点坐标(0,0) 
	leftX=10;
	leftY=10;
	rightX=100;
	rightY=100;
	red=255;
	green=255;
	blue=255;
//	(*myScreen).Screen();//Still can't figure out how to initiate it .
	attention();
}
MyRectangle::MyRectangle(int leftX,int leftY,int rightX,int rightY)
{
	this->leftX=leftX;
	this->leftY=leftY;
	this->rightX=rightX;
	this->rightY=rightY;
	red=255;
	green=255;
	blue=255;
	attention();
}
void MyRectangle::setCoordinations(int leftX,int leftY,int rightX,int rightY)
{
	// MyRectangle类中应提供setCoordinations()用于设置对角线的左侧及右侧顶点坐标；
	//函数的参数的含义及类型和构造函数1的前4个参数相同。
	this->leftX=leftX;
	this->leftY=leftY;
	this->rightX=rightX;
	this->rightY=rightY;
}
void MyRectangle::setScreen(Screen& myScreen)
{
	this->myScreen=&myScreen;
}
void MyRectangle::attention(void)
// MyRectangle类的所有构造函数均应使用cout输出字符串“myrectangle”并换行
{
	cout<<"myrectangle"<<endl;
}
void MyRectangle::setColor(int R,int G,int B)
{
	red=R;
	green=G;
	blue=B;	
}
void	MyCircle::setColor(int R,int G,int B)
{
	red=R;
	green=G;
	blue=B;
}
MyCircle::MyCircle(int x,int y,int r)
{
	this->x=x;
	this->y=y;
	this->r=r;
	red=255;
	green=255;
	blue=255;
	cout<<"mycircle"<<endl;
}
MyCircle::MyCircle()
{
	x=200;
	y=200;
	r=100;
	red=255;
	green=255;
	blue=255;
	cout<<"mycircle"<<endl;	
}
MyCircle::MyCircle(MyCircle& inCircle)
{
	this->x=inCircle.x;
	this->y=inCircle.y;
	this->r=inCircle.r;
	this->red=inCircle.red;
	this->green=inCircle.green;
	this->blue=inCircle.blue;
}
void MyCircle::setCenter(int x,int y)
{
	this->x=x;
	this->y=y;
}
void MyCircle::setRadius(int r)
{
	this->r=r;
}

void MyCircle::Draw()
{
	Screen::getInstance();
	cout<<x<<" "<<y<<" "<<r<<endl;
	cout<<red<<" "<<green<<" "<<blue<<endl;
}
int main() {
  int width, height;
  cin >> width >> height;
  Screen::getInstance(width, height);
//  Screen::getInstance();
 
  int leftX, leftY, rightX, rightY;
  cin >> leftX >> leftY >> rightX >> rightY;
  MyRectangle myRectangle(leftX, leftY, rightX, rightY);
  myRectangle.setColor(0, 0, 0xff);
  myRectangle.Draw();
 
  int centerX, centerY, radius; 
  cin >> centerX >> centerY >> radius;
  MyCircle myCircles[2];
  (myCircles + 1)->setCenter(centerX, centerY);
  myCircles[1].setRadius(radius);
  myCircles[0].Draw();
  myCircles[1].Draw();
  
  MyCircle myCircle(myCircles[1]);
  myCircle.Draw();
   
  Screen::deleteInstance();
   
  cin.get();
  return 0;
}
