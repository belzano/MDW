#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace uhf {	
namespace tasks {
	
	class Task
	{
		public:
		
			typedef std::string Type;
		
			Task(const char* iType);
		
			Type getType() const {return m_type; }
			
			virtual int run() = 0;
			
		private:
			Type m_type;
	};
	
	typedef std::shared_ptr<Task> TaskPtr;
}
}
