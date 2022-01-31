#include <fstream>

#include "ScopedLogger.h"

std::string ScopedLogger::m_loggerName("ScopedLogger.log");
std::ofstream ScopedLogger::m_logger(m_loggerName, std::ios_base::app);

ScopedLogger::ScopedLogger(const std::string& fileName, const std::string& funcName
	, const int& lineNr, const std::thread::id& threadId)
	: m_fileName(fileName)
	, m_funcName(funcName)
	, m_threadId(threadId)
{
	m_logger << "\n" << fileName <<": line "<<lineNr <<": "<< funcName
		<< "() started with threadid " << threadId <<"\n" << std::flush;
}

void ScopedLogger::Init(const std::string& logFileName)
{
	m_loggerName=logFileName;
	m_logger.close();
	m_logger.open(m_loggerName.c_str(), std::ios_base::app);
}

ScopedLogger::~ScopedLogger()
{
	m_logger << "\n" << m_fileName<<": "<< m_funcName
		<< "() finished with threadid " << m_threadId <<"\n" << std::flush;
	m_logger.close();
}
