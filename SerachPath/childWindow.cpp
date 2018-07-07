#include "childWindow.h"

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

setMazeWindow::setMazeWindow(QWidget *parent) : QDialog(parent)
{
	QIcon icon;
	icon.addFile(QStringLiteral(":/SerachPath/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowTitle(QObject::tr("SerachPath@Jinec"));
	setWindowIcon(icon);
	setWindowOpacity(0.9);
	setFixedSize(220, 200);

	rowsLabel = new QLabel(s2q("迷宫行数："));
	rowsLabel->setGeometry(20, 20, 80, 20);
	rowsLabel->setParent(this);
	rowsText = new QLineEdit;
	rowsText->setGeometry(100, 20, 100, 20);
	rowsText->setParent(this);

	colsLabel = new QLabel(s2q("迷宫列数："));
	colsLabel->setGeometry(20, 60, 80, 20);
	colsLabel->setParent(this);
	colsText = new QLineEdit;
	colsText->setGeometry(100, 60, 100, 20);
	colsText->setParent(this);

	nameLabel = new QLabel(s2q("迷宫名称："));
	nameLabel->setGeometry(20, 100, 80, 20);
	nameLabel->setParent(this);
	nameText = new QLineEdit;
	nameText->setGeometry(100, 100, 100, 20);
	nameText->setParent(this);

	commitBtn = new QPushButton(s2q("确认"));
	commitBtn->setGeometry(80, 150, 60, 30);
	commitBtn->setParent(this);
	connect(commitBtn, &QPushButton::clicked, this, &setMazeWindow::commitBtnSlot);
}

setMazeWindow::~setMazeWindow()
{

}

void setMazeWindow::commitBtnSlot()
{
	QString rowsStr = rowsText->text();
	QString colsStr = colsText->text();
	QString nameStr = nameText->text();
	if (rowsStr.isEmpty() || colsStr.isEmpty() || nameStr.isEmpty())
	{
		QMessageBox::critical(this, s2q("错误"), s2q("输入不能为空！"), QMessageBox::Ok);
		return;
	}	
	else
	{
		int rows = rowsStr.toInt();
		int cols = colsStr.toInt();
		string name = q2s(nameStr);

		if (rows > 50 || cols > 50)
		{
			QMessageBox::critical(this, s2q("错误"), s2q("迷宫规模太大，请重新输入！"), QMessageBox::Ok);
			return;
		}

		makeMazeWindow *setMaze = new makeMazeWindow(cols, rows, name);
		setMaze->show();
		close();
	}
}

makeMazeWindow::makeMazeWindow(QWidget *parent) :QWidget(parent)
{

}

makeMazeWindow::makeMazeWindow(int cols, int rows, string name, QWidget *parent) : QWidget(parent)
{
	this->cols = cols;
	this->rows = rows;
	this->name = name;
	maze = new string *[rows];
	for (int i = 0; i < rows; i++)
		maze[i] = new string[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			maze[i][j] = " ";

	blank = QPixmap(":/SerachPath/Resources/blank_maker.png");
	start = QPixmap(":/SerachPath/Resources/start_maker.png");
	end = QPixmap(":/SerachPath/Resources/end_maker.png");
	wall = QPixmap(":/SerachPath/Resources/wall_maker.png");

	QIcon icon;
	icon.addFile(QStringLiteral(":/SerachPath/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowTitle(s2q("SerachPath_MazeCreater@Jinec"));
	setWindowIcon(icon);
	setWindowOpacity(0.9);
	setMouseTracking(true);
	setFixedSize(1000, 800);
	layout = new QHBoxLayout();
	leftWidget = new QWidget();
	rightWidget = new QWidget();
	leftWidget->setMouseTracking(true);
	rightWidget->setMouseTracking(true);
	layout->addWidget(leftWidget, 2);
	layout->addWidget(rightWidget, 8);
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);

	leftLayout = new QVBoxLayout();
	modeGroup = new QButtonGroup();
	QString mode[] = { s2q("起点"), s2q("终点"), s2q("墙壁"), s2q("道路") };
	for (int i = 0; i < 4; i++)
	{
		modeBtn[i] = new QRadioButton(mode[i]);
		modeLabel[i] = new QLabel();
		modeGroup->addButton(modeBtn[i], i);
	}
	QLabel *setModeStr1 = new QLabel(s2q("选择目标后，\n点击右侧网格即可。"));
	QLabel *setModeStr2 = new QLabel(s2q("选择目标："));
	QFont font1("Microsoft YaHei", 12, 75);
	QFont font2("Microsoft YaHei", 18, 75);
	setModeStr1->setFont(font1);
	setModeStr2->setFont(font2);
	leftLayout->addWidget(setModeStr1);
	leftLayout->addWidget(setModeStr2);
	modeLabel[0]->setPixmap(start);
	leftLayout->addWidget(modeBtn[0]);
	leftLayout->addWidget(modeLabel[0]);
	modeLabel[1]->setPixmap(end);
	leftLayout->addWidget(modeBtn[1]);
	leftLayout->addWidget(modeLabel[1]);
	modeLabel[2]->setPixmap(wall);
	leftLayout->addWidget(modeBtn[2]);
	leftLayout->addWidget(modeLabel[2]);
	modeLabel[3]->setPixmap(blank);
	leftLayout->addWidget(modeBtn[3]);
	leftLayout->addWidget(modeLabel[3]);
	QPushButton *commitBtn = new QPushButton(s2q("保存"));
	commitBtn->setFixedSize(100,50);
	leftLayout->addWidget(commitBtn);
	connect(commitBtn, &QPushButton::clicked, this, &makeMazeWindow::commitBtnSlot);
	leftWidget->setLayout(leftLayout);

}

makeMazeWindow::~makeMazeWindow()
{}

void makeMazeWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	widgetHeight = (*rightWidget).height() - 20;
	widgetWidth = (*rightWidget).width() - 20;
	iconEdge = min(widgetWidth / rows, widgetHeight / cols);
	iconSize = QSize(iconEdge, iconEdge);
	painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
	QPen pen;
	pen.setWidth(5);
	painter.setPen(pen);
	painter.drawLine(this->width() - widgetWidth - 60, 0, this->width() - widgetWidth - 60, this->height());
	painter.fillRect(QRect(this->width() - widgetWidth - 10, 10, iconSize.width()*cols, iconSize.height()*rows), QBrush(Qt::white));
	pen.setWidth(2);
	painter.setPen(pen);
	for (int i = 0; i < cols + 1; i++)
		painter.drawLine(this->width() - widgetWidth - 10 + i * iconSize.width(), 10, this->width() - widgetWidth - 10 + i * iconSize.width(), 10 + iconSize.height()*rows);
	for (int i = 0; i < rows + 1; i++)
		painter.drawLine(this->width() - widgetWidth - 10, 10 + i * iconSize.height(), this->width() - widgetWidth - 10 + iconSize.width()*cols, 10 + i * iconSize.height());
}

void makeMazeWindow::mouseMoveEvent(QMouseEvent *event)
{
	int posx = event->pos().x();
	int posy = event->pos().y();
	if (posx >= this->width() - widgetWidth - 10 && posx <= this->width() - widgetWidth - 10 + iconSize.width()*cols && posy >= 10 && posy <= 10 + iconSize.height()*rows)
		setCursor(Qt::PointingHandCursor);
	else
		setCursor(Qt::ArrowCursor);
}

void makeMazeWindow::mouseReleaseEvent(QMouseEvent *event)
{
	int posx = event->pos().x();
	int posy = event->pos().y();
	if (posx - (this->width() - widgetWidth - 10) >= 0 && posy >= 10)
	{
		int x = (posx - (this->width() - widgetWidth - 10)) / iconSize.width();
		int y = (posy - 10) / iconSize.height();

		if (x >= 0 && x < cols && y >= 0 && y < rows)
		{
			if (modeGroup->checkedId() == 0)
			{
				if (startFlag)
				{
					QMessageBox::critical(this, s2q("错误"), s2q("只能设定一个起点！"), QMessageBox::Ok);
					return;
				}
				startFlag = true;
				maze[y][x] = "S";
				QLabel *pic = new QLabel();
				pic->setScaledContents(true);
				pic->setPixmap(start);
				pic->setGeometry(10 + x * iconSize.width(), 10 + y * iconSize.height(), iconSize.width(), iconSize.height());
				pic->setParent(rightWidget);
				pic->show();
			}
			else if (modeGroup->checkedId() == 1)
			{
				if (endFlag)
				{
					QMessageBox::critical(this, s2q("错误"), s2q("只能设定一个终点！"), QMessageBox::Ok);
					return;
				}
				endFlag = true;
				maze[y][x] = "D";
				QLabel *pic = new QLabel();
				pic->setScaledContents(true);
				pic->setPixmap(end);
				pic->setGeometry(10 + x * iconSize.width(), 10 + y * iconSize.height(), iconSize.width(), iconSize.height());
				pic->setParent(rightWidget);
				pic->show();
			}
			else if (modeGroup->checkedId() == 2)
			{
				if (maze[y][x] == "S")
					startFlag = false;
				else if (maze[y][x] == "D")
					endFlag = false;

				maze[y][x] = "X";
				QLabel *pic = new QLabel();
				pic->setScaledContents(true);
				pic->setPixmap(wall);
				pic->setGeometry(10 + x * iconSize.width(), 10 + y * iconSize.height(), iconSize.width(), iconSize.height());
				pic->setParent(rightWidget);
				pic->show();
			}
			else if (modeGroup->checkedId() == 3)
			{
				if (maze[y][x] == "S")
					startFlag = false;
				else if (maze[y][x] == "D")
					endFlag = false;

				maze[y][x] = " ";
				QLabel *pic = new QLabel();
				pic->setScaledContents(true);
				pic->setPixmap(blank);
				pic->setGeometry(10 + x * iconSize.width(), 10 + y * iconSize.height(), iconSize.width(), iconSize.height());
				pic->setParent(rightWidget);
				pic->show();

			}
		}
	}
}

void makeMazeWindow::commitBtnSlot()
{
	if (startFlag && endFlag)
	{
		QMessageBox::information(this, s2q("提示"), s2q("若程序安装在C盘默认路径下，则需保存至其他目录！"), QMessageBox::Ok);

		QFileDialog *fileDialog = new QFileDialog(this);
		fileDialog->setWindowTitle("Open Directory");
		fileDialog->setFileMode(QFileDialog::Directory);
		fileDialog->setViewMode(QFileDialog::Detail);

		string directoryPath;
		//判断文件是否正常打开
		if (fileDialog->exec())
		{
			QString fullPath = fileDialog->selectedFiles()[0];
			directoryPath = q2s(fullPath);
		}
		else
			return;

		ofstream writeFile(directoryPath + "/" + name + ".txt");
		writeFile << rows << " " << cols << "\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				writeFile << maze[i][j];
			writeFile << "\n";
		}
		writeFile.close();
		close();
	}
	else
		QMessageBox::critical(this, s2q("错误"), s2q("请设置起点和终点！"), QMessageBox::Ok);
}

generateMazeWinodw::generateMazeWinodw(QWidget *parent) : QDialog(parent)
{
	setWindowTitle(s2q("SerachPath@Jinec"));
	setWindowOpacity(0.9);
	setFixedSize(250, 360);

	mazeSizeGroup = new QButtonGroup();
	QString mazeSize[] = { s2q("超小规模 （5*5）"),s2q("较小规模 （9*9）"),s2q("中等规模 （15*15）"),s2q("较大规模 （19*19）"),s2q("超大规模 （25*25）"),s2q("自定义规模（仅支持奇数）") };
	for (int i = 0; i < 6; i++)
	{
		mazeSizeBtn[i] = new QRadioButton(mazeSize[i]);
		mazeSizeGroup->addButton(mazeSizeBtn[i], i);
		mazeSizeBtn[i]->setGeometry(20, 20 + i * 40, 160, 20);
		mazeSizeBtn[i]->setParent(this);
	}
	mazeSizeBtn[0]->setChecked(true);

	customSizeRowsText = new QLineEdit;
	customSizeRowsText->setGeometry(180, 220, 20, 20);
	customSizeRowsText->setParent(this);

	customMultiLabel = new QLabel(s2q("*"));
	customMultiLabel->setGeometry(203, 220, 7, 20);
	customMultiLabel->setParent(this);

	customSizeColsText = new QLineEdit;
	customSizeColsText->setGeometry(210, 220, 20, 20);
	customSizeColsText->setParent(this);

	nameLabel = new QLabel(s2q("迷宫名称："));
	nameLabel->setGeometry(20, 260, 60, 20);
	nameLabel->setParent(this);
	nameText = new QLineEdit;
	nameText->setGeometry(80, 260, 120, 20);
	nameText->setParent(this);

	commitBtn = new QPushButton(s2q("生成迷宫并保存"));
	commitBtn->setGeometry(70, 300, 110, 40);
	commitBtn->setParent(this);
	connect(commitBtn, &QPushButton::clicked, this, &generateMazeWinodw::commitBtnSlot);
}

generateMazeWinodw::~generateMazeWinodw()
{

}

void generateMazeWinodw::commitBtnSlot()
{
	int mazeSizeMode;
	int rows, cols;
	mazeSizeMode = mazeSizeGroup->checkedId();
	if (mazeSizeMode == 0)
	{
		rows = 5;
		cols = 5;
	}
	else if (mazeSizeMode == 1)
	{
		rows = 9;
		cols = 9;
	}
	else if (mazeSizeMode == 2)
	{
		rows = 15;
		cols = 15;
	}
	else if (mazeSizeMode == 3)
	{
		rows = 19;
		cols = 19;
	}
	else if (mazeSizeMode == 4)
	{
		rows = 25;
		cols = 25;
	}
	else if (mazeSizeMode == 5)
	{
		QString rowsStr = customSizeRowsText->text();
		QString colsStr = customSizeColsText->text();
		if (rowsStr.isEmpty() || colsStr.isEmpty())
		{
			QMessageBox::critical(this, s2q("错误"), s2q("“迷宫规模”输入不能为空！"), QMessageBox::Ok);
			return;
		}
		else
		{
			rows = rowsStr.toInt();
			cols = colsStr.toInt();
			if (rows % 2 == 0 || cols % 2 == 0)
			{
				QMessageBox::critical(this, s2q("错误"), s2q("“迷宫规模”输入不能为偶数！"), QMessageBox::Ok);
				return;
			}
		}
	}
	string name;
	QString nameStr = nameText->text();
	if (nameStr.isEmpty())
	{
		QMessageBox::critical(this, s2q("错误"), s2q("“迷宫名称”不能为空！"), QMessageBox::Ok);
		return;
	}
	else
		name = q2s(nameStr);
	
	if (rows > 50 || cols > 50)
	{
		QMessageBox::critical(this, s2q("错误"), s2q("迷宫规模太大，请重新输入！"), QMessageBox::Ok);
		return;
	}

	GenerateMaze = new generateMaze(rows + 2, cols + 2);
	GenerateMaze->genMaze();

	QMessageBox::information(this, s2q("提示"), s2q("若程序安装在C盘默认路径下，则需保存至其他目录！"), QMessageBox::Ok);
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle("Open Directory");
	fileDialog->setFileMode(QFileDialog::Directory);
	fileDialog->setViewMode(QFileDialog::Detail);

	string directoryPath;
	//判断文件是否正常打开
	if (fileDialog->exec())
	{
		QString fullPath = fileDialog->selectedFiles()[0];
		directoryPath = q2s(fullPath);
	}
	else
		return;

	GenerateMaze->outputMaze(directoryPath, name);
	close();
}

generateMazeWinodw::generateMaze::generateMaze(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	maze = new Gird *[rows];
	for (int i = 0; i < rows; i++)
		maze[i] = new Gird[cols];
	mazeStr = new string *[rows];
	for (int i = 0; i < rows; i++)
		mazeStr[i] = new string[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			maze[i][j].dig = false;
			if (i % 2 != 0 && j % 2 != 0)
				maze[i][j].cell = true;
			else
				maze[i][j].cell = false;
		}
	}
	Point startPoint;
	startPoint.row = 1;
	startPoint.col = 1;
	mazeStack.push(startPoint);
	srand(time(0));
}

generateMazeWinodw::generateMaze::~generateMaze()
{

}

int generateMazeWinodw::generateMaze::dirRand()
{
	int resultDir = 0;
	dirList.clear();
	Point thisPoint;
	thisPoint = mazeStack.top();
	if (thisPoint.row - 2 > 0 && !maze[thisPoint.row - 2][thisPoint.col].dig)
		dirList.push_back(0);
	if (thisPoint.row + 2 < rows - 1 && !maze[thisPoint.row + 2][thisPoint.col].dig)
		dirList.push_back(1);
	if (thisPoint.col - 2 > 0 && !maze[thisPoint.row][thisPoint.col - 2].dig)
		dirList.push_back(2);
	if (thisPoint.col + 2 < cols - 1 && !maze[thisPoint.row][thisPoint.col + 2].dig)
		dirList.push_back(3);

	if (dirList.size() == 0)
		resultDir = -1;
	else
		resultDir = dirList[rand() % ((int)dirList.size())];

	return resultDir;
}

void generateMazeWinodw::generateMaze::genMaze()
{
	while (!mazeStack.empty())
	{
		int dir = dirRand();
		Point thisPoint = mazeStack.top();
		Point nextPoint;
		if (dir == -1)
			mazeStack.pop();
		else
		{
			if (dir == 0)
			{
				maze[thisPoint.row - 2][thisPoint.col].dig = true;
				maze[thisPoint.row - 1][thisPoint.col].dig = true;
				nextPoint.row = thisPoint.row - 2;
				nextPoint.col = thisPoint.col;
				mazeStack.push(nextPoint);
			}
			else if(dir == 1)
			{
				maze[thisPoint.row + 2][thisPoint.col].dig = true;
				maze[thisPoint.row + 1][thisPoint.col].dig = true;
				nextPoint.row = thisPoint.row + 2;
				nextPoint.col = thisPoint.col;
				mazeStack.push(nextPoint);
			}
			else if (dir == 2)
			{
				maze[thisPoint.row][thisPoint.col - 2].dig = true;
				maze[thisPoint.row][thisPoint.col - 1].dig = true;
				nextPoint.row = thisPoint.row;
				nextPoint.col = thisPoint.col - 2;
				mazeStack.push(nextPoint);
			}
			else if (dir == 3)
			{
				maze[thisPoint.row][thisPoint.col + 2].dig = true;
				maze[thisPoint.row][thisPoint.col + 1].dig = true;
				nextPoint.row = thisPoint.row;
				nextPoint.col = thisPoint.col + 2;
				mazeStack.push(nextPoint);
			}
		}
	}
}

void generateMazeWinodw::generateMaze::outputMaze(string directoryPath, string name)
{
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (maze[i][j].cell || maze[i][j].dig)
				mazeStr[i-1][j-1] = " ";
			else
				mazeStr[i-1][j-1] = "X";
		}
	}
	mazeStr[0][0] = "S";
	mazeStr[rows - 3][cols - 3] = "D";

	ofstream writeFile(directoryPath + "/" + name + ".txt");
	writeFile << rows - 2 << " " << cols - 2 << "\n";
	for (int i = 0; i < rows - 2; i++)
	{
		for (int j = 0; j < cols - 2; j++)
			writeFile << mazeStr[i][j];
		writeFile << "\n";
	}
	writeFile.close();
}