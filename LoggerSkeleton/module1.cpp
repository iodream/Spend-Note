
#include <QLoggingCategory>
#include <QtGlobal>
#include "module1.h"

Q_LOGGING_CATEGORY(module1,"module1")
void func1()
{
	qDebug(module1) << "func1 has started executing";
	qInfo(module1) << "module1 is performing work";
}
