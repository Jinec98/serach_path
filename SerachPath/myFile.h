#pragma once
#ifndef MYFILE_H_INCLUDED
#define MYFILE_H_INCLUDED

#include <string>
#include <list>
#include <fstream>
#include "Maze.h"
#include "Point.h"

//文件处理基类
class myFile
{
public :
	myFile();
	~myFile();

	string fileName;
	Maze *maze;
};

//读文件类，继承于文件处理类
class openFile : public myFile
{
public:
	openFile();
	openFile(const string fileName);
	~openFile();

	Maze& getMaze();
};

//写文件类，继承于文件处理类
class writeFile : public myFile
{
public:
	writeFile();
	writeFile(const string fileName, Maze *maze);
	~writeFile();

	void writeMaze(list<Point*> path, string step);
};

#endif // MYFILE_H_INCLUDED
