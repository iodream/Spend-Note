#pragma once

#include <string>
#include <QMutex>
#include <QFile>
#include <QtGlobal>


class Logger
{
public:
	enum log_severity
	{
		debug,
		info,
		critical,
		warning,
		fatal,
	};

	Logger(Logger &other) = delete;
	void operator=(const Logger &) = delete;
	static Logger* GetInstance(const std::string filename);
	friend Logger& operator<<(Logger& stream, const char* log_msg);
	static log_severity GetLogSeverity();
	static void SetLogSeverity(const Logger::log_severity& lvl);

private:
	Logger(const std::string filename);
	static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

	static QFile* m_logging_file;
	static Logger* m_logger;
	static QMutex m_mutex;
	std::string m_filename;
	static log_severity m_severity;
};
