#pragma once

#include <string>
#include <fstream>
#include <thread>
#include <mutex>

//use this macro to create logger
#define SCOPED_LOGGER ScopedLogger log(__FILE__, __func__, \
	__LINE__, std::this_thread::get_id())

class ScopedLogger
{
public:
	ScopedLogger(const std::string& file_name, const std::string& func_name,
		const int& line_nr, const std::thread::id& thread_id);
	~ScopedLogger();
	static void Init(const std::string& log_file_name);

private:
	static std::ofstream m_stream;
	std::string m_file_name;
	std::string m_func_name;
	int m_line_nr;
	static std::string m_log_file_name;
	std::thread::id m_thread_id;
	static std::mutex m_log_mutex;
};

