#include <stdio.h>
#include <vector>

class Point
{
private:
	int x, y;
	
public:
	Point *parent;
	int f, g, h;
	int search;
	int visited;
	int getX(){ return x;}
	int getY(){ return y;}
	void setX(int x0) {x = x0;}
	void setY(int y0) {y = y0;}
	Point(int x0, int y0)
	{
		x = x0;
		y = y0;
		f = 0;
		g = 0;
		h = 0;
		search = 0;
		parent = NULL;
		visited = -1;
	}
	Point()
	{
		x = -1;
		y = -1;
		f = -1;
		g = 0;
		h = 0;
		search = 0;
		parent = NULL;
		visited = -1;
	}
};


