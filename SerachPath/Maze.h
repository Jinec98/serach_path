#pragma once
#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <string>
#include <vector>
#include "Point.h"

using namespace std;

//√‘π¨¿‡
class Maze
{
public:
	Maze();
	Maze(int rows, int cols);
	Maze(const Maze& m);
	~Maze();

	void setMaze(int rows, int cols);

	int cols, rows;
	vector<vector<Point*> > Map;
	Point startPoint, endPoint;
};

#endif // MAZE_H_INCLUDED
