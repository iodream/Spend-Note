#pragma once

#include <string>
#include <fstream>
#include <thread>

#define SCOPED_LOGGER ScopedLogger log(__FILE__, __func__, __LINE__, std::this_thread::get_id())

class ScopedLogger
{
public:
	ScopedLogger(const std::string& fileName, const std::string& funcName
				, const int& lineNr, const std::thread::id& threadId);
	~ScopedLogger();
	static void Init(const std::string& logFileName);

private:
	static std::ofstream m_logFile;
	std::string m_fileName;
	std::string m_funcName;
	static std::string m_logFileName;
	std::thread::id m_threadId;
};

