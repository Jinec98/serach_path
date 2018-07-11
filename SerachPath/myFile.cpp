#include "myFile.h"

myFile::myFile() {}
myFile::~myFile() {}

openFile::openFile() {}
openFile::openFile(const string fileName)
{
	this->fileName = fileName;
	maze = new Maze();
}
openFile::~openFile() {}

//用于打开文件，并将文件中的信息转换成Maze对象中的信息
Maze& openFile::getMaze()
{
	//将文件名转换成const string类型并打开该文件
	ifstream OpenFile(fileName.c_str());
	int rows = 1;

	OpenFile >> maze->rows >> maze->cols;
	OpenFile.get();

	//将得到的迷宫最外围添加一圈墙
	maze->rows += 2;
	maze->cols += 2;
	maze->setMaze(maze->rows, maze->cols);

	for (int i = 0; i < maze->rows; i++)
	{
		for (int j = 0; j < maze->cols; j++)
		{
			if (i == 0 || i == maze->rows - 1 || j == 0 || j == maze->cols - 1)
			{
				maze->Map[i][j] =  new Point(i, j, 1);
			}
			else
				continue;
		}
	}

	//读文件
	while (!OpenFile.eof())
	{
		string str;
		getline(OpenFile, str);
		int len = str.length();
		for (int i = 0; i<len; i++)
		{
			if (str[i] == ' ')
				maze->Map[rows][i + 1] =  new Point(rows, i + 1, 0);
			else if (str[i] == 'X')
				maze->Map[rows][i + 1] =  new Point(rows, i + 1, 1);
			else if (str[i] == 'S')
			{
				maze->Map[rows][i + 1] =  new Point(rows, i + 1, 2);
				maze->startPoint = Point(*maze->Map[rows][i + 1]);
			}
			else if (str[i] == 'D')
			{
				maze->Map[rows][i + 1] =  new Point(rows, i + 1, 3);
				maze->endPoint = Point(*maze->Map[rows][i + 1]);
			}
		}
		rows++;
	}

	OpenFile.close();

	return *maze;
}

writeFile::writeFile() {}
writeFile::writeFile(const string fileName, Maze *maze)
{
	this->fileName = fileName;
	this->maze = maze;
}
writeFile::~writeFile() {}

//用于写文件，将路径及步数写入文件中
void writeFile::writeMaze(list<Point*> path, string step)
{
	//将文件名转换成const string类型，并打开其文件输出流
	ofstream writeFile(fileName.c_str());

	//忽视掉之前迷宫中最外围的一圈墙，并将迷宫的信息写入文件中，将路径按照题目要求以“*”的形式表示
	string *str = new string[maze->rows - 2];
	for (int i = 1; i<maze->rows - 1; i++)
	{
		for (int j = 1; j<maze->cols - 1; j++)
		{
			if (maze->Map[i][j]->n > 10)
				str[i - 1] += "*";
			else if (maze->Map[i][j]->n <= 0)
				str[i - 1] += " ";
			else if (maze->Map[i][j]->n == 1)
				str[i - 1] += "X";
			else if (maze->Map[i][j]->n == 2)
				str[i - 1] += "S";
			else if (maze->Map[i][j]->n == 3)
				str[i - 1] += "D";
		}
		str[i - 1] += "\n";
	}
	for (int i = 0; i<maze->rows - 2; i++)
		writeFile << str[i];
	writeFile << "该路径共需：" << step << "步\n" << "路径的坐标为：\n";
	for (auto &p : path)
		writeFile << "(" << p->x << "," << p->y << ")\n";

	writeFile.close();
}
