#include "Maze.h"

//构造函数
Maze::Maze() {}
Maze::Maze(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
}

//拷贝构造函数
Maze::Maze(const Maze &m)
{
	rows = m.rows;
	cols = m.cols;
	startPoint = m.startPoint;
	endPoint = m.endPoint;
	Map = m.Map;
	Map.resize(m.rows);
	for (unsigned int i = 0; i < Map.size(); i++)
		Map[i].resize(m.cols);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			Map[i][j] = new Point(*m.Map[i][j]);
}
Maze::~Maze()
{

}

//用于初始化二维vector的大小
void Maze::setMaze(int rows, int cols)
{
	Map.resize(rows);
	for (unsigned int i = 0; i < Map.size(); i++)
		Map[i].resize(cols);
}
