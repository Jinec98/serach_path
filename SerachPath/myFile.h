#pragma once
#ifndef MYFILE_H_INCLUDED
#define MYFILE_H_INCLUDED

#include <string>
#include <list>
#include <fstream>
#include "Maze.h"
#include "Point.h"

class myFile
{
public :
	myFile();
	~myFile();

	string fileName;
	Maze *maze;
};

class openFile : public myFile
{
public:
	openFile();
	openFile(const string fileName);
	~openFile();

	Maze& getMaze();
};

class writeFile : public myFile
{
public:
	writeFile();
	writeFile(const string fileName, Maze *maze);
	~writeFile();

	void writeMaze(list<Point*> path, string step);
};

#endif // MYFILE_H_INCLUDED
