#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>


using std::cout;
using std::endl;
using std::cin;
using std::string;


class Screen
{
	private:
		static int height;
		static int width;
		string enter;
		string leave;
		static Screen* instance;
		static void check(int width,int height);
		Screen();
	public:
		Screen(Screen &screen);
		~Screen();
		void setScreen(int width,int height);
		static Screen* getInstance(int width,int height);
		static void deleteInstance(void);	
};
int Screen::width=640;
int Screen::height=480;
Screen*   Screen::instance=NULL;
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
void Screen::setScreen(int width,int height)
{
	check(width,height);
	this->width=width;
	this->height=height;
}
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


class MyShape {
	protected:
		int R_;
		int G_;
		int B_;
		string enter;
		string leave;
	public:
		MyShape();
		MyShape(int R,int G,int B);
		~MyShape();
		void getMyShape(void);
		void setColor(int R,int G,int B);
		virtual void Draw()=0;
};
MyShape::MyShape()
{
	int R_=255;
	int G_=255;
	int B_=255;
	enter="enter mycircle";
	leave="leave mycircle";
}
MyShape::MyShape(int R,int G,int B)
{
	R_=R;
	G_=G;
	B_=B;
	enter="enter mycircle";
	leave="leave mycircle";
}
MyShape::~MyShape()
{
	//Unfinished
}
void MyShape::getMyShape(void)
{
	cout<<"R="<<R_<<" "<<"G="<<G_<<" "<<"B="<<B_<<endl;
}
void MyShape::setColor(int R,int G,int B)
{
	R_=R;
	G_=G;
	B_=B;	
}


class MyRectangle:public MyShape
{
	private:
		int leftX_;
		int leftY_;
		int rightX_;
		int rightY_;
	public:
		MyRectangle();
		MyRectangle(int leftX,int leftY,int rightX,int rightY);
		void setCoordinations(int leftX,int leftY,int rightX,int rightY);
		void Draw(void);
		//Unfinished	
};

MyRectangle::MyRectangle():MyShape()
{
	leftX_=10;
	leftY_=10;
	rightX_=100;
	rightY_=100;
	cout<<"myrectangle"<<endl;
}
MyRectangle::MyRectangle(int leftX,int leftY,int rightX,int rightY):MyShape()
{
	leftX_=leftX;
	leftY_=leftY;
	rightX_=rightX;
	rightY_=rightY;
	cout<<"myrectangle"<<endl;
}
void MyRectangle::setCoordinations(int leftX,int leftY,int rightX,int rightY)
{
	leftX_=leftX;
	leftY_=leftY;
	rightX_=rightX;
	rightY_=rightY;	
}
void MyRectangle::Draw(void)
{
	Screen::getInstance();
	cout<<leftX_<<" ";
	cout<<leftY_<<" ";
	cout<<abs(rightX_-leftX_)<<" ";
	cout<<abs(rightY_-leftY_)<<endl;	
	cout<<R_<<" "<<G_<<" "<<B_<<endl;	
}


class MyCircle:public MyShape
{
	private:
		int x_;
		int y_;
		int r_;
	public:
		MyCircle();
		MyCircle(int x,int y,int r);
		MyCircle(MyCircle& inCircle);
		void setCenter(int x,int y);
		void setRadius(int r);
		void Draw(void);
		//Unfinished
};
MyCircle::MyCircle():MyShape()
{
	x_=200;
	y_=200;
	r_=100;
	cout<<"mycircle"<<endl;
}
MyCircle::MyCircle(int x,int y,int r):MyShape()
{
	x_=x;
	y_=y;
	r_=r;
	cout<<"mycircle"<<endl;
}
MyCircle::MyCircle(MyCircle& inCircle):MyShape(inCircle.R_,inCircle.G_,inCircle.B_)
{
	x_=inCircle.x_;
	y_=inCircle.y_;
	r_=inCircle.r_;
	cout<<"mycircle"<<endl;

}
void MyCircle::setCenter(int x,int y)
{
	x_=x;
	y_=y;
}
void MyCircle::setRadius(int r)
{
	r_=r;
}
void MyCircle::Draw(void)
{
	Screen::getInstance();
	cout<<x_<<" "<<y_<<" "<<r_<<endl;
	cout<<R_<<" "<<G_<<" "<<B_<<endl;	
}
MyShape* createShape(char shapeType)
{
	MyShape* pShape=NULL;
	switch (shapeType)
	{
	case 'c':
			pShape=new MyCircle();
			break;
	case 'r':
			pShape=new MyRectangle();
			break;
    } 
	return pShape;
}

int main() {
  const int SHAPENUMBER = 5;
  Screen::getInstance();
//  Screen::getInstance();
   
  char shapeType;
  MyShape* shapes[SHAPENUMBER];
  for(int i = 0; i < SHAPENUMBER; i++) {
    cout << "input shape type" << endl;
    cin >> shapeType;
    shapes[i] = createShape(shapeType);
  }
   
  MyRectangle* myrectangle;
  MyCircle* mycircle;
  for(int i = 0; i < SHAPENUMBER; i++) {
    mycircle = dynamic_cast<MyCircle*>(shapes[i]);
    myrectangle = dynamic_cast<MyRectangle*>(shapes[i]);
    if ( (mycircle != 0) || (myrectangle != 0)) {
      shapes[i]->setColor(shapeType+i, shapeType+2*i, shapeType+3*i);
      if( typeid(*shapes[i]) == typeid(MyRectangle)) {
        myrectangle -> setCoordinations(10+10*i, 10+10*i, 400+10*i, 200+10*i); 
      } else {
        mycircle -> setCenter(200+10*i, 200+10*i);
        mycircle -> setRadius(50+10*i);
      }   
      shapes[i]->Draw();
    } else {
      cout << "invalid shape" << endl;
    }      
  }
   
  for(int i = 0; i< SHAPENUMBER; i++) {
      delete shapes[i];
  }
   
  Screen::deleteInstance();
   
  cin.get();
  return 0;
}
