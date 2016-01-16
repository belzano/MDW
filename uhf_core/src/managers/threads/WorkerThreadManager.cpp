#include "WorkerThreadManager.hpp"

#include "WorkerThread.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"


////////////////////////////////////////////////////////////

namespace uhf {
namespace threads {
	
	WorkerThreadManager::WorkerThreadManager()
	{
		
	}
	
	////////////////////////////////////////////////////////////

	void WorkerThreadManager::initialize()
	{
		
	}

	////////////////////////////////////////////////////////////

	void WorkerThreadManager::activate()
	{
		std::list<WorkerThread*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->activate();
		}
	}
	
	////////////////////////////////////////////////////////////
		
	void WorkerThreadManager::deactivate()
	{
		std::list<WorkerThread*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->requestShutdown();
		}
	}
	
	////////////////////////////////////////////////////////////
			
	void WorkerThreadManager::waitForCompletion()
	{
		// TODO check if deactivate() was called before. 
		// All workers should be terminating
		
		std::list<WorkerThread*>::iterator workerIt;
		for(workerIt  = m_workers.begin();
			workerIt != m_workers.end();
			++workerIt)
		{
			(*workerIt)->waitForCompletion();
		}
	}
		
}
}
