#include "Point.h"

Point::Point() {}
Point::Point(int x, int y, int n)
{
	this->x = x;
	this->y = y;
	this->n = n;
	F = 0;
	G = 0;
	H = 0;
	parent = NULL;
}
Point::Point(const Point &p)
{
	x = p.x;
	y = p.y;
	n = p.n;
	F = p.F;
	G = p.G;
	H = p.H;
	parent = p.parent;
}

bool Point::operator==(const Point & p)
{
	return x == p.x && y == p.y && n == p.n && F == p.F && G == p.G && H == p.H && parent == p.parent;
}

