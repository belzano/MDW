#pragma once

#include <ostream>
#include "logger/Level.hpp"

namespace logger
{
	class Stream 
	{
		public:
			Stream();
			
			void write(Level level,
					   const char* domain, 
					   const char* data);
			
			void write(Level level,
					   const char* domain, 
					   std::ostringstream& stream);
			
			// TODO ostream semantics
			// ostream& operator::<<(Level level, const char* domain, const char* data)
			
		private:
			void writeHeader(Level level, 
							const char* domain, 
							char** ptr, 
							char* eos);
			
			// write utility
			void write(const char* src, char** ptr, char* eos);

			int m_bufferColsCount;
			int m_bufferRowsCount;
			char* m_buffer;
			int m_bufferRow;
			
			int _pid;
			int _tid;
	};
}

