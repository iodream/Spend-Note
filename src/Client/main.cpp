#include "Controller/Controller.h"
#include <QApplication>
#include "Logger/Logger.h"
int main(int argc, char *argv[])
{
	Logger::Init("Client.log");
	QApplication a(argc, argv);
	Controller controller;

	controller.Start();
//	controller.StartTest();
	return a.exec();
}
