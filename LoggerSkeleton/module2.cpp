
#include <QLoggingCategory>
#include <QtGlobal>
#include "module2.h"

Q_LOGGING_CATEGORY(module2,"module2")
int func2(const char* testString)
{
	qDebug(module2) << "func2 has started executing";
	qInfo(module2) << "test string is " << testString;
	qWarning(module2) << "No data found!";
	return -1;
}
