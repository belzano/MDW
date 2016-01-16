#pragma once

#include <list>
#include <memory>

#include "wtf/tasks/Task.hpp"
#include "Queue.hpp"


namespace WTF {
namespace tasks {	
	
	class QueueConsumer;
	
	/////////////////////////////////////////////////////////////////////
		
	class QueueHandler 
	{
		public:
			QueueHandler(const QueuePtr& queue, U8 workerCount);
			
			// Asynchronous component interface
			void initialize();
			void activate();
			void deactivate();
			void waitForCompletion();
			
			// public interface
			void insertTask(TaskPtr task);
			
		private:
			QueuePtr 		m_queue;
			U8				m_workerCount;
			std::list<QueueConsumer*> m_workers;	
			
	};
}
}
