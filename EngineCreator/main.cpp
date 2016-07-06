#include "enginecreator.h"
#include "mainwindow.h"
#include <QTextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowState(Qt::WindowMaximized);
	w.show();	
	return a.exec();
}
