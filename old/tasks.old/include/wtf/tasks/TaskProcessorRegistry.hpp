#pragma once

#include <string>
#include <memory>
#include <map>

#include "wtf/tasks/TaskProcessor.hpp"

namespace  WTF {	
namespace tasks {

	class TaskProcessorRegistry
	{
		public:
			
			TaskProcessorConstPtr getTaskProcessor(const std::string&) const;

			void registerTaskProcessor(const std::string& key, TaskProcessorConstPtr theProcessor);

			static TaskProcessorRegistry& instance();

		private:
			std::map<std::string, TaskProcessorConstPtr> _processors;

	};

}
} // namespace WTF ends

