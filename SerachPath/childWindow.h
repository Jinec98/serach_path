#pragma once

#include <QDialog>
#include <QtWidgets/QMainWindow>
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
#include <QMouseEvent>
#include <QFileDialog>
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

	int widgetHeight;
	int widgetWidth;
	int iconEdge;
	QSize iconSize;

	string **maze;
	bool startFlag = false;
	bool endFlag = false;

protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
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
