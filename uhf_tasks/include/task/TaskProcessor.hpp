#pragma once

#include <string>
#include "task/Task.hpp"
#include "toolbox/Types.hpp"

namespace uhf {	
namespace tasks {

	class TaskProcessor
	{
		public:
		
			typedef std::string Type;
		
			TaskProcessor(const char* iType);
			Type getType() const {return m_type; }
			
			virtual int process(TaskPtr&) const = 0;
			
		private:
			Type m_type;
	};
	
	typedef std::shared_ptr<const TaskProcessor> TaskProcessorConstPtr;
}
}
