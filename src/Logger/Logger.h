#pragma once

#include <string>
#include <QFile>
#include <QtGlobal>
#include <mutex>

class Logger
{
public:
	Logger(Logger &other) = delete;
	void operator=(const Logger&) = delete;
	static void Init(const std::string&, const std::string&);

private:
	Logger();
	static void MessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

	static QFile* m_logging_file;
	static QFile* m_scoped_logging_file;

	static Logger* m_logger;
	static std::mutex m_log_mutex;
	static std::string m_file_name;
	static std::string m_scoped_file_name;

};
