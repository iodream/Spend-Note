
#include <QLoggingCategory>
#include <QtGlobal>
#include "module2.h"

Q_LOGGING_CATEGORY(module2,"module2")
int func2(const char* testString)
{
	qDebug(module2) << "func2 has started executing" << "\n";
	qInfo(module2) << "test string is " << testString << "\n";
	qWarning(module2) << "No data found!"  << "\n";
	return -1;
}
