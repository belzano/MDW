#pragma once

#include <string>
#include "uhf/task/Task.hpp"

namespace uhf {	
namespace tasks {

	/////////////////////////////////////////////////////////////////////
		
	class TaskManager
	{
		public:		
			
			// Singleton
			static TaskManager* getInstance();
			
			// public interface
			void insertTask(const std::string& queueName, TaskPtr task);
			//void createDedicatedConsumer(const std::string& queueName);

		private:
			TaskManager();
			TaskManager(const TaskManager&);

			static TaskManager* m_instance;
	};
}
}
