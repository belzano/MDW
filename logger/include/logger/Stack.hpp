#pragma once

#include <deque>
#include <string>
#include <ostream>

namespace logger
{
	class Stack : public std::deque<std::string> 
	{
	};
}

std::ostream& operator<<(std::ostream& ioOut, const logger::Stack& stack);
