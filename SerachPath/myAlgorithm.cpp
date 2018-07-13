#include "myAlgorithm.h"

myAlgorithm::myAlgorithm() {}

//���๹�캯��
myAlgorithm::myAlgorithm(Maze &maze)
{
	step = -1;
	keyStep = 11;
	this->maze = maze;
}

myAlgorithm::~myAlgorithm() {}


//bfs��Ĺ��캯��������Maze���͵�����
bfs::bfs() {}
bfs::bfs(Maze &maze) : myAlgorithm(maze) {}
bfs::~bfs() {}

//������������ĺ��Ĵ��룬��������·�������������յ������
Point* bfs::findPath(Point &startPoint, Point &endPoint)
{
	//����������������˶���
	queue<Point*> q;
	q.push(&startPoint);

	while (!q.empty())
	{
		//�õ����׵ĵ㲢�������
		Point* curPoint = q.front();
		//������֮ǰ�Ѿ��������ĵ���������ǰѭ��
		if (curPoint->n < 0)
		{
			q.pop();
			continue;
		}
		//���������б�ǣ����ü�����step��ʾ�������ǵڼ�����
		if (curPoint->x != maze.startPoint.x || curPoint->y != maze.startPoint.y)
		{
			curPoint->n = step;
			step--;
		}
		q.pop();

		//�õ���ǰ����Χ�ܹ�����ĵ�
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		//�����ܹ���������е�
		for (auto &target : surroundPoints)
		{
			//���ܹ�����ĵ��parentָ��ָ��ǰ��
			target->parent = curPoint;
			//����ҵ��յ㣬�򷵻��Ǹ������ָ��
			if (target->x == endPoint.x && target->y == endPoint.y)
				return target;
			//���ܹ�����ĵ����
			q.push(target);
		}
	}
	return NULL;
}

