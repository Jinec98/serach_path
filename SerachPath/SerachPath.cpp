#include "SerachPath.h"

//内联函数，用于将string类型转换成QString类型
inline QString s2q(const std::string &s)
{
	return QString(QString::fromLocal8Bit(s.c_str()));
}

//内联函数，用于将QString类型转换成string类型
inline std::string q2s(const QString &s) 
{
	return std::string((const char *)s.toLocal8Bit());
}

//构造函数
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

//用于初始化窗口
void SerachPath::initWindow()
{
	//设置窗口基本信息
	icon.addFile(QStringLiteral(":/SerachPath/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);

	setWindowTitle(QObject::tr("SerachPath@Jinec"));
	setWindowIcon(icon);
	setFixedSize(780, 500);
	setWindowOpacity(0.9);

	//设置窗口布局
	widget = new QWidget(this);
	setCentralWidget(widget);
	layout = new QGridLayout();
	widget->setLayout(layout);
	layout->setHorizontalSpacing(0);// 设置水平间距
	layout->setVerticalSpacing(0);  // 设置垂直间距
	layout->setContentsMargins(10, 10, 10, 10);// 设置外间距

	//初始化素材图片
	blank = QPixmap(":/SerachPath/Resources/blank.png");
	start = QPixmap(":/SerachPath/Resources/start.png");
	end = QPixmap(":/SerachPath/Resources/end.png");
	wall = QPixmap(":/SerachPath/Resources/wall.png");
	path = QPixmap(":/SerachPath/Resources/path.png");
	keyPath = QPixmap(":/SerachPath/Resources/keyPath.png");

	//得到桌面长宽
	desktopWidget = QApplication::desktop();
	QRect clientRect = desktopWidget->availableGeometry();
	maxWidth = clientRect.width();
	maxHeight = clientRect.height();
	initWidth = this->width();

	//初始界面的label
	initLabel = new QLabel();
	std::string infoText;
	infoText += "\t\t\t本程序为“最短路径求取动态演示”所开发\n\n";
	infoText += "对于本程序：\n\n";
	infoText += "运用深度优先搜索（DFS）、广度优先搜索（BFS）、基于曼哈顿距离的启发式搜索（Astar）算法，\n";
	infoText += "可在迷宫中搜索从起点到终点的路径，并显示搜索的步骤及最佳路径。\n";
	infoText += "在数据结构方面，运用了链表、栈、队列、树、STL（list、vector、stack、queue）等相关知识；\n";
	infoText += "在C++方面，运用了多文件、拷贝构造、运算符重载、内联函数、文件输入输出流、指针与引用等相关知识；\n";
	infoText += "在QT方面，运用了窗口、布局、控件、信号槽、对话框、多线程等相关知识。\n\n\n";
	infoText += "由于迷宫的大小规模未知，窗口界面大小为算法计算得出，因此在迷宫规模为5*5-30*30下程序显示最佳。\n";
	infoText += "如若是第一次运行本程序，建议先点击“帮助”了解程序的相关操作。\n\n";
	infoText += "程序基本流程为：（程序源目录下/test中含有迷宫测试样例，若直接打开可跳过“创建迷宫”）\n";
	infoText += "\t创建迷宫->打开文件->设置显示速度->设置搜索算法->寻找路径->得到最短路径->保存文件\n\n";
	infoText += "如遇BUG敬请谅解，并可与我联系╮(﹀_﹀)╭\n\n";
	infoText += "作者：@Jinec\tQQ：389468296";
	QString infoStr = s2q(infoText);
	initLabel->setText(infoStr);
	QFont font("Microsoft YaHei", 12, 75);
	initLabel->setFont(font);
	layout->addWidget(initLabel, 0,0);
}

//用于自动设置窗口大小的函数
void SerachPath::setWindow()
{
	//得到素材图片的长宽
	iconWidth = blank.width();
	iconHeight = blank.height();

	//将桌面的长宽-100设为窗口的最大长宽，将最初的宽度设为窗口的最小宽度
	int screenMaxWidth = maxWidth - 100;
	int screenMaxHeight = maxHeight - 100;
	int screenMinWidth = initWidth;

	//若图片的长宽*迷宫的行列二者之一超过了桌面的长宽，则进行等比例缩小
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
		//如果二者都超过了，则计算图片的长宽比和屏幕的长宽比并进行比较
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
	//若图片的宽*迷宫的列小于最小宽度则等比例放大
	else if (iconWidth*maze->cols < initWidth)
	{
		int height = (iconHeight * maze->rows) * screenMinWidth / (iconWidth * maze->cols);
		setFixedSize(screenMinWidth, height);
	}
	//若图片的长宽*迷宫的行列比较适合，则直接以该值设为窗口大小
	else
	{
		setFixedSize(iconWidth*maze->cols, iconHeight * maze->rows);
	}

	//得到设置后的窗口长宽
	widgetHeight = (*widget).height();
	widgetWidth = (*widget).width();
	move((maxWidth - widgetWidth) / 2, (maxHeight - widgetHeight) / 2);

	//设置窗口中用于显示图片的label的大小，并将label中的图片设置为自适应大小
	for (unsigned int i = 0; i < mapLabel.size(); i++)
	{
		for (unsigned int j = 0; j < mapLabel[i].size(); j++)
		{
			mapLabel[i][j]->resize(widgetWidth / mapLabel[i].size(), widgetHeight / mapLabel.size());
			mapLabel[i][j]->setScaledContents(true);
		}
	}
}

//用于创建工具栏
void SerachPath::createToolBar()
{
	//初始化工具栏的信号槽
	makeMazeAction = new QAction(QIcon(":/SerachPath/Resources/add.png"), s2q("创建迷宫"), this);
	openFileAction = new QAction(QIcon(":/SerachPath/Resources/openFile.png"), s2q("打开文件"), this);
	findPathAction = new QAction(QIcon(":/SerachPath/Resources/findPath.png"), s2q("寻找路径"), this);
	getPathAction = new QAction(QIcon(":/SerachPath/Resources/getPath.png"), s2q("得到路径"), this);
	saveFileAction = new QAction(QIcon(":/SerachPath/Resources/saveFile.png"), s2q("保存文件"), this);
	helpAction = new QAction(QIcon(":/SerachPath/Resources/help.png"), s2q("帮助"), this);
	setSpeedAction = new QAction(QIcon(":/SerachPath/Resources/setSpeed.png"), s2q("显示速度"), this);

	//连接工具栏的按钮和信号槽
	connect(makeMazeAction, &QAction::triggered, this, &SerachPath::makeMazeActionSlot);
	connect(openFileAction, &QAction::triggered, this, &SerachPath::openFileActionSlot);
	connect(findPathAction, &QAction::triggered, this, &SerachPath::findPathActionSlot);
	connect(getPathAction, &QAction::triggered, this, &SerachPath::getPathActionSlot);
	connect(saveFileAction, &QAction::triggered, this, &SerachPath::saveFileActionSlot);
	connect(helpAction, &QAction::triggered, this, &SerachPath::helpActionSlot);

	//初始化工具栏的按钮
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

	//初始化滑块
	setSpeedTool = addToolBar("Set Speed");
	setSpeedTool->addAction(setSpeedAction);
	setSpeed = new QSlider(Qt::Horizontal);
	setSpeed->setRange(-500, 0);
	setSpeed->setValue(-200);
	setSliderQss(setSpeed, "#FFFFFF", "#000000", "#000000");
	setSpeedTool->addWidget(setSpeed);
	
	//初始化设置算法的选择工具
	setModeTool = addToolBar("Set Mode");
	setMode = new QComboBox();
	QString dfs = s2q("深度优先搜索（DFS）");
	QString bfs = s2q("广度优先搜索（BFS）");
	QString astar = s2q("启发式搜索（A*）");
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

//打开文件信号槽
void SerachPath::openFileActionSlot()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle("Open File");
	fileDialog->setNameFilter("Text File(*.txt)");
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	fileDialog->setViewMode(QFileDialog::Detail);

	//判断文件是否正常打开
	if (fileDialog->exec())
	{
		fileFullPath = fileDialog->selectedFiles()[0];
		QFileInfo fileInfo = QFileInfo(fileFullPath);
		fileAbsPath = fileInfo.absolutePath();
		fileName = q2s(fileInfo.fileName());
	}
	else
		return;

	//得到文件的路径及其文件名
	std::string filePath = q2s(fileFullPath);
	fileOpen = new openFile(filePath);
	maze = new Maze(fileOpen->getMaze());

	//将打开文件得到的迷宫显示出来
	deleteMap();
	setMap();
	setWindow();
	showMap(*maze);
}

//寻找路径信号槽
void SerachPath::findPathActionSlot()
{
	//判断是否打开文件
	if (maze == NULL)
	{
		QString infoStr = s2q("请先选择要打开的文件");
		QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
		return;
	}

	//判断设置的是哪种算法
	if (setMode->currentIndex() == 0)
	{
		dfsMaze = Maze(*maze);
		Dfs = dfs(dfsMaze);
		dfsResult = Dfs.findPath(dfsMaze.startPoint, dfsMaze.endPoint);
		showMap(*maze);
		printPath(dfsMaze,Dfs.step);

		if (dfsResult == NULL)
		{
			QString infoStr = s2q("寻找不到通往终点的路径");
			QMessageBox::warning(this, s2q("失败"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "通过深度优先搜索算法，一共耗费了：" + to_string(-Dfs.step) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
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
			QString infoStr = s2q("寻找不到通往终点的路径");
			QMessageBox::warning(this, s2q("失败"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "通过广度优先搜索算法，一共耗费了：" + to_string(-Bfs.step) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
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
			QString infoStr = s2q("寻找不到通往终点的路径");
			QMessageBox::warning(this, s2q("失败"), infoStr, QMessageBox::Ok);
			return;
		}

		std::string stepInfo = "通过启发式搜索算法，一共耗费了：" + to_string(-Astar.step) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
	}

}

//得到路径信号槽
void SerachPath::getPathActionSlot()
{
	if (setMode->currentIndex() == 0)
	{
		//判断该种算法是否已经执行过寻找路径
		if (dfsResult == NULL)
		{
			QString infoStr = s2q("请先开始寻找路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
			return;
		}
		dfsPath = Dfs.getPath(dfsResult);
		showMap(dfsMaze);
		printKeyPath(dfsMaze, Dfs.keyStep);

		std::string stepInfo = "深度优先搜索算法得到的不一定是最佳路径\n通过深度优先搜索算法得到的路径需要：" + to_string(Dfs.keyStep-10) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 1)
	{
		if (bfsResult == NULL)
		{
			QString infoStr = s2q("请先开始寻找路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
			return;
		}
		bfsPath = Bfs.getPath(bfsResult);
		showMap(bfsMaze);
		printKeyPath(bfsMaze, Bfs.keyStep);

		std::string stepInfo = "通过广度优先搜索算法得到的最佳路径需要：" + to_string(Bfs.keyStep-10) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
	}
	else if (setMode->currentIndex() == 2)
	{
		if (astarResult == NULL)
		{
			QString infoStr = s2q("请先开始寻找路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
			return;
		}
		astarPath = Astar.getPath(astarResult);
		showMap(astarMaze);
		printKeyPath(astarMaze, Astar.keyStep);

		std::string stepInfo = "通过启发式搜索算法得到的最佳路径需要：" + to_string(Astar.keyStep-10) + "步";
		QString infoStr = s2q(stepInfo);
		QMessageBox::information(this, s2q("完成"), infoStr, QMessageBox::Ok);
	}
}

//保存文件信号槽
void SerachPath::saveFileActionSlot()
{
	//得到保存的路径
	std::string filePath = q2s(fileAbsPath);
	if (setMode->currentIndex() == 0)
	{
		//判断该种算法是否已经执行过得到路径
		if (dfsPath.empty())
		{
			QString infoStr = s2q("请先得到最佳路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
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
			QString infoStr = s2q("请先得到最佳路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
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
			QString infoStr = s2q("请先得到最佳路径");
			QMessageBox::critical(this, s2q("错误"), infoStr, QMessageBox::Ok);
			return;
		}
		filePath += "/astarPath_" + fileName;
		fileWrite = new writeFile(filePath, &astarMaze);
		fileWrite->writeMaze(astarPath, to_string(Astar.keyStep - 10));
	}
	
	QString infoStr = s2q("文件保存成功\n文件保存在打开的文件的目录下");
	QMessageBox::information(this, s2q("成功"), infoStr, QMessageBox::Ok);
}

//帮助文档信号槽
void SerachPath::helpActionSlot()
{
	std::string infoText;
	infoText = "本程序运用DFS、BFS、Astar算法，在迷宫中搜索从起点到终点的路径，能够显示搜索的步骤以及最佳路径。\n\n\n";
	infoText += "本程序须知：\n\n";
	infoText += "1、点击“创建迷宫”\t进入迷宫创造界面\n\n";
	infoText += "\t输入所创造的迷宫的行列及名称，在该界面中通过鼠标创建迷宫，最终选择目录保存文件\n";
	infoText += "\t保存的文件为本程序可识别的txt文本，可用于后续“打开文件”使用\n\n";
	infoText += "2、点击“打开文件”\t打开“.txt”文本文件\n\n";
	infoText += "\t该文件内容的格式为：\n\t第一行：两个数字m、n，分别表示迷宫的行与列\n";
	infoText += "\t余下m行：每行n个字符，表示迷宫中坐标为（m，n）的地方的状态\n\t其中：“ ”（一个空格）表示可行路径、“X”（大写英文字母X）表示墙（不可行走）、“S”表示起点、“D”表示终点\n\n";
	infoText += "\t注意：迷宫的最适规模为5*5-30*30，在此情况下程序显示的最为清晰\n\n";
	infoText += "3、设置“搜索算法”\t工具栏最后一项\n\n";
	infoText += "\t共有三种算法可供选择：\n\t深度优先搜索（DFS）、广度优先搜索（BFS）、启发式搜索（Astar）\n\n";
	infoText += "4、点击“寻找路径”\t需先打开文件\n\n";
	infoText += "\t可通过设置好的算法在迷宫中逐步寻找从起点到终点的路径\n";
	infoText += "\t探寻的方向为右→、上↑、左←、下↓\n\t若无可行路径则会弹出消息提示\n\n";
	infoText += "5、点击“得到路径”\t需先寻找路径\n\n";
	infoText += "\t可显示通过之前的寻找而得到的最佳路径\n\n";
	infoText += "6、点击“保存文件”\t需先得到路径\n\n";
	infoText += "\t可将程序的运行结果保存至文本文件中\n\t该文件保存在之前打开的文件的目录下\n\t命名为“算法名称_打开的文件名称”\n\n";
	infoText += "\t该文件的内容的格式为：\n\t前m行：每行n个字符表示迷宫，其中“*”表示从起点到终点的最佳路径\n\t显示该路径的步数step\n\t余下step行：显示从起点到终点的路径的坐标\n\n";
	infoText += "7、滑动“显示速度”拉杆\t速度范围（0-500ms）\n\n";
	infoText += "\t可调节每一步骤显示的速度\n\t如果迷宫规模较大，建议将速度初始值先调大\n\n";
	QString infoStr = s2q(infoText);
	QMessageBox::question(this, s2q("帮助"), infoStr, QMessageBox::Ok);

}

//用于初始化迷宫的laebl，并将其添加至窗口上
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

//用于清空窗口上的label，并清空迷宫label的内存
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

//用于显示搜索的每一步骤
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
					//用于调节显示速度
					QThread::msleep(-setSpeed->value());
				}
			}
		}
		
	}

}

//用于显示最佳路径
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
					//用于调节显示速度
					QThread::msleep(-setSpeed->value());
				}
			}
		}
	}
}

//用于显示迷宫，通过判断迷宫每个点的信息来分别显示不同的素材
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

//滑块的美化函数，源于网络博客
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
