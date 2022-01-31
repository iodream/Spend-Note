#include "Controller/Controller.h"
#include "../Logger/ScopedLogger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	SCOPED_LOGGER;
	QApplication a(argc, argv);
	Controller controller;

	controller.Start();
//	controller.StartTest();
	return a.exec();
}
