#pragma once
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <cstdlib>
#include <vector>

//迷宫中的点类
class Point
{
public:
	Point();
	Point(int x, int y, int n);
	Point(const Point &p);
	bool operator== (const Point &p);

	int x, y, n;//坐标及该点状态
	int F, G, H;//用于启发式算法
	Point *parent;
};

#endif // POINT_H_INCLUDED
