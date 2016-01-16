#include "QueueHandler.hpp"
#include "QueueConsumer.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"


namespace WTF {
namespace tasks {	
	
	QueueHandler::QueueHandler(const QueuePtr& queue, U8 workerCount)
		: m_queue(queue)
		, m_workerCount(workerCount)
	{
		
	}

	////////////////////////////////////////////////////////////

	void QueueHandler::initialize()
	{
		for(int i = 0; i < m_workerCount; ++i)	
		{
			m_workers.push_back(new QueueConsumer(m_queue));
		}
	}
	
	////////////////////////////////////////////////////////////

	void QueueHandler::activate()
	{
		std::list<QueueConsumer*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->activate();
		}
	}
	
	////////////////////////////////////////////////////////////
		
	void QueueHandler::deactivate()
	{
		std::list<QueueConsumer*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->requestShutdown();
		}
	}
	
	////////////////////////////////////////////////////////////
			
	void QueueHandler::waitForCompletion()
	{
		// TODO check if deactivate() was called before. 
		// All workers should be terminating
		
		std::list<QueueConsumer*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->waitForCompletion();
		}
	}
		
		
}
}
