#include "MessageHandler.h"
#include <fstream>
#include <string>
#include <string>

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	using namespace std;

	ofstream out("logfile.txt",ios_base::app);
	string local(msg.toUtf8().data());

	switch (type) {
	case QtDebugMsg:
		out <<  "DBG: "<< context.category << " " << local << " " << context.file << " " <<  context.line << " "
			 <<  context.function << endl;
		break;
	case QtInfoMsg:
		out <<  "INF: "<< context.category << " " << local << " " << context.file << " " <<  context.line << " "
			 <<  context.function << endl;
		break;
	case QtWarningMsg:
		out <<  "WRN: "<< context.category << " " << local << " " << context.file << " " <<  context.line << " "
			 <<  context.function << endl;
		break;
	case QtCriticalMsg:
		out <<  "CRIT: "<< context.category << " " << local << " " << context.file << " " <<  context.line << " "
			 <<  context.function << endl;
		break;
	case QtFatalMsg:
		out <<  "FAT: "<< context.category << " " << local << " " << context.file << " " <<  context.line << " "
			 <<  context.function << endl;
		abort();
	}
}
