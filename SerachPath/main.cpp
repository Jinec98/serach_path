#include "SerachPath.h"
#include <QtWidgets/QApplication>

//����������
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	SerachPath window;
	window.show();

	return a.exec();
}