//���ڵõ����·��������Ĳ���Ϊ�ҵ����յ��ָ��
list<Point*> bfs::getPath(Point *result)
{
	//��ʾ���·��������0,1����ռ�ùʴ�11��ʼ����󽫽��-10����
	keyStep = 11;
	//���ڴ洢·�����б�
	list<Point*> path;
	while (result)
	{
		//���������������˼����յ㿪ʼ����parentָ��
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

//���ڵõ�ĳ������Χ�ܹ���������е�
vector<Point*> bfs::getSurroundPoints(const Point *point) const
{
	//���ڴ洢�ܹ���������е�
	vector<Point*> surroundPoints;

	//��������
	int dx[4] = { 0,-1,0,1 };
	int dy[4] = { 1,0,-1,0 };

	for (int i = 0; i<4; i++)
	{
		int x = point->x + dx[i];
		int y = point->y + dy[i];
		//�жϸõ��ܷ񵽴���������vector
		if (isCanReach(point, maze.Map[x][y]))
		{
			surroundPoints.push_back(maze.Map[x][y]);
		}

	}

	return surroundPoints;
}

//�����ж�ĳ�����ܷ񵽴�Ŀ���
bool bfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}


//�����������������ջ
stack<Point*> s;
//dfs��Ĺ��캯��
dfs::dfs() {}
dfs::dfs(Maze &maze) : myAlgorithm(maze) {}
dfs::~dfs() {}

//������������㷨�ĺ��Ĵ��룬����Ѱ��·����������ǵ�ǰ����յ������
Point* dfs::findPath(Point &curPoint, Point &endPoint)
{
	s.push(&curPoint);
	//���õ��Ѿ��Ѿ���������ֱ��return
	if (curPoint.n < 0)
	{
		s.pop();
		return NULL;
	}
	//���������б�ǣ����ü�����step��ʾ�������ǵڼ�����
	if (curPoint.x != maze.startPoint.x || curPoint.y != maze.startPoint.y)
	{
		curPoint.n = step;
		step--;
	}

	//�õ���ǰ����Χ�ܵ�������е�
	vector<Point*> surroundPoints = getSurroundPoints(&curPoint);
	//�����ܹ���������е�
	for (auto &target : surroundPoints)
	{
		//���ܹ�����ĵ��parentָ��ָ��ǰ��
		target->parent = &curPoint;
		//��������յ��򷵻��յ��ָ��
		if (target->x == endPoint.x && target->y == endPoint.y)
			return target;

		Point *result;
		//�ݹ�
		result = findPath(*target, endPoint);
		if (result != NULL)
			return result;
	}
	s.pop();
	return NULL;
}

//���ڵõ�·��
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

//���ڵõ���ǰ����Χ�ܹ��ﵽ�����е�
vector<Point*> dfs::getSurroundPoints(const Point *point) const
{
	vector<Point*> surroundPoints;

	//��������
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

//�����жϵ�ǰ���ܷ񵽴�Ŀ���
bool dfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}

//aStar��Ĺ��캯��
aStar::aStar() {}
aStar::aStar(Maze &maze) : myAlgorithm(maze) {}
aStar::~aStar() {}

//���ڼ���A*�㷨�е�g(n)
int aStar::calcG(Point *point)
{
	int thisG = 1;
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return thisG + parentG;
}

//���ڼ���A*�㷨�е�h(n)
int aStar::calcH(Point *point, Point *endPoint)
{
	//�����پ���
	return abs(point->x - endPoint->x) + abs(point->y - endPoint->y);
	//ŷ����þ���
	//return sqrt((point->x - endPoint->x)*(point->x - endPoint->x) + (point->y - endPoint->y)*(point->y - endPoint->y));
}

//���ڼ���A*�㷨�е�f(n)
int aStar::calcF(Point *point)
{
	return point->G + point->H;
}

//���ڵõ�openlist��fֵ��С�ĵ�
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

//����ʽ�����ĺ��Ĵ��룬����Ѱ��·����������������յ������
Point* aStar::findPath(Point &startPoint, Point &endPoint)
{
	//��������openList
	openList.push_back(&startPoint);
	while (!openList.empty())
	{
		//�õ�openList��fֵ��С�ĵ�
		Point* curPoint = getLeastFPoint();
		//���������б�ǣ����ü�����step��ʾ�������ǵڼ�����
		if (curPoint->x != maze.startPoint.x || curPoint->y != maze.startPoint.y)
		{
			curPoint->n = step;
			step--;
		}

		//��������Ƴ�openList
		openList.remove(curPoint);
		//����������closeList
		closeList.push_back(curPoint);

		//�õ���ǰ����Χ�ܵ�������е�
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		//�����ܵ�������е�
		for (auto &target : surroundPoints)
		{
			//�жϸõ��Ƿ�����openList��
			if (!isInList(openList, target))
			{
				//����������parentָ��ָ��ǰ�㣬������g��h��fֵ����������openList
				target->parent = curPoint;
				target->G = calcG(target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			else
			{
				//���ڣ���Ƚϸõ�֮ǰ��fֵ�����Ե�ǰ��Ϊparent��fֵ�Ĵ�С�����Ե�ǰ��Ϊparent��fֵС�����޸ĸõ�
				int tempG = curPoint->G + 1;
				if (tempG<target->G)
				{
					target->parent = curPoint;
					target->G = tempG;
					target->F = calcF(target);
				}
			}

			//�ж�openList���Ƿ����յ㣬�����򷵻��յ�ָ��
			Point *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint;
		}
	}
	return NULL;
}

//���ڵõ����·��
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

//�����ж�ĳ�����Ƿ���ĳ���б���
Point* aStar::isInList(list<Point*> thisList, const Point *point) const
{
	for (auto p : thisList)
		if (p->x == point->x && p->y == point->y)
			return p;
	return NULL;
}

//�����ж�ĳ�����Ƿ��ܹ�����Ŀ���
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

//���ڵõ�ĳ������Χ�ܹ���������е�
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

//IDA*�๹�캯��
idaStar::idaStar() {}
idaStar::idaStar(Maze &maze) : myAlgorithm(maze) {}
idaStar::~idaStar() {}

//���ڼ���IDA*�㷨�е�g(n)
int idaStar::calcG(Point *point)
{
	int thisG = 1;
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return thisG + parentG;
}

//���ڼ���IDA*�㷨�е�h(n)
int idaStar::calcH(Point *point, Point *endPoint)
{
	//�����پ���
	return abs(point->x - endPoint->x) + abs(point->y - endPoint->y);
	//ŷ����þ���
	//return sqrt((point->x - endPoint->x)*(point->x - endPoint->x) + (point->y - endPoint->y)*(point->y - endPoint->y));
}

//���ڼ���IDA*�㷨�е�f(n)
int idaStar::calcF(Point *point)
{
	return point->G + point->H;
}

//������������ʽ��������Ѱ��·���ĺ�����������������յ������
Point* idaStar::findPath(Point &startPoint, Point &endPoint)
{
	//������㵽�յ��fֵ����Ϊ��ʼ������
	startPoint.G = calcG(&startPoint);
	startPoint.H = calcH(&startPoint, &endPoint);
	startPoint.F = calcF(&startPoint);
	int startStep = startPoint.F;

	Point *result;
	while ((result = idaSerach(&startPoint, endPoint, startStep)) == NULL)
	{
		//�ж��Ƿ��Թ���ȫ������
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

		//�ڴ˹��������Ҳ����յ㣬�򽫹�����++
		startStep++;
		//��ʼ���Թ�
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

//IDA*�㷨���ĺ���
Point* idaStar::idaSerach(Point *point, Point &endPoint, int maxF)
{
	//���õ��Fֵ>Ԥ������Fֵ���򷵻�
	if (point->F > maxF)
		return NULL;	

	//��������յ��򷵻��յ��ָ��
	if (point->x == endPoint.x && point->y == endPoint.y)
		return point;

	//���������б�ǣ����ü�����step��ʾ�������ǵڼ�����
	if (point->x != maze.startPoint.x || point->y != maze.startPoint.y)
	{
		if (point->n == 0)
		{
			point->n = step;
			step--;
		}
	}

	//�õ���ǰ����Χ�ܵ�������е�
	vector<Point*> surroundPoints = getSurroundPoints(point);
	//�����ܹ���������е�
	for (auto &target : surroundPoints)
	{
		//���ܹ�����ĵ��parentָ��ָ��ǰ��
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
		//�ݹ�
		result = idaSerach(target, endPoint, maxF);
		if (result != NULL)
			return result;
	}
	return NULL;
}

//���ڵõ�·��
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

//���ڵõ���ǰ����Χ�ܵ�������е�
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

//�жϸõ��Ƿ��ܹ�����
bool idaStar::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= maze.rows && target->y >= 1 && target->y <= maze.cols)
		return true;
	return false;
}

