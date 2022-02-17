#include <fstream>
#include <QTime>

#include "Logger.h"


std::mutex Logger::m_log_mutex;
QFile* Logger::m_logging_file;
QFile* Logger::m_scoped_logging_file;
Logger* Logger::m_logger = nullptr;
std::string Logger::m_file_name("logfile.log");
std::string Logger::m_scoped_file_name("ScopedLogger.log");


Logger::Logger()
{
	qInstallMessageHandler(MessageHandler);
	m_logging_file = new QFile(QString(m_file_name.c_str()));
	m_logging_file->open(QIODevice::WriteOnly | QIODevice::Append);
	m_scoped_logging_file = new QFile(QString(m_scoped_file_name.c_str()));
	m_scoped_logging_file->open(QIODevice::WriteOnly | QIODevice::Append);
	qInfo() << "Logger created at: " <<QDate::currentDate().toString()
			<<" " << QTime::currentTime().toString();
}

void Logger::Init(const std::string& file_name,
				  const std::string& scoped_file_name="ScopedLogger.log")
{
	m_file_name = file_name;
	m_scoped_file_name = scoped_file_name;

	m_logger = new Logger;
}

void Logger::MessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	using namespace std;

	std::lock_guard<std::mutex> lock(m_log_mutex);
	QTextStream stream(m_logging_file);
	QTextStream stream_scoped(m_scoped_logging_file);


	switch (type)
	{
	case QtDebugMsg:
		stream << QDate::currentDate().toString() << " " << QTime::currentTime().toString()
			<< QString("DBG: ")<<  " " << msg << " " << context.file << " " <<  context.line << " "
			<<  context.function << "\n";
		break;
	case QtInfoMsg:
		stream << QDate::currentDate().toString() << " " << QTime::currentTime().toString()
			<<  " INF: "<< " " << msg << "\n";
		break;
	case QtWarningMsg:
		stream << QDate::currentDate().toString() <<" " << QTime::currentTime().toString()
			   <<" WARN: "	<< " " << msg << " " << context.file << " " <<  context.line << " "
			   <<  context.function << "\n";
		stream_scoped << QTime::currentTime().toString() <<" WARN: "
			<< msg << " " << context.file << " " <<  context.line << " "
			<<  context.function << "\n";
		break;
	case QtCriticalMsg:
		stream << QDate::currentDate().toString() << " " << QTime::currentTime().toString()
				<<" CRIT: "	<< " " << msg << " " << context.file << " " <<  context.line << " "
				<<  context.function << "\n";
		stream_scoped << QDate::currentDate().toString() << " " << QTime::currentTime().toString()
			<<" CRIT: "	<< " " << msg << " " << context.file << " " <<  context.line << " "
			<<  context.function << "\n";
		break;
	case QtFatalMsg:
		break;
	}
}



