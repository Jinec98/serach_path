#pragma once
#ifndef MYFILE_H_INCLUDED
#define MYFILE_H_INCLUDED

#include <string>
#include <list>
#include <fstream>
#include "Maze.h"
#include "Point.h"

class openFile
{
public:
	openFile();
	openFile(const string fileName);
	~openFile();

	Maze& getMaze();

private:
	string fileName;
	Maze *maze;
};

class writeFile
{
public:
	writeFile();
	writeFile(const string fileName, Maze *maze);
	~writeFile();

	void writeMaze(list<Point*> path, string step);

private:
	string fileName;
	Maze *maze;
};

#endif // MYFILE_H_INCLUDED
