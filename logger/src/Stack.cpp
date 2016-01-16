#include "logger/Stack.hpp"

using namespace logger;

///////////////////////////////////////

std::ostream& operator<<(std::ostream& ioOut, const Stack& stack)
{
	if (stack.empty())
		return ioOut;

	std::deque<std::string>::const_iterator dequeIt;
	for(dequeIt  = stack.begin();
		dequeIt != stack.end();
		++dequeIt)
	{
		if (dequeIt != stack.begin())
			ioOut << "_";
		ioOut << *dequeIt;
	}
	
	return ioOut;
}
