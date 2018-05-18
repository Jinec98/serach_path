#pragma once
#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED

#include <cstdlib>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include "Point.h"
#include "Maze.h"
#include "myAlgorithm.h"

using namespace std;

class bfs
{
public:
	bfs();
	bfs(Maze &maze);

	Point* findPath(Point &startPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;

	int step;
	int keyStep;
	Maze m;
};

class dfs
{
public:
	dfs();
	dfs(Maze &maze);

	Point* findPath(Point &curPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;

	int step;
	int keyStep;
	Maze m;
};

class aStar
{
public:
	aStar();
	aStar(Maze &m);
	~aStar();

	Point* findPath(Point &startPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*> getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;

	Point* isInList(list<Point*> thisList, const Point *point) const;
	Point* getLeastFPoint();

	int calcG(Point *point);
	int calcH(Point *point, Point *endPoint);
	int calcF(Point *point);

	Maze m;
	int step;
	int keyStep;
	list<Point*> openList;
	list<Point*> closeList;
};

#endif // BFS_H_INCLUDED
