#include <fstream>
#include <string>
#include <qfile.h>
#include <qmutex.h>
#include "MessageHandler.h"

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	using namespace std;

	QMutex mutex;
	QFile outFile("file.log");
	mutex.lock();
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream stream(&outFile);

	switch (type)
	{
	case QtDebugMsg:
		stream <<  QString("DBG: ")<< context.category << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtInfoMsg:
		stream <<  "INF: "<< context.category << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtWarningMsg:
		stream <<  "WRN: "<< context.category << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtCriticalMsg:
		stream <<  "CRIT: "<< context.category << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtFatalMsg:
		stream <<  "FAT: "<< context.category << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		abort();
	}
		mutex.unlock();
}
