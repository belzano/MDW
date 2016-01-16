
#include "task/TaskProcessorRegistry.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>
#include <iterator>

namespace uhf {
namespace tasks {

TaskProcessorRegistry& TaskProcessorRegistry::instance()
{
	static TaskProcessorRegistry instance;
	return instance;
}

////////////////////////////////////////////////////////////////////
    
TaskProcessorConstPtr TaskProcessorRegistry::getTaskProcessor(const std::string& url) const
{
	MDW_LOG_DEBUG("looking on task processor ["<< url	<< "]");	
	
	std::map<std::string, TaskProcessorConstPtr >::const_iterator it;
	it = _processors.find(url);
	if (it == _processors.end())
	{
		MDW_LOG_DEBUG("TaskProcessor not found ["<< url	<< "]");
		return TaskProcessorConstPtr((TaskProcessor*)NULL); 
	}	
	
	MDW_LOG_DEBUG("TaskProcessor found ["<< url	<< "]");
	return it->second;
}

////////////////////////////////////////////////////////////////////

void TaskProcessorRegistry::registerTaskProcessor(const std::string& url, 
												  TaskProcessorConstPtr processor)
{

	std::map<std::string, TaskProcessorConstPtr >::iterator it;
	it = _processors.find(url);
	if (it != _processors.end())
	{
		// Warning: overriding existing service
	}
	_processors[url] = processor;
	
	MDW_LOG_INFO("TaskProcessor registration ["<< url << "] " );
}

}
}

