#pragma once

#include <QDialog>
#include <QtWidgets>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QMessageBox>
#include <QtGui>
#include <QDesktopServices>
#include <QFileDialog>
#include <QApplication>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>
#include <vector>
#include <ctime>

using namespace std;

class setMazeWindow : public QDialog
{
	Q_OBJECT

public:
	explicit setMazeWindow(QWidget *parent = 0);
	~setMazeWindow();

private slots:
	void commitBtnSlot();

private:
	QLabel * colsLabel;
	QLabel *rowsLabel;
	QLabel *nameLabel;

	QLineEdit *colsText;
	QLineEdit *rowsText;
	QLineEdit *nameText;

	QPushButton *commitBtn;
};

class makeMazeWindow : public QWidget
{
	Q_OBJECT

public:
	explicit makeMazeWindow(QWidget *parent = 0);
	makeMazeWindow(int cols, int rows, string name = "untitled", QWidget *parent = 0);
	~makeMazeWindow();
	int cols;
	int rows;
	string name;
	QPixmap blank;
	QPixmap start;
	QPixmap end;
	QPixmap wall;
	QHBoxLayout *layout;
	QWidget *leftWidget;
	QWidget *rightWidget;
	QVBoxLayout *leftLayout;
	QButtonGroup *modeGroup;
	QRadioButton *modeBtn[4];
	QLabel *modeLabel[4];
	QLabel ***mazePicLabel;

	int widgetHeight;
	int widgetWidth;
	int iconEdge;
	QSize iconSize;

	string **maze;
	bool startFlag = false;
	bool endFlag = false;
	bool isPress = false;

protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void commitBtnSlot();
};

class generateMazeWinodw : public QDialog
{
	Q_OBJECT

public:
	explicit generateMazeWinodw(QWidget *parent = 0);
	~generateMazeWinodw();

private slots:
	void commitBtnSlot();

private:
	QRadioButton * mazeSizeBtn[6];
	QButtonGroup * mazeSizeGroup;
	QLabel * customMultiLabel;
	QLineEdit * customSizeRowsText;
	QLineEdit * customSizeColsText;
	QLabel * nameLabel;
	QLineEdit * nameText;
	QPushButton * commitBtn;

	class generateMaze
	{
	public:
		generateMaze(int rows, int cols);
		~generateMaze();

		int dirRand();
		void genMaze();
		void outputMaze(string directoryPath, string name);

	private:
		struct Gird
		{
			bool cell;
			bool dig;
		}**maze;
		struct Point
		{
			int row;
			int col;
		};
		int rows, cols;
		string **mazeStr;
		stack<Point> mazeStack;
		vector<int> dirList;
	};
	generateMaze * GenerateMaze;
};

class showAboutWindow : public QWidget
{
	Q_OBJECT

public:
	explicit showAboutWindow();
	~showAboutWindow();

	enum  Type
	{
		None = 0,
		Amplification,
		Shrink,
		Move
	};

private:
	QPixmap * classDiagramPix;
	int actionMode;          //动作(放大,缩小,移动...)
	QRect paintArea;         //绘画区域
	float pixRatio;                //比例
	int pixWidth;
	int pixHeight;
	QPoint pixOffset;              //一次的图片偏移值
	QPoint allOffset;           //总偏移
	bool isPress;
	QPoint prePoint;
	QLabel *linkLabel;
	QLabel *ratioLabel;

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);     //鼠标滑轮事件
	void paintEvent(QPaintEvent *event);

};
