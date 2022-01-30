#include "ScopedLogger.h"
#include <fstream>

std::string ScopedLogger::m_logFileName("logfile.log");
std::ofstream ScopedLogger::m_logFile(m_logFileName, std::ios_base::app);

ScopedLogger::ScopedLogger(const std::string& fileName, const std::string& funcName
						   , const int& lineNr, const std::thread::id& threadId)
	: m_fileName(fileName)
	, m_funcName(funcName)
	, m_threadId(threadId)
{
	m_logFile << "\n" << fileName <<": line "<<lineNr <<": "<< funcName
		<< "() started with threadid " << threadId <<"\n" << std::flush;
}

void ScopedLogger::Init(const std::string& logFileName)
{
	m_logFileName=logFileName;
	m_logFile.close();
	m_logFile.open(m_logFileName.c_str(), std::ios_base::app);
}

ScopedLogger::~ScopedLogger()
{
	m_logFile << "\n" << m_fileName<<": "<< m_funcName
		<< "() finished with threadid " << m_threadId <<"\n" << std::flush;
	m_logFile.close();
}
