#include "toolbox/ScopedChrono.hpp"
#include <ctime>
#include <chrono>
#include <iostream>

#include "toolbox/Logger.hpp"

////////////////////////////////////////////////////////////////////

namespace toolbox
{

ScopedChrono::ScopedChrono(const std::string& desc)
{
	_desc = desc;
	reset();
}

ScopedChrono::ScopedChrono(const char* desc)
{
	_desc = std::string(desc);
	reset();
}

ScopedChrono::~ScopedChrono()
{
	dump();
}

void ScopedChrono::dump()
{
	Timestamp end = std::chrono::high_resolution_clock::now();	
	std::chrono::duration<double> time_span_sec = std::chrono::duration<double>((end - _startTS) );

	MDW_LOG_PERF( _desc << ":" << 1000 * time_span_sec.count()	<< "ms");
}

void ScopedChrono::reset()
{
    _startTS = std::chrono::high_resolution_clock::now();
}

}
