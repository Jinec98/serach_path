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

//���ڴ��ļ��������ļ��е���Ϣת����Maze�����е���Ϣ
Maze& openFile::getMaze()
{
	//���ļ���ת����const string���Ͳ��򿪸��ļ�
	ifstream OpenFile(fileName.c_str());
	int rows = 1;

	OpenFile >> maze->rows >> maze->cols;
	OpenFile.get();

	//���õ����Թ�����Χ���һȦǽ
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

	//���ļ�
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

//����д�ļ�����·��������д���ļ���
void writeFile::writeMaze(list<Point*> path, string step)
{
	//���ļ���ת����const string���ͣ��������ļ������
	ofstream writeFile(fileName.c_str());

	//���ӵ�֮ǰ�Թ�������Χ��һȦǽ�������Թ�����Ϣд���ļ��У���·��������ĿҪ���ԡ�*������ʽ��ʾ
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
	writeFile << "��·�����裺" << step << "��\n" << "·��������Ϊ��\n";
	for (auto &p : path)
		writeFile << "(" << p->x << "," << p->y << ")\n";

	writeFile.close();
}
