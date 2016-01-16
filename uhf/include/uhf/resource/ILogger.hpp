#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace uhf {	

class ILogger
{
public:
    constexpr static const char* TypeName = "uhf::resource::ILogger";
  
    typedef class enum
    {
	Debug,
	Stat,
	Perf,
	Info,
	Warning,
	Error,
	Fatal
    } 
    Level;
  
    virtual std::ostream& log(LogType) = 0;
};

typedef std::shared_ptr<ILogger> ILoggerPtr;

}
