#include "Controller/Controller.h"
#include <QApplication>
#include "Logger/Logger.h"
#include "Logger/ScopedLogger.h"

int main(int argc, char *argv[])
{
	Logger::Init("Client.log");
	ScopedLogger::Init("ClientScopedLogger.log"); // mandatory
	SCOPED_LOGGER;
	QApplication a(argc, argv);
	Controller controller;

	controller.Start();
//	controller.StartTest();
	return a.exec();
}
