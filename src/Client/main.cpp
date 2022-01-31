#include "Controller/Controller.h"
#include "../Logger/ScopedLogger.h"
#include <QApplication>
#include "Logger/Logger.h"
int main(int argc, char *argv[])
{
	SCOPED_LOGGER;
	Logger::Init("Client.log");
	QApplication a(argc, argv);
	Controller controller;

	controller.Start();
//	controller.StartTest();
	return a.exec();
}
