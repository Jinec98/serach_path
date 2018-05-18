#include "myAlgorithm.h"

bfs::bfs() {};
//bfs��Ĺ��캯��������Maze���͵�����
bfs::bfs(Maze &m)
{
	step = -1;
	keyStep = 11;
	this->m = m;
}

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
		if (curPoint->x != m.startPoint.x || curPoint->y != m.startPoint.y)
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
		if ((result->x != m.startPoint.x || result->y != m.startPoint.y) && (result->x != m.endPoint.x || result->y != m.endPoint.y))
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
		if (isCanReach(point, m.Map[x][y]))
		{
			surroundPoints.push_back(m.Map[x][y]);
		}

	}

	return surroundPoints;
}

//�����ж�ĳ�����ܷ񵽴�Ŀ���
bool bfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= m.rows && target->y >= 1 && target->y <= m.cols)
		return true;
	return false;
}


//�����������������ջ
stack<Point*> s;
dfs::dfs() {};
//dfs��Ĺ��캯��
dfs::dfs(Maze &m)
{
	step = -1;
	keyStep = 11;
	this->m = m;
}

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
	if (curPoint.x != m.startPoint.x || curPoint.y != m.startPoint.y)
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
		if ((result->x != m.startPoint.x || result->y != m.startPoint.y) && (result->x != m.endPoint.x || result->y != m.endPoint.y))
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
		if (isCanReach(point, m.Map[x][y]))
		{
			surroundPoints.push_back(m.Map[x][y]);
		}
	}

	return surroundPoints;
}

//�����жϵ�ǰ���ܷ񵽴�Ŀ���
bool dfs::isCanReach(const Point *point, const Point *target) const
{
	if ((target->n == 0 || target->n == 3) && target->x >= 1 && target->x <= m.rows && target->y >= 1 && target->y <= m.cols)
		return true;
	return false;
}


aStar::aStar() {};
//aStar��Ĺ��캯��
aStar::aStar(Maze &m)
{
	step = -1;
	keyStep = 11;
	this->m = m;
}
aStar::~aStar()
{

}

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
		if (curPoint->x != m.startPoint.x || curPoint->y != m.startPoint.y)
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
		if ((result->x != m.startPoint.x || result->y != m.startPoint.y) && (result->x != m.endPoint.x || result->y != m.endPoint.y))
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
	if (target->x<0 || target->x>m.rows || target->y<0 || target->y>m.cols || m.Map[target->x][target->y]->n == 1 || (target->x == point->x && target->y == point->y) || isInList(closeList, target))
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
		if (isCanReach(point, m.Map[x][y]))
		{
			surroundPoints.push_back(m.Map[x][y]);
		}

	}

	return surroundPoints;
}
