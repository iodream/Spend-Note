#include <fstream>

#include "ScopedLogger.h"

std::string ScopedLogger::m_logfilename("ScopedLogger.log");
std::ofstream ScopedLogger::m_stream(m_logfilename, std::ios_base::app);
std::mutex ScopedLogger::m_logmutex;


ScopedLogger::ScopedLogger(const std::string& filename, const std::string& funcname
	, const int& linenr, const std::thread::id& threadid)
	: m_filename(filename)
	, m_funcname(funcname)
	, m_threadid(threadid)
{
	std::lock_guard<std::mutex> lock(m_logmutex);
	m_stream << "\n" << filename <<": line "<<linenr <<": "<< funcname
		<< "() started with threadid " << threadid <<"\n" << std::flush;
}

void ScopedLogger::Init(const std::string& logfilename)
{
	m_stream.close();	// close previous file if we are changing logs mid-app execution
	m_logfilename = logfilename;
	m_stream.open(m_logfilename, std::ios_base::app); // open new file
}

ScopedLogger::~ScopedLogger()
{
	std::lock_guard<std::mutex> lock(m_logmutex);
	m_stream << "\n" << m_filename<<": "<< m_funcname
		<< "() finished with threadid " << m_threadid <<"\n" << std::flush;
}
