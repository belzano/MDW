#include "uhf/core/component/LoggerConsole.hpp"

#include <iostream>

namespace uhf {
namespace core {
namespace component {
		
/////////////////////////////////////////////////////////////////////

LoggerConsole::LoggerConsole()
: IComponent()
{

}
	
/////////////////////////////////////////////////////////////////////

LoggerConsole::~LoggerConsole()
{

}

/////////////////////////////////////////////////////////////////////

void LoggerConsole::log(const char* data)
{
    std::cout << data;
}			
}
}
}
