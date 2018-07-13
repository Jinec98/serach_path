#include "myAlgorithm.h"

myAlgorithm::myAlgorithm() {}

//基类构造函数
myAlgorithm::myAlgorithm(Maze &maze)
{
	step = -1;
	keyStep = 11;
	this->maze = maze;
}

myAlgorithm::~myAlgorithm() {}


//bfs类的构造函数，传入Maze类型的引用
bfs::bfs() {}
bfs::bfs(Maze &maze) : myAlgorithm(maze) {}
bfs::~bfs() {}

//广度优先搜索的核心代码，用于搜索路径，传入起点和终点的引用
Point* bfs::findPath(Point &startPoint, Point &endPoint)
{
	//广度优先搜索运用了队列
	queue<Point*> q;
	q.push(&startPoint);

	while (!q.empty())
	{
		//得到队首的点并将其出队
		Point* curPoint = q.front();
		//若果是之前已经遍历过的点则跳过当前循环
		if (curPoint->n < 0)
		{
			q.pop();
			continue;
		}
		//将这个点进行标记，并用计数器step表示遍历的是第几个点
		if (curPoint->x != maze.startPoint.x || curPoint->y != maze.startPoint.y)
		{
			curPoint->n = step;
			step--;
		}
		q.pop();

		//得到当前点周围能够到达的点
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		//遍历能够到达的所有点
		for (auto &target : surroundPoints)
		{
			//将能够到达的点的parent指针指向当前点
			target->parent = curPoint;
			//如果找到终点，则返回那个带你的指针
			if (target->x == endPoint.x && target->y == endPoint.y)
				return target;
			//将能够到达的点入队
			q.push(target);
		}
	}
	return NULL;
}

//用于得到最佳路径，传入的参数为找到的终点的指针
list<Point*> bfs::getPath(Point *result)
{
	//表示最佳路径，由于0,1都被占用故从11开始，最后将结果-10即可
	keyStep = 11;
	//用于存储路径的列表
	list<Point*> path;
	while (result)
	{
		//运用了树和链表的思想从终点开始遍历parent指针
		if ((result->x != maze.startPoint.x || result->y != maze.startPoint.y) && (result->x != maze.endPoint.x || result->y != maze.endPoint.y))
		{
			result->n = keyStep;
			keyStep++;
		}
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

//用于得到某个点周围能够到达的所有点
vector<Point*> bfs::getSurroundPoints(const Point *point) const
{
	//用于存储能够到达的所有点
	vector<Point*> surroundPoints;

	//遍历方向
	int dx[4] = { 0,-1,0,1 };
	int dy[4] = { 1,0,-1,0 };

	for (int i = 0; i<4; i++)
	{
		int x = point->x + dx[i];
		int y = point->y + dy[i];
		//判断该点能否到达，若能则加入vector
		if (isCanReach(point, maze.Map[x][y]))
		{
			surroundPoints.push_back(maze.Map[x][y]);
		}

	}

	return surroundPoints;
}

//用于判断某个点能否到达目标点
bool bfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}


//深度优先搜索运用了栈
stack<Point*> s;
//dfs类的构造函数
dfs::dfs() {}
dfs::dfs(Maze &maze) : myAlgorithm(maze) {}
dfs::~dfs() {}

//深度优先搜索算法的核心代码，用于寻找路径，传入的是当前点和终点的引用
Point* dfs::findPath(Point &curPoint, Point &endPoint)
{
	s.push(&curPoint);
	//若该点已经已经遍历过则直接return
	if (curPoint.n < 0)
	{
		s.pop();
		return NULL;
	}
	//将这个点进行标记，并用计数器step表示遍历的是第几个点
	if (curPoint.x != maze.startPoint.x || curPoint.y != maze.startPoint.y)
	{
		curPoint.n = step;
		step--;
	}

	//得到当前点周围能到达的所有点
	vector<Point*> surroundPoints = getSurroundPoints(&curPoint);
	//遍历能够到达的所有点
	for (auto &target : surroundPoints)
	{
		//将能够到达的点的parent指针指向当前点
		target->parent = &curPoint;
		//如果到达终点则返回终点的指针
		if (target->x == endPoint.x && target->y == endPoint.y)
			return target;

		Point *result;
		//递归
		result = findPath(*target, endPoint);
		if (result != NULL)
			return result;
	}
	s.pop();
	return NULL;
}

//用于得到路径
list<Point*> dfs::getPath(Point *result)
{
	keyStep = 11;
	list<Point*> path;
	while (result)
	{
		if ((result->x != maze.startPoint.x || result->y != maze.startPoint.y) && (result->x != maze.endPoint.x || result->y != maze.endPoint.y))
		{
			result->n = keyStep;
			keyStep++;
		}
		path.push_front(result);
		result = result->parent;
	}

	return path;
}

//用于得到当前点周围能够达到的所有点
vector<Point*> dfs::getSurroundPoints(const Point *point) const
{
	vector<Point*> surroundPoints;

	//遍历方向
	int dx[4] = { 0,-1,0,1 };
	int dy[4] = { 1,0,-1,0 };

	for (int i = 0; i<4; i++)
	{
		int x = point->x + dx[i];
		int y = point->y + dy[i];
		if (isCanReach(point, maze.Map[x][y]))
		{
			surroundPoints.push_back(maze.Map[x][y]);
		}
	}

	return surroundPoints;
}

//用于判断当前点能否到达目标点
bool dfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}

