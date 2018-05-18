#pragma once
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <cstdlib>
#include <vector>

class Point
{
public:
	Point();
	Point(int x, int y, int n);
	Point(const Point &p);
	bool operator== (const Point &p);

	int x, y, n;
	int F, G, H;
	Point *parent;
};

#endif // POINT_H_INCLUDED
