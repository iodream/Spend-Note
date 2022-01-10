#include <QCoreApplication>
#include "LoggerSkeleton.h"

int main(int argc, char **argv)
{

	QCoreApplication app(argc, argv);
	auto p_logger = Logger::GetInstance("logfile.log");

	*p_logger <<  "hello" ;

	Logger::SetLogSeverity(Logger::warning);

	*p_logger <<  "a warning" ;

	return app.exec();
}
