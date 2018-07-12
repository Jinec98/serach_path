#pragma once

#include <string>
#include <QDialog>
#include <QThread>
#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "SerachPath.h"
#include "childWindow.h"
#include "myFile.h"
#include "myAlgorithm.h"
#include "Point.h"
#include "Maze.h"
#include <qdebug.h>

inline QString s2q(const std::string &s);
inline std::string q2s(const QString &s);

//主界面类
class SerachPath : public QMainWindow
{
	Q_OBJECT

public:
	SerachPath(QWidget *parent = Q_NULLPTR);
	~SerachPath();

private slots:
	void makeMazeActionSlot();
	void generateMazeActionSlot();
	void openFileActionSlot();
	void findPathActionSlot();
	void getPathActionSlot();
	void saveFileActionSlot();
	void helpActionSlot();
	void aboutActtionSlot();
	
private:
	void createToolBar();
	void initWindow();
	void setWindow();
	void setMap();
	void deleteMap();
	void showMap(Maze maze);
	void printPath(Maze maze,int step);
	void printKeyPath(Maze maze,int step);
	void setSliderQss(QSlider *slider, QString normalColor, QString grooveColor, QString handleColor);

	int widgetWidth;
	int widgetHeight;
	int maxWidth;
	int maxHeight;
	int iconWidth;
	int iconHeight;
	int initWidth;

	QDesktopWidget * desktopWidget;
	QWidget * widget;
	QGridLayout * layout;

	QIcon icon;
	QLabel * initLabel;
	QLabel * initLinkLabel;

	QToolBar * makeMazeTool;
	QToolBar * generateMazeTool;
	QToolBar * openFileTool;
	QToolBar * findPathTool;
	QToolBar * getPathTool;
	QToolBar * saveFileTool;
	QToolBar * helpTool;
	QToolBar * aboutTool;
	QToolBar * setModeTool;
	QToolBar * setSpeedTool;

	QAction * makeMazeAction;
	QAction * generateMazeAction;
	QAction * openFileAction;
	QAction * findPathAction;
	QAction * getPathAction;
	QAction * saveFileAction;
	QAction * helpAction;
	QAction * aboutAction;
	QAction * setSpeedAction;

	QComboBox * setMode;

	QSlider * setSpeed;

	QString fileFullPath;
	QString fileAbsPath;
	string fileName;

	QPixmap blank;
	QPixmap start;
	QPixmap end;
	QPixmap wall;
	QPixmap path;
	QPixmap keyPath;

	vector<vector<QLabel *> > mapLabel;

	openFile * fileOpen;
	writeFile * fileWrite;
	Maze * maze = NULL;
	Maze bfsMaze;
	Maze dfsMaze;
	Maze astarMaze;
	Maze idastarMaze;
	dfs Dfs;
	bfs Bfs;
	aStar Astar;
	idaStar IDAstar;
	Point * dfsResult = NULL;
	Point * bfsResult = NULL;
	Point * astarResult = NULL;
	Point * idastarResult = NULL;
	list<Point*> dfsPath;
	list<Point*> bfsPath;
	list<Point*> astarPath;
	list<Point*> idastarPath;
};
