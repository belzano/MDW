#include "logger/Module.hpp"
#include "logger/Stream.hpp"
#include "Manager.hpp"

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

// TO get PID/TID
#include <sys/syscall.h>
#include <sys/types.h>

using namespace logger;

////////////////////////////////////

Stream::Stream()
	: m_bufferColsCount(1024)
	, m_bufferRowsCount(256)
	, m_buffer(nullptr)
	, m_bufferRow(0)
{
	_pid = syscall(SYS_getpid);
	_tid = syscall(SYS_gettid);
	
	m_buffer = new char[m_bufferColsCount*m_bufferRowsCount];
}

////////////////////////////////////

void Stream::write(const char* src, char** ptr, char* eos)
{
	size_t remainingBytes = eos - *ptr;
	size_t dataLen = strlen(src);
	size_t sizeToWrite = std::min(remainingBytes, dataLen);
	
	memcpy(*ptr, src, sizeToWrite );
	*ptr = *ptr + sizeToWrite;
}
			
////////////////////////////////////

void Stream::write(Level level,
			 	   const char* domain, 
				   std::ostringstream& stream)
{
	Stream::write(level, domain, stream.str().c_str());
}
			
////////////////////////////////////

void Stream::write(Level level, const char* domain, const char* data)
{
	// TODO early exit if this level is deactivated
	
	
	// Get an available row
	char* bufferRow = m_buffer + m_bufferColsCount*m_bufferRow;
	 
	char** ptr = &bufferRow;
	char*  eos = bufferRow + m_bufferColsCount;
	
	// write header
	writeHeader(level, domain, ptr, eos);
	// write data
	write(data, ptr, eos);
	// fill with zeroes
	memset(*ptr, 0, eos - *ptr);
	
	// set index to next avl row
	m_bufferRow++;
	m_bufferRow = m_bufferRow % m_bufferRowsCount;
	
	// Signal the DQer thread there's new logs
	Module::Instance().getManager().signal();
}
			
////////////////////////////////////////////////

void Stream::writeHeader(Level level, const char*/*domain*/,  char** ptr, char* eos)
{
	std::stringstream tempBuffer;
	
	const char sep = ' ';
	// TS
	tempBuffer << boost::posix_time::second_clock::universal_time().time_of_day() << sep;
		
	// LEVEL	
	switch(level)
	{
		case Debug:
			tempBuffer << "DEBUG";
		break;
		case Stat:
			tempBuffer << "STATS";
		break;
		case Perf:
			tempBuffer << "PERFS";
		break;
		case Info:
			tempBuffer << "INFOS";
		break;
		case Warning:
			tempBuffer << "WARNG";
		break;
		case Error:
			tempBuffer << "ERROR";
		break;
		case Fatal:
			tempBuffer << "FATAL";
		break;
	}
	tempBuffer << sep;

	// PID
	tempBuffer << "PID#" << _pid << sep;
	
	// TID
	tempBuffer << "TID#" << _tid << sep;
	
	// TODO useless copy with .str()
	write(tempBuffer.str().c_str(), ptr, eos);
}

////////////////////////////////////////////////

