#include "ThreadManager.hpp"

#include "Thread.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"


////////////////////////////////////////////////////////////

namespace uhf {
namespace manager {
	
	ThreadManager::ThreadManager()
	{
		
	}
	
	////////////////////////////////////////////////////////////

	void ThreadManager::initialize()
	{
		
	}

	////////////////////////////////////////////////////////////
			
	void ThreadManager::registerThread(std::shared_ptr<Thread> worker)
	{
		m_workers.push_back(worker);
		// TODO start asasp if activated
	}

	////////////////////////////////////////////////////////////

	void ThreadManager::activate()
	{
		std::list<std::shared_ptr<Thread>>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->activate();
		}
	}
	
	////////////////////////////////////////////////////////////
		
	void ThreadManager::deactivate()
	{
		std::list<std::shared_ptr<Thread>>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->requestShutdown();
		}
	}
	
	////////////////////////////////////////////////////////////
			
	void ThreadManager::waitForCompletion()
	{
		// TODO check if deactivate() was called before. 
		// All workers should be terminating
		
		std::list<std::shared_ptr<Thread>>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->waitForCompletion();
		}
	}
		
}
}
