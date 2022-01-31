#include <fstream>
#include <QTime>
#include <mutex>

#include "Logger.h"


QMutex Logger::m_logmutex;
QFile* Logger::m_logging_file;
Logger* Logger::m_logger = nullptr;
std::string Logger::m_filename("logfile.log");

Logger::Logger()
{
	qInstallMessageHandler(MessageHandler);
	m_logging_file = new QFile(QString(m_filename.c_str()));
	m_logging_file->open(QIODevice::WriteOnly | QIODevice::Append);
	qDebug() << "Logger created\n" << "Time created:" << QTime::currentTime().toString()<<"\n";
}

void Logger::Init(const std::string& filename)
{
	m_filename=filename;
	m_logger = new Logger;
}

void Logger::MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	using namespace std;

	std::lock_guard<QMutex> lock(m_logmutex);
	QTextStream stream(m_logging_file);

	switch (type)
	{
	case QtDebugMsg:
		stream <<  QString("DBG: ")<<  " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtInfoMsg:
		stream <<  "INF: "<< " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtWarningMsg:
		stream << "WRN: " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtCriticalMsg:
		stream <<  "CRIT: " << " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		break;
	case QtFatalMsg:
		break;
	}
}



