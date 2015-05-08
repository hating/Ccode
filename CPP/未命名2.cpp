#include "graphics.h"
int main()
{
	initgraph(320,240);
	outtextxy(20,120,"Aloha World!");
	line(10,10,300,200);
	
	ege::getch();
	closegraph();
	return 0;
}
