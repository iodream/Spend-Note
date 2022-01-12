#include <QCoreApplication>
#include "LoggerSkeleton.h"

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	Logger::SetFileName("log1file.log");
	auto p_logger = Logger::GetInstance();
	p_logger->debug() <<  "debug" ;
	p_logger->info() << "debug info";
	return app.exec();
}
