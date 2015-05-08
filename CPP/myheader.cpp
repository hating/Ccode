#include "myheader.h"
#include <iostream>
#include <cstdlib>
Screen::Screen()
{
	height=480;
	width=640;
}
Screen::Screen(int width,int height)
{
	check(width,height);
	this->width=width;
	this->height=height;
}
void Screen::check(int width,int height)
{
	if(width>1000||height>1000)
	{
		exit(998);
	}
}
void Screen::getScreen()
{
	std::cout<<"The width is :\t"<<width<<std::endl;
	std::cout<<"The height is :\t"<<height<<std::endl;
	std::cout<<"======================================"<<std::endl;
}
void Screen::setScreen(int width,int height)
{
	check(width,height);
	std::cout<<"The previous width is :\t"<<this->width<<std::endl;
	std::cout<<"The previous height is :\t"<<this->height<<std::endl;
	this->width=width;
	this->height=height;
	std::cout<<"Now the width is :\t"<<this->width<<std::endl;
	std::cout<<"Now the height is :\t"<<this->height<<std::endl;
	
}
void Screen::attention(void)
{
	std::cout<<"screen"<<std::endl;
}
bool Screen::match(int rightX,int rightY)
{
	if(rightX<width&&rightY<height)
	{
		return true;
	}
	return false;
}

void MyRectangle::Draw(void)
{
	if(check())
	{
		//The check function is not complete.
	std::cout<<"The leftX is :\t"<<leftX<<std::endl;
	std::cout<<"The leftY is :\t"<<leftY<<std::endl;
	std::cout<<"The height of the rectalgle is :\t"<<rightY-leftY<<std::endl;
	std::cout<<"The width of the rectalgle is :\t"<<rightX-leftX<<std::endl;	
	}
	else 
	{
		std::cout<<"invalid myrectangle"<<std::endl;
	}
}
MyRectangle::MyRectangle()
{
	leftX=0;
	leftY=0;
	rightX=0;
	rightY=0;
//	(*myScreen).Screen();//Still can't figure out how to initiate it . 
}
MyRectangle::MyRectangle(int leftX,int leftY,int rightX,int rightY,Screen* myScreen)
{
	this->leftX=leftX;
	this->leftY=leftY;
	this->rightX=rightX;
	this->rightY=rightY;
	this->myScreen=myScreen;
}
void MyRectangle::setCoordinations(int leftX,int leftY,int righeX,int rightY)
{
	this->leftX=leftX;
	this->leftY=leftY;
	this->rightX=rightX;
	this->rightY=rightY;
}
void MyRectangle::setScreen(Screen& myScreen)
{
	this->myScreen=&myScreen;
}
void MyRectangle::getAll(void)
{
	
	std::cout<<"leftX="<<leftX<<std::endl;
	std::cout<<"leftY="<<leftX<<std::endl;
	std::cout<<"rightX="<<leftX<<std::endl;
	std::cout<<"rightY="<<leftX<<std::endl;
	(*myScreen).getScreen();
//Maybe invade	std::cout<<"Screen height="<<myscreen-><<std::endl;
}
bool MyRectangle::check(void)
{
	if(leftX<rightX&&leftY<rightY)
	{
		return myScreen->match(rightX,rightY);
	}
	return false;
}
