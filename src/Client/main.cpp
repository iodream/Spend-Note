#include "Controller/Controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Controller controller;
	controller.Start();
//	controller.StartTest();
    return a.exec();
}
