#pragma once

#include <string>
#include <QMutex>
#include <QFile>
#include <QtGlobal>
#include <mutex>

class Logger
{
public:
	Logger(Logger &other) = delete;
	void operator=(const Logger &) = delete;
	static void Init(const std::string&);

private:
	Logger();
	static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

	static QFile* m_logging_file;
	static Logger* m_logger;
	static QMutex m_logmutex;
	static std::string m_filename;
};
