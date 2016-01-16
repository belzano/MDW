#pragma once

#include "logger/Stack.hpp"

namespace logger
{
	class Stream;

	class ThreadContext
	{
		public:
			
			static ThreadContext& ThreadInstance();
	
			Stream& getLogStream();
			Stack& getStack();
			
		private:
		
			ThreadContext();
			
			Stream* _logStream;
			Stack _stack;
	};

}
