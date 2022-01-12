#include <QCoreApplication>
#include "LoggerSkeleton.h"



int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	Logger::Init("log1file.log");
	qDebug() << "hello" << "\n";
	qInfo() << "hello_info" << "\n";
	return app.exec();
}
