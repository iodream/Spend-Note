#include <QtGlobal>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <MessageHandler.h>
#include "module1.h"
#include "module2.h"

Q_DECLARE_LOGGING_CATEGORY(general)


Q_LOGGING_CATEGORY(general, "General")
int main(int argc, char **argv)
{
	qInstallMessageHandler(MessageHandler); // Install the handler
	QCoreApplication app(argc, argv);
	qDebug(general) << "Log started";
	func1();
	auto ret = func2("some text");
	return app.exec();
}
