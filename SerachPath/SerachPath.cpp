#include "SerachPath.h"

//�������������ڽ�string����ת����QString����
inline QString s2q(const std::string &s)
{
	return QString(QString::fromLocal8Bit(s.c_str()));
}

//�������������ڽ�QString����ת����string����
inline std::string q2s(const QString &s) 
{
	return std::string((const char *)s.toLocal8Bit());
}

//���캯��
SerachPath::SerachPath(QWidget *parent)
	: QMainWindow(parent)
{
	initWindow();
	createToolBar();
	//ui.setupUi(this);
}
SerachPath::~SerachPath()
{

}

//���ڳ�ʼ������
void SerachPath::initWindow()
{
	//���ô��ڻ�����Ϣ
	icon.addFile(QStringLiteral(":/SerachPath/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);

	setWindowTitle(QObject::tr("SerachPath@Jinec"));
	setWindowIcon(icon);
	setFixedSize(780, 500);
	setWindowOpacity(0.9);

	//���ô��ڲ���
	widget = new QWidget(this);
	setCentralWidget(widget);
	layout = new QGridLayout();
	widget->setLayout(layout);
	layout->setHorizontalSpacing(0);// ����ˮƽ���
	layout->setVerticalSpacing(0);  // ���ô�ֱ���
	layout->setContentsMargins(10, 10, 10, 10);// ��������

	//��ʼ���ز�ͼƬ
	blank = QPixmap(":/SerachPath/Resources/blank.png");
	start = QPixmap(":/SerachPath/Resources/start.png");
	end = QPixmap(":/SerachPath/Resources/end.png");
	wall = QPixmap(":/SerachPath/Resources/wall.png");
	path = QPixmap(":/SerachPath/Resources/path.png");
	keyPath = QPixmap(":/SerachPath/Resources/keyPath.png");

	//�õ����泤��
	desktopWidget = QApplication::desktop();
	QRect clientRect = desktopWidget->availableGeometry();
	maxWidth = clientRect.width();
	maxHeight = clientRect.height();
	initWidth = this->width();

	//��ʼ�����label
	initLabel = new QLabel();
	std::string infoText;
	infoText += "\t\t\t������Ϊ�����·����ȡ��̬��ʾ��������\n\n";
	infoText += "���ڱ�����\n\n";
	infoText += "�����������������DFS�����������������BFS�������������پ��������ʽ������Astar���㷨��\n";
	infoText += "�����Թ�����������㵽�յ��·��������ʾ�����Ĳ��輰���·����\n";
	infoText += "�����ݽṹ���棬����������ջ�����С�����STL��list��vector��stack��queue�������֪ʶ��\n";
	infoText += "��C++���棬�����˶��ļ����������졢��������ء������������ļ������������ָ�������õ����֪ʶ��\n";
	infoText += "��QT���棬�����˴��ڡ����֡��ؼ����źŲۡ��Ի��򡢶��̵߳����֪ʶ��\n\n\n";
	infoText += "�����Թ��Ĵ�С��ģδ֪�����ڽ����СΪ�㷨����ó���������Թ���ģΪ5*5-30*30�³�����ʾ��ѡ�\n";
	infoText += "�����ǵ�һ�����б����򣬽����ȵ�����������˽�������ز�����\n\n";
	infoText += "�����������Ϊ��������ԴĿ¼��/test�к����Թ�������������ֱ�Ӵ򿪿������������Թ�����\n";
	infoText += "\t�����Թ�->���ļ�->������ʾ�ٶ�->���������㷨->Ѱ��·��->�õ����·��->�����ļ�\n\n";
	infoText += "����BUG�����½⣬����������ϵ�r(��_��)�q\n\n";
	infoText += "���ߣ�@Jinec\tQQ��389468296";
	QString infoStr = s2q(infoText);
	initLabel->setText(infoStr);
	QFont font("Microsoft YaHei", 12, 75);
	initLabel->setFont(font);
	layout->addWidget(initLabel, 0,0);
}

//�����Զ����ô��ڴ�С�ĺ���
void SerachPath::setWindow()
{
	//�õ��ز�ͼƬ�ĳ���
	iconWidth = blank.width();
	iconHeight = blank.height();

	//������ĳ���-100��Ϊ���ڵ���󳤿�������Ŀ����Ϊ���ڵ���С���
	int screenMaxWidth = maxWidth - 100;
	int screenMaxHeight = maxHeight - 100;
	int screenMinWidth = initWidth;

	//��ͼƬ�ĳ���*�Թ������ж���֮һ����������ĳ�������еȱ�����С
	if (iconWidth*maze->cols > maxWidth || iconHeight * maze->rows > maxHeight)
	{
		if (iconWidth*maze->cols > maxWidth && iconHeight*maze->rows <= maxHeight)
		{
			int height = (iconHeight * maze->rows) * screenMaxWidth / (iconWidth * maze->cols);
			setFixedSize(screenMaxWidth, height);
		}
		else if (iconWidth*maze->cols <= maxWidth && iconHeight*maze->rows > maxHeight)
		{
			int width = (iconWidth * maze->cols) * screenMaxHeight / (iconHeight * maze->rows);
			setFixedSize(width, screenMaxHeight);
		}
		//������߶������ˣ������ͼƬ�ĳ���Ⱥ���Ļ�ĳ���Ȳ����бȽ�
		else
		{
			double iconRate = (iconWidth*maze->cols) / (iconHeight*maze->rows);
			double screenRate = maxWidth / maxHeight;
			if (iconRate > screenRate)
			{
				int height = (iconHeight * maze->rows) * screenMaxWidth / (iconWidth * maze->cols);
				setFixedSize(screenMaxWidth, height);
			}
			else
			{
				int width = (iconWidth * maze->cols) * screenMaxHeight / (iconHeight * maze->rows);
				setFixedSize(width, screenMaxHeight);
			}
		}
	}
	//��ͼƬ�Ŀ�*�Թ�����С����С�����ȱ����Ŵ�
	else if (iconWidth*maze->cols < initWidth)
	{
		int height = (iconHeight * maze->rows) * screenMinWidth / (iconWidth * maze->cols);
		setFixedSize(screenMinWidth, height);
	}
	//��ͼƬ�ĳ���*�Թ������бȽ��ʺϣ���ֱ���Ը�ֵ��Ϊ���ڴ�С
	else
	{
		setFixedSize(iconWidth*maze->cols, iconHeight * maze->rows);
	}

	//�õ����ú�Ĵ��ڳ���
	widgetHeight = (*widget).height();
	widgetWidth = (*widget).width();
	move((maxWidth - widgetWidth) / 2, (maxHeight - widgetHeight) / 2);

	//���ô�����������ʾͼƬ��label�Ĵ�С������label�е�ͼƬ����Ϊ����Ӧ��С
	for (unsigned int i = 0; i < mapLabel.size(); i++)
	{
		for (unsigned int j = 0; j < mapLabel[i].size(); j++)
		{
			mapLabel[i][j]->resize(widgetWidth / mapLabel[i].size(), widgetHeight / mapLabel.size());
			mapLabel[i][j]->setScaledContents(true);
		}
	}
}

//���ڴ���������
void SerachPath::createToolBar()
{
	//��ʼ�����������źŲ�
	makeMazeAction = new QAction(QIcon(":/SerachPath/Resources/add.png"), s2q("�����Թ�"), this);
	openFileAction = new QAction(QIcon(":/SerachPath/Resources/openFile.png"), s2q("���ļ�"), this);
	findPathAction = new QAction(QIcon(":/SerachPath/Resources/findPath.png"), s2q("Ѱ��·��"), this);
	getPathAction = new QAction(QIcon(":/SerachPath/Resources/getPath.png"), s2q("�õ�·��"), this);
	saveFileAction = new QAction(QIcon(":/SerachPath/Resources/saveFile.png"), s2q("�����ļ�"), this);
	helpAction = new QAction(QIcon(":/SerachPath/Resources/help.png"), s2q("����"), this);
	setSpeedAction = new QAction(QIcon(":/SerachPath/Resources/setSpeed.png"), s2q("��ʾ�ٶ�"), this);

	//���ӹ������İ�ť���źŲ�
	connect(makeMazeAction, &QAction::triggered, this, &SerachPath::makeMazeActionSlot);
	connect(openFileAction, &QAction::triggered, this, &SerachPath::openFileActionSlot);
	connect(findPathAction, &QAction::triggered, this, &SerachPath::findPathActionSlot);
	connect(getPathAction, &QAction::triggered, this, &SerachPath::getPathActionSlot);
	connect(saveFileAction, &QAction::triggered, this, &SerachPath::saveFileActionSlot);
	connect(helpAction, &QAction::triggered, this, &SerachPath::helpActionSlot);

	//��ʼ���������İ�ť
	makeMazeTool = addToolBar("Create Maze");
	makeMazeTool->addAction(makeMazeAction);

	openFileTool = addToolBar("Open File");
	openFileTool->addAction(openFileAction);

	findPathTool = addToolBar("Find Path");
	findPathTool->addAction(findPathAction);

	getPathTool = addToolBar("Get Path");
	getPathTool->addAction(getPathAction);

	saveFileTool = addToolBar("Save File");
	saveFileTool->addAction(saveFileAction);

	helpTool = addToolBar("Help");
	helpTool->addAction(helpAction);

	//��ʼ������
	setSpeedTool = addToolBar("Set Speed");
	setSpeedTool->addAction(setSpeedAction);
	setSpeed = new QSlider(Qt::Horizontal);
	setSpeed->setRange(-500, 0);
	setSpeed->setValue(-200);
	setSliderQss(setSpeed, "#FFFFFF", "#000000", "#000000");
	setSpeedTool->addWidget(setSpeed);
	
	//��ʼ�������㷨��ѡ�񹤾�
	setModeTool = addToolBar("Set Mode");
	setMode = new QComboBox();
	QString dfs = s2q("�������������DFS��");
	QString bfs = s2q("�������������BFS��");
	QString astar = s2q("����ʽ������A*��");
	setMode->addItem(QIcon(":/SerachPath/Resources/setMode.png"), dfs);
	setMode->addItem(QIcon(":/SerachPath/Resources/setMode.png"), bfs);
	setMode->addItem(QIcon(":/SerachPath/Resources/setMode.png"), astar);
	setModeTool->addWidget(setMode);
}

void SerachPath::makeMazeActionSlot()
{
	setMazeWindow *setMaze = new setMazeWindow(this);
	setMaze->show();
}

//���ļ��źŲ�
void SerachPath::openFileActionSlot()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle("Open File");
	fileDialog->setNameFilter("Text File(*.txt)");
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	fileDialog->setViewMode(QFileDialog::Detail);

	//�ж��ļ��Ƿ�������
	if (fileDialog->exec())
	{
		fileFullPath = fileDialog->selectedFiles()[0];
		QFileInfo fileInfo = QFileInfo(fileFullPath);
		fileAbsPath = fileInfo.absolutePath();
		fileName = q2s(fileInfo.fileName());
	}
	else
		return;

	//�õ��ļ���·�������ļ���
	std::string filePath = q2s(fileFullPath);
	fileOpen = new openFile(filePath);
	maze = new Maze(fileOpen->getMaze());

	//�����ļ��õ����Թ���ʾ����
	deleteMap();
	setMap();
	setWindow();
	showMap(*maze);
}

//Ѱ��·���źŲ�
void SerachPath::findPathActionSlot()
{
	//�ж��Ƿ���ļ�
	if (maze == NULL)
	{
		QString infoStr = s2q("����ѡ��Ҫ�򿪵��ļ�");
		QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
		return;
	}

	//�ж����õ��������㷨
	if (setMode->currentIndex() == 0)
	{
		dfsMaze = Maze(*maze);
		Dfs = dfs(dfsMaze);
		dfsResult = Dfs.findPath(dfsMaze.startPoint, dfsMaze.endPoint);
		showMap(*maze);
		printPath(dfsMaze,Dfs.step);

		if (dfsResult == NULL)
		{
			QString infoStr = s2q("Ѱ�Ҳ���ͨ���յ��·��");
			QMessageBox::warning(this, s2q("ʧ��"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "ͨ��������������㷨��һ���ķ��ˣ�" + to_string(-Dfs.step) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 1)
	{
		bfsMaze = Maze(*maze);
		Bfs = bfs(bfsMaze);
		bfsResult = Bfs.findPath(bfsMaze.startPoint, bfsMaze.endPoint);
		showMap(*maze);
		printPath(bfsMaze,Bfs.step);

		if (bfsResult == NULL)
		{
			QString infoStr = s2q("Ѱ�Ҳ���ͨ���յ��·��");
			QMessageBox::warning(this, s2q("ʧ��"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "ͨ��������������㷨��һ���ķ��ˣ�" + to_string(-Bfs.step) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 2)
	{
		astarMaze = Maze(*maze);
		Astar = aStar(astarMaze);
		astarResult = Astar.findPath(astarMaze.startPoint, astarMaze.endPoint);
		showMap(*maze);
		printPath(astarMaze,Astar.step);

		if (astarResult == NULL)
		{
			QString infoStr = s2q("Ѱ�Ҳ���ͨ���յ��·��");
			QMessageBox::warning(this, s2q("ʧ��"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "ͨ������ʽ�����㷨��һ���ķ��ˣ�" + to_string(-Astar.step) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}

}

//�õ�·���źŲ�
void SerachPath::getPathActionSlot()
{
	if (setMode->currentIndex() == 0)
	{
		//�жϸ����㷨�Ƿ��Ѿ�ִ�й�Ѱ��·��
		if (dfsResult == NULL)
		{
			QString infoStr = s2q("���ȿ�ʼѰ��·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		dfsPath = Dfs.getPath(dfsResult);
		showMap(dfsMaze);
		printKeyPath(dfsMaze, Dfs.keyStep);

		std::string stepInfo = "������������㷨�õ��Ĳ�һ�������·��\nͨ��������������㷨�õ���·����Ҫ��" + to_string(Dfs.keyStep-10) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 1)
	{
		if (bfsResult == NULL)
		{
			QString infoStr = s2q("���ȿ�ʼѰ��·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		bfsPath = Bfs.getPath(bfsResult);
		showMap(bfsMaze);
		printKeyPath(bfsMaze, Bfs.keyStep);

		std::string stepInfo = "ͨ��������������㷨�õ������·����Ҫ��" + to_string(Bfs.keyStep-10) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 2)
	{
		if (astarResult == NULL)
		{
			QString infoStr = s2q("���ȿ�ʼѰ��·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		astarPath = Astar.getPath(astarResult);
		showMap(astarMaze);
		printKeyPath(astarMaze, Astar.keyStep);

		std::string stepInfo = "ͨ������ʽ�����㷨�õ������·����Ҫ��" + to_string(Astar.keyStep-10) + "��";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("���"), infoStr, QMessageBox::Ok);
	}
}

//�����ļ��źŲ�
void SerachPath::saveFileActionSlot()
{
	//�õ������·��
	std::string filePath = q2s(fileAbsPath);
	if (setMode->currentIndex() == 0)
	{
		//�жϸ����㷨�Ƿ��Ѿ�ִ�й��õ�·��
		if (dfsPath.empty())
		{
			QString infoStr = s2q("���ȵõ����·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		filePath += "/dfsPath_" + fileName;
		fileWrite = new writeFile(filePath, &dfsMaze);
		fileWrite->writeMaze(dfsPath, to_string(Dfs.keyStep - 10));
	}
	else if (setMode->currentIndex() == 1)
	{
		if (bfsPath.empty())
		{
			QString infoStr = s2q("���ȵõ����·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		filePath += "/bfsPath_" + fileName;
		fileWrite = new writeFile(filePath, &bfsMaze);
		fileWrite->writeMaze(bfsPath, to_string(Bfs.keyStep - 10));
	}
	else if (setMode->currentIndex() == 2)
	{
		if (astarPath.empty())
		{
			QString infoStr = s2q("���ȵõ����·��");
			QMessageBox::critical(this, s2q("����"), infoStr, QMessageBox::Ok);
			return;
		}
		filePath += "/astarPath_" + fileName;
		fileWrite = new writeFile(filePath, &astarMaze);
		fileWrite->writeMaze(astarPath, to_string(Astar.keyStep - 10));
	}
	
	QString infoStr = s2q("�ļ�����ɹ�\n�ļ������ڴ򿪵��ļ���Ŀ¼��");
	QMessageBox::information(this, s2q("�ɹ�"), infoStr, QMessageBox::Ok);
}

//�����ĵ��źŲ�
void SerachPath::helpActionSlot()
{
	std::string infoText;
	infoText = "����������DFS��BFS��Astar�㷨�����Թ�����������㵽�յ��·�����ܹ���ʾ�����Ĳ����Լ����·����\n\n\n";
	infoText += "��������֪��\n\n";
	infoText += "1������������Թ���\t�����Թ��������\n\n";
	infoText += "\t������������Թ������м����ƣ��ڸý�����ͨ����괴���Թ�������ѡ��Ŀ¼�����ļ�\n";
	infoText += "\t������ļ�Ϊ�������ʶ���txt�ı��������ں��������ļ���ʹ��\n\n";
	infoText += "2����������ļ���\t�򿪡�.txt���ı��ļ�\n\n";
	infoText += "\t���ļ����ݵĸ�ʽΪ��\n\t��һ�У���������m��n���ֱ��ʾ�Թ���������\n";
	infoText += "\t����m�У�ÿ��n���ַ�����ʾ�Թ�������Ϊ��m��n���ĵط���״̬\n\t���У��� ����һ���ո񣩱�ʾ����·������X������дӢ����ĸX����ʾǽ���������ߣ�����S����ʾ��㡢��D����ʾ�յ�\n\n";
	infoText += "\tע�⣺�Թ������ʹ�ģΪ5*5-30*30���ڴ�����³�����ʾ����Ϊ����\n\n";
	infoText += "3�����á������㷨��\t���������һ��\n\n";
	infoText += "\t���������㷨�ɹ�ѡ��\n\t�������������DFS�����������������BFS��������ʽ������Astar��\n\n";
	infoText += "4�������Ѱ��·����\t���ȴ��ļ�\n\n";
	infoText += "\t��ͨ�����úõ��㷨���Թ�����Ѱ�Ҵ���㵽�յ��·��\n";
	infoText += "\t̽Ѱ�ķ���Ϊ�ҡ����ϡ���������¡�\n\t���޿���·����ᵯ����Ϣ��ʾ\n\n";
	infoText += "5��������õ�·����\t����Ѱ��·��\n\n";
	infoText += "\t����ʾͨ��֮ǰ��Ѱ�Ҷ��õ������·��\n\n";
	infoText += "6������������ļ���\t���ȵõ�·��\n\n";
	infoText += "\t�ɽ���������н���������ı��ļ���\n\t���ļ�������֮ǰ�򿪵��ļ���Ŀ¼��\n\t����Ϊ���㷨����_�򿪵��ļ����ơ�\n\n";
	infoText += "\t���ļ������ݵĸ�ʽΪ��\n\tǰm�У�ÿ��n���ַ���ʾ�Թ������С�*����ʾ����㵽�յ�����·��\n\t��ʾ��·���Ĳ���step\n\t����step�У���ʾ����㵽�յ��·��������\n\n";
	infoText += "7����������ʾ�ٶȡ�����\t�ٶȷ�Χ��0-500ms��\n\n";
	infoText += "\t�ɵ���ÿһ������ʾ���ٶ�\n\t����Թ���ģ�ϴ󣬽��齫�ٶȳ�ʼֵ�ȵ���\n\n";
	QString infoStr = s2q(infoText);
	QMessageBox::question(this, s2q("����"), infoStr, QMessageBox::Ok);

}

//���ڳ�ʼ���Թ���laebl�������������������
void SerachPath::setMap()
{
	mapLabel.resize(maze->rows);
	for (unsigned int i = 0; i < mapLabel.size(); i++)
		mapLabel[i].resize(maze->cols);

	for (int i = 0; i < maze->rows; i++)
	{
		for (int j = 0; j < maze->cols; j++)
		{
			mapLabel[i][j] = new QLabel();
			layout->addWidget(mapLabel[i][j], i, j, 1, 1);
		}
	}
}

//������մ����ϵ�label��������Թ�label���ڴ�
void SerachPath::deleteMap()
{
	QLayoutItem *item;
	while ((item = layout->takeAt(0)) != 0) {
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}

	for (unsigned int i = 0; i < mapLabel.size(); i++)
	{
		mapLabel[i].clear();
	}
	mapLabel.clear();
}

//������ʾ������ÿһ����
void SerachPath::printPath(Maze maze,int step)
{
	int cnt = -1;
	while (cnt > step) 
	{
		for (int i = 0; i < maze.rows; i++)
		{
			for (int j = 0; j < maze.cols; j++)
			{
				if (maze.Map[i][j]->n == cnt)
				{
					mapLabel[i][j]->setPixmap(path);
					cnt--;
					repaint();
					//���ڵ�����ʾ�ٶ�
					QThread::msleep(-setSpeed->value());
				}
			}
		}
		
	}

}

//������ʾ���·��
void SerachPath::printKeyPath(Maze maze,int step)
{
	step--;
	int cnt = step;
	while (cnt > 10)
	{
		for (int i = 0; i < maze.rows; i++)
		{
			for (int j = 0; j < maze.cols; j++)
			{
				if (maze.Map[i][j]->n == cnt)
				{
					mapLabel[i][j]->setPixmap(keyPath);
					cnt--;
					repaint();
					//���ڵ�����ʾ�ٶ�
					QThread::msleep(-setSpeed->value());
				}
			}
		}
	}
}

//������ʾ�Թ���ͨ���ж��Թ�ÿ�������Ϣ���ֱ���ʾ��ͬ���ز�
void SerachPath::showMap(Maze maze)
{
	for (int i = 0; i < maze.rows; i++)
	{
		for (int j = 0; j < maze.cols; j++)
		{
			if (maze.Map[i][j]->n == 0)
				mapLabel[i][j]->setPixmap(blank);
			else if (maze.Map[i][j]->n == 1)
				mapLabel[i][j]->setPixmap(wall);
			else if (maze.Map[i][j]->n == 2)
				mapLabel[i][j]->setPixmap(start);
			else if (maze.Map[i][j]->n == 3)
				mapLabel[i][j]->setPixmap(end);
			else if (maze.Map[i][j]->n < 0 || maze.Map[i][j]->n > 10)
				mapLabel[i][j]->setPixmap(path);
		}
	}
}

//���������������Դ�����粩��
void SerachPath::setSliderQss(QSlider *slider, QString normalColor, QString grooveColor, QString handleColor)
{
	int sliderHeight = 8;
	int sliderRadius = 4;
	int handleWidth = 13;
	int handleRadius = 6;
	int handleOffset = 3;

	QStringList qss;
	qss.append(QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(normalColor).arg(sliderHeight).arg(sliderRadius));
	qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
	qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;margin-bottom:-%3px;border-radius:%4px;"
		"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
		.arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

	slider->setStyleSheet(qss.join(""));
}
