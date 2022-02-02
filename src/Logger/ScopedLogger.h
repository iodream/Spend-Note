#pragma once

#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <QMutex>

//use this macro to create logger
#define SCOPED_LOGGER ScopedLogger log(__FILE__, __func__ \
	, __LINE__, std::this_thread::get_id())

class ScopedLogger
{
public:
	ScopedLogger(const std::string& filename, const std::string& funcname
	, const int& linenr, const std::thread::id& threadid);
	~ScopedLogger();
	static void Init(const std::string& logfilename);

private:
	static std::ofstream m_stream;
	std::string m_filename;
	std::string m_funcname;
	static std::string m_logfilename;
	std::thread::id m_threadid;
	static QMutex m_logmutex;
};

