#include <QtGlobal>
#include <QCoreApplication>
#include "thread"
#include "MessageHandler.h"
#include "module1.h"
#include "module2.h"


Q_DECLARE_LOGGING_CATEGORY(general)


Q_LOGGING_CATEGORY(general, "General")
int main(int argc, char **argv)
{

	QCoreApplication app(argc, argv);

	qInstallMessageHandler(MessageHandler); // Install the handler
	std::thread t1(func1);					// test some threads
	std::thread t2(func2, "text");
	std::thread t3(func1);
	t1.join();
	t2.join();
	t3.join();

	qDebug(general) << "Log started";		//standard log msg
	func1();
	auto ret = func2("some text");

	return app.exec();
}
