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
		//Screen��Ĺ��캯���ܹ�������Ļ�Ŀ�͸��������Ͳ�����������Ϊ��λ��
		//���洢������������� 
		static int height; //��Screen���У���������Ļ��͸ߵ��������Ա��Ϊstatic int ���͡� 
		static int width;
		string enter;//��Screen���У��������string���͵����ݳ�Աenter��leave 
		string leave;
		static Screen* instance;//��Screen���У�����һ��Screen*���͵ľ�̬��˽�����ݳ�Աinstance�� 
		static void check(int width,int height);
//		void attention(void);
		Screen();
	public:
		Screen(Screen &screen);
		~Screen();
//		void getScreen(void);
		void setScreen(int width,int height);
		static Screen* getInstance(int width,int height);//��Screen���У�����һ����̬���е�getInstance()�������ú�������instance��ֵ����������������Ĭ��ֵ���ֱ�Ϊ640��480.
		static void deleteInstance(void); 
};
class MyRectangle
{
	private:
	//MyRectangle���е���������һ��Ψһ��Screen���йصĳ�Ա��������Ϊ Screen* ����  
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
//	//����ʵ�ֲ��� 
//	std::cout<<"The width is :\t"<<width<<std::endl;
//	std::cout<<"The height is :\t"<<height<<std::endl;
//	std::cout<<"======================================"<<std::endl;
//}
void Screen::setScreen(int width,int height)
{
	//����ʵ�ֲ��� 
	check(width,height);
	this->width=width;
	this->height=height;
}


//void Screen::attention(void)
//{
	//Screen������й��캯����Ӧ����ַ�����screen�������� 
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
	//MyRectangle���Ĭ�Ϲ��캯�����Խ�������������������Ϊԭ������(0,0) 
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
	// MyRectangle����Ӧ�ṩsetCoordinations()�������öԽ��ߵ���༰�Ҳඥ�����ꣻ
	//�����Ĳ����ĺ��弰���ͺ͹��캯��1��ǰ4��������ͬ��
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
// MyRectangle������й��캯����Ӧʹ��cout����ַ�����myrectangle��������
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
