#include <fstream>

#include "ScopedLogger.h"

std::string ScopedLogger::m_logfilename("ScopedLogger.log");
std::ofstream ScopedLogger::m_stream(m_logfilename, std::ios_base::app);

ScopedLogger::ScopedLogger(const std::string& filename, const std::string& funcname
	, const int& linenr, const std::thread::id& threadid)
	: m_filename(filename)
	, m_funcname(funcname)
	, m_threadid(threadid)
{
	m_stream << "\n" << filename <<": line "<<linenr <<": "<< funcname
		<< "() started with threadid " << threadid <<"\n" << std::flush;
	m_stream.close();
}

void ScopedLogger::Init(const std::string& logfilename)
{
	std::remove(m_logfilename.c_str());
	m_logfilename=logfilename;
	m_stream.close();
}

ScopedLogger::~ScopedLogger()
{
	m_stream.open(m_logfilename.c_str(), std::ios_base::app);
	m_stream << "\n" << m_filename<<": "<< m_funcname
		<< "() finished with threadid " << m_threadid <<"\n" << std::flush;
	m_stream.close();
}
