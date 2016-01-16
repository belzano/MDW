#include "uhf/core/component/LoggerConsole.hpp"

#include <iostream>

namespace uhf {
namespace core {
namespace component {
		
/////////////////////////////////////////////////////////////////////

LoggerConsole::LoggerConsole(IBrokerPtr broker)
: IComponent(broker)
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
