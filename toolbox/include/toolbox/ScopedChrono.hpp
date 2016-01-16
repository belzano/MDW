#pragma once

#include <string>
#include <ctime>
#include <chrono>

//////////////////////////////////////////////////////////////////////

namespace toolbox
{
typedef std::chrono::high_resolution_clock::time_point Timestamp; 

class ScopedChrono
{
  public:
	ScopedChrono(const std::string& desc);
	ScopedChrono(const char* desc);	
	~ScopedChrono();
	void dump();
	void reset();
	
	std::string _desc;
	//clock_t 	_timestamp;
	
    Timestamp _startTS;
};

}


