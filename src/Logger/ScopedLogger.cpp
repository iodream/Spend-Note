#include <fstream>

#include "ScopedLogger.h"
#include <QTime>
#include <QDate>

std::string ScopedLogger::m_log_file_name;
std::ofstream ScopedLogger::m_stream;
std::mutex ScopedLogger::m_log_mutex;


ScopedLogger::ScopedLogger(const std::string& file_name, const std::string& func_name
	, const int& line_nr, const std::thread::id& thread_id)
	: m_file_name(file_name)
	, m_func_name(func_name)
	, m_line_nr(line_nr)
	, m_thread_id(thread_id)
{
	std::lock_guard<std::mutex> lock(m_log_mutex);
	m_stream << QDate::currentDate().toString().toStdString() << " " << QTime::currentTime().toString().toStdString()
			<< " "<< m_file_name << ":" << m_line_nr << "\n"
			<< "[" << m_thread_id << "] " << m_func_name << "() started\n" << std::flush;
}

void ScopedLogger::Init(const std::string& log_file_name)
{
	m_log_file_name = log_file_name;
	m_stream.open(m_log_file_name, std::ios_base::app);
}

ScopedLogger::~ScopedLogger()
{
	std::lock_guard<std::mutex> lock(m_log_mutex);
	m_stream << QDate::currentDate().toString().toStdString() << " " << QTime::currentTime().toString().toStdString()
			<< " " << m_file_name << ":" << m_line_nr << "\n"
			<< "[" << m_thread_id << "] " << m_func_name << "() finished\n" << std::flush;
}
