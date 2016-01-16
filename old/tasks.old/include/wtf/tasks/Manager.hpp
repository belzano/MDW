#pragma once

#include <string>
#include "wtf/tasks/Task.hpp"

namespace  WTF {	
namespace tasks {

	/////////////////////////////////////////////////////////////////////
		
	class Manager
	{
		public:		
			
			// Singleton
			static Manager* getInstance();
			
			// public interface
			void insertTask(const std::string& queueName, TaskPtr task);
			//void createDedicatedConsumer(const std::string& queueName);

		private:
			Manager();
			Manager(const Manager&);

			static Manager* m_instance;
	};
}
}
