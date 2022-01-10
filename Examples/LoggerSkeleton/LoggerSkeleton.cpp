#include "LoggerSkeleton.h"
#include <fstream>
#include <QTime>
#include <mutex>

Logger* Logger::m_logger = nullptr;
QMutex Logger::m_mutex;
Logger::log_severity Logger::m_severity = debug;
QFile* Logger::m_logging_file;

Logger::Logger(const std::string filename): m_filename(filename)
{
	qInstallMessageHandler(MessageHandler);
	m_logging_file = new QFile(QString(filename.c_str()));
	m_logging_file->open(QIODevice::WriteOnly | QIODevice::Append);
	qDebug() << "Logger created\n" << "Time created:" << QTime::currentTime().toString()<<"\n";
}

void Logger::MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	using namespace std;

	std::lock_guard<QMutex> lock(m_mutex);
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
		stream <<  "FAT: "<<  " " << msg << " " << context.file << " " <<  context.line << " "
			 <<  context.function << "\n";
		abort();
	}
}

Logger* Logger::GetInstance(const std::string filename)
{
	   if (m_logger == nullptr)
		   m_logger = new Logger(filename);

	   return m_logger;
}

Logger& operator<<(Logger& stream, const char* log_msg)
{
	using log = Logger::log_severity;
	switch(Logger::GetLogSeverity())
	{
	case log::debug:
		qDebug() << QString(log_msg) << "\n";
		break;
	case log::info:
		qInfo() << QString(log_msg) << "\n";
		break;
	case log::warning:
		qWarning() << QString(log_msg) << "\n";
		break;
	case log::critical:
		qCritical() << QString(log_msg) << "\n";
		break;
	case log::fatal:
		qFatal(log_msg);
		break;
	default:
		qDebug() << QString(log_msg) << "\n";
	};
	return stream;
}

inline Logger::log_severity Logger::GetLogSeverity()
{
   return m_severity;
}

void Logger::SetLogSeverity(const Logger::log_severity& severity)
{
	m_severity=severity;
}
