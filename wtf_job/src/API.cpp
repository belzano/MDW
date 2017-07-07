
#include "job/API.hpp"
#include "job/JobManager.hpp"

#include "toolbox/ExecutionContext.hpp"
#include "toolbox/Logger.hpp"

#include <iostream>
#include <functional>
#include <string>
#include <ctime>

////////////////////////////////////////////////////////////////////

namespace job
{
 
JobManager init()
{
	std::string messageQueueName 		= toolbox::ExecutionContext::instance().getMessageQueueName();
	std::string queueItemsStoragePath	= toolbox::ExecutionContext::instance().getDirData();
	
	MDW_LOG_INFO("Job manager initiated with queue_name [" << messageQueueName 
					<< "] and storage on [" << queueItemsStoragePath << "]");
	
	return JobManager(messageQueueName, queueItemsStoragePath);
}
					

}