//aStar类的构造函数
aStar::aStar() {}
aStar::aStar(Maze &maze) : myAlgorithm(maze) {}
aStar::~aStar() {}

//用于计算A*算法中的g(n)
int aStar::calcG(Point *point)
{
	int thisG = 1;
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return thisG + parentG;
}

//用于计算A*算法中的h(n)
int aStar::calcH(Point *point, Point *endPoint)
{
	//曼哈顿距离
	return abs(point->x - endPoint->x) + abs(point->y - endPoint->y);
	//欧几里得距离
	//return sqrt((point->x - endPoint->x)*(point->x - endPoint->x) + (point->y - endPoint->y)*(point->y - endPoint->y));
}

//用于计算A*算法中的f(n)
int aStar::calcF(Point *point)
{
	return point->G + point->H;
}

//用于得到openlist中f值最小的点
Point* aStar::getLeastFPoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList)
			if (point->F<resPoint->F)
				resPoint = point;
		return resPoint;
	}
	return NULL;
}

//启发式搜索的核心代码，用于寻找路径，传入的是起点和终点的引用
Point* aStar::findPath(Point &startPoint, Point &endPoint)
{
	//将起点加入openList
	openList.push_back(&startPoint);
	while (!openList.empty())
	{
		//得到openList中f值最小的点
		Point* curPoint = getLeastFPoint();
		//将这个点进行标记，并用计数器step表示遍历的是第几个点
		if (curPoint->x != maze.startPoint.x || curPoint->y != maze.startPoint.y)
		{
			curPoint->n = step;
			step--;
		}

		//将这个点移出openList
		openList.remove(curPoint);
		//将这个点加入closeList
		closeList.push_back(curPoint);

		//得到当前点周围能到达的所有点
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		//遍历能到达的所有点
		for (auto &target : surroundPoints)
		{
			//判断该点是否已在openList中
			if (!isInList(openList, target))
			{
				//若不在则将其parent指针指向当前点，并计算g、h、f值，最后将其加入openList
				target->parent = curPoint;
				target->G = calcG(target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			else
			{
				//若在，则比较该点之前的f值和若以当前点为parent的f值的大小，若以当前点为parent的f值小，则修改该点
				int tempG = curPoint->G + 1;
				if (tempG<target->G)
				{
					target->parent = curPoint;
					target->G = tempG;
					target->F = calcF(target);
				}
			}

			//判断openList中是否含有终点，若有则返回终点指针
			Point *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint;
		}
	}
	return NULL;
}

//用于得到最佳路径
list<Point*> aStar::getPath(Point *result)
{
	keyStep = 11;
	list<Point*> path;
	while (result)
	{
		if ((result->x != maze.startPoint.x || result->y != maze.startPoint.y) && (result->x != maze.endPoint.x || result->y != maze.endPoint.y))
		{
			result->n = keyStep;
			keyStep++;
		}	
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

//用于判断某个点是否在某个列表中
Point* aStar::isInList(list<Point*> thisList, const Point *point) const
{
	for (auto p : thisList)
		if (p->x == point->x && p->y == point->y)
			return p;
	return NULL;
}

//用于判断某个点是否能够到达目标点
bool aStar::isCanReach(const Point *point, const Point *target) const
{
	if (target->x<0 || target->x>maze.rows || target->y<0 || target->y>maze.cols || maze.Map[target->x][target->y]->n == 1 || (target->x == point->x && target->y == point->y) || isInList(closeList, target))
		return false;
	else if (abs(point->x - target->x) + abs(point->y - target->y) == 1)
	{
		return true;
	}
	else
		return false;
}

//用于得到某个点周围能够到达的所有点
vector<Point*> aStar::getSurroundPoints(const Point *point) const
{
	vector<Point*> surroundPoints;

	int dx[4] = { 0,-1,0,1 };
	int dy[4] = { 1,0,-1,0 };

	for (int i = 0; i<4; i++)
	{
		int x = point->x + dx[i];
		int y = point->y + dy[i];
		if (isCanReach(point, maze.Map[x][y]))
		{
			surroundPoints.push_back(maze.Map[x][y]);
		}

	}

	return surroundPoints;
}

//IDA*类构造函数
idaStar::idaStar() {}
idaStar::idaStar(Maze &maze) : myAlgorithm(maze) {}
idaStar::~idaStar() {}

//用于计算IDA*算法中的g(n)
int idaStar::calcG(Point *point)
{
	int thisG = 1;
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return thisG + parentG;
}

//用于计算IDA*算法中的h(n)
int idaStar::calcH(Point *point, Point *endPoint)
{
	//曼哈顿距离
	return abs(point->x - endPoint->x) + abs(point->y - endPoint->y);
	//欧几里得距离
	//return sqrt((point->x - endPoint->x)*(point->x - endPoint->x) + (point->y - endPoint->y)*(point->y - endPoint->y));
}

//用于计算IDA*算法中的f(n)
int idaStar::calcF(Point *point)
{
	return point->G + point->H;
}

//迭代加深启发式搜索用于寻找路径的函数，传入的是起点和终点的引用
Point* idaStar::findPath(Point &startPoint, Point &endPoint)
{
	//计算起点到终点的f值，设为初始估价量
	startPoint.G = calcG(&startPoint);
	startPoint.H = calcH(&startPoint, &endPoint);
	startPoint.F = calcF(&startPoint);
	int startStep = startPoint.F;

	Point *result;
	while ((result = idaSerach(&startPoint, endPoint, startStep)) == NULL)
	{
		//判断是否迷宫已全部遍历
		bool noPath = true;
		for (int i = 0; i < maze.rows; i++)
		{
			for (int j = 0; j < maze.cols; j++)
			{
				if (maze.Map[i][j]->n == 0)
					noPath = false;
			}
		}
		if (noPath)
			return NULL;

		//在此估价量下找不到终点，则将估价量++
		startStep++;
		//初始化迷宫
		step = -1;
		for (int i = 0; i < maze.rows; i++)
		{
			for (int j = 0; j < maze.cols; j++)
			{
				maze.Map[i][j]->parent = NULL;
				if (maze.Map[i][j]->n < 0)
					maze.Map[i][j]->n = 0;
			}
		}
	}

	return result;
}

//IDA*算法核心函数
Point* idaStar::idaSerach(Point *point, Point &endPoint, int maxF)
{
	//若该点的F值>预设的最大F值，则返回
	if (point->F > maxF)
		return NULL;	

	//如果到达终点则返回终点的指针
	if (point->x == endPoint.x && point->y == endPoint.y)
		return point;

	//将这个点进行标记，并用计数器step表示遍历的是第几个点
	if (point->x != maze.startPoint.x || point->y != maze.startPoint.y)
	{
		if (point->n == 0)
		{
			point->n = step;
			step--;
		}
	}

	//得到当前点周围能到达的所有点
	vector<Point*> surroundPoints = getSurroundPoints(point);
	//遍历能够到达的所有点
	for (auto &target : surroundPoints)
	{
		//将能够到达的点的parent指针指向当前点
		if (target->parent == NULL)
		{
			target->parent = point;
			target->G = calcG(target);
			target->H = calcH(target, &endPoint);
			target->F = calcF(target);
		}
		else
		{
			int tempG = point->G + 1;
			if (tempG < target->G)
			{
				target->parent = point;
				target->G = tempG;
				target->F = calcF(target);
			}
		}

		Point *result;
		//递归
		result = idaSerach(target, endPoint, maxF);
		if (result != NULL)
			return result;
	}
	return NULL;
}

//用于得到路径
list<Point*> idaStar::getPath(Point *result)
{
	keyStep = 11;
	list<Point*> path;
	while (result)
	{
		if ((result->x != maze.startPoint.x || result->y != maze.startPoint.y) && (result->x != maze.endPoint.x || result->y != maze.endPoint.y))
		{
			result->n = keyStep;
			keyStep++;
		}
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

//用于得到当前点周围能到达的所有点
vector<Point*> idaStar::getSurroundPoints(const Point *point) const
{
	vector<Point*> surroundPoints;

	int dx[4] = { 0,-1,0,1 };
	int dy[4] = { 1,0,-1,0 };

	for (int i = 0; i<4; i++)
	{
		int x = point->x + dx[i];
		int y = point->y + dy[i];
		if (isCanReach(point, maze.Map[x][y]))
		{
			surroundPoints.push_back(maze.Map[x][y]);
		}

	}

	return surroundPoints;
}

//判断该点是否能够到达
bool idaStar::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}

