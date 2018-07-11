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

class myAlgorithm 
{
public:
	myAlgorithm();
	myAlgorithm(Maze &maze);
	~myAlgorithm();

	virtual Point* findPath(Point &startPoint, Point &endPoint) = 0;
	virtual list<Point*> getPath(Point *result) = 0;
	virtual vector<Point*>getSurroundPoints(const Point *point) const = 0;
	virtual bool isCanReach(const Point *point, const Point *target) const = 0;

	int step;
	int keyStep;
	Maze maze;
};

class bfs : public myAlgorithm
{
public:
	bfs();
	bfs(Maze &maze);
	~bfs();

	Point* findPath(Point &startPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;
};

class dfs : public myAlgorithm
{
public:
	dfs();
	dfs(Maze &maze);
	~dfs();

	Point* findPath(Point &curPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;

};

class aStar : public myAlgorithm
{
public:
	aStar();
	aStar(Maze &maze);
	~aStar();

	Point* findPath(Point &startPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;
	Point* isInList(list<Point*> thisList, const Point *point) const;
	Point* getLeastFPoint();

	int calcG(Point *point);
	int calcH(Point *point, Point *endPoint);
	int calcF(Point *point);

	list<Point*> openList;
	list<Point*> closeList;
};

class idaStar : public myAlgorithm
{
public:
	idaStar();
	idaStar(Maze &maze);
	~idaStar();

	Point* findPath(Point &startPoint, Point &endPoint);
	list<Point*> getPath(Point *result);
	vector<Point*>getSurroundPoints(const Point *point) const;
	bool isCanReach(const Point *point, const Point *target) const;
	Point* idaSerach(Point *point, Point &endPoint, int maxF);

	int calcG(Point *point);
	int calcH(Point *point, Point *endPoint);
	int calcF(Point *point);
};

#endif // BFS_H_INCLUDED
