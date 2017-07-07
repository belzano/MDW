#include "WorkerThread.hpp"

#include "toolbox/ExecutionContext.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <thread>
#include <chrono>
#include <signal.h>


/////////////////////////////////////////////////////////////////////

void* processingThread(void *param)
{
	MDW_LOG_INFO("WorkerThread started OK");
	
	uhf::threads::WorkerThread* callback = (uhf::threads::WorkerThread*) param;
	while(! callback->shutdownRequested())
	{
		callback->run();
	}
	
	MDW_LOG_INFO("WorkerThread thread exited");
	return 0;
}

namespace uhf{
namespace threads{
	
	/////////////////////////////////////////////////////////////////////

	WorkerThread::WorkerThread(const std::string& name) 
		: _name(name)
	{
		
	}
	
	/////////////////////////////////////////////////////////////////////

	void WorkerThread::initialize() 
	{
	
	}

	/////////////////////////////////////////////////////////////////////

	bool WorkerThread::shutdownRequested() const
	{
		return _shutdownRequested;
	}

	/////////////////////////////////////////////////////////////////////

	void WorkerThread::requestShutdown()
	{
		MDW_LOG_INFO("Shutdown requested!");
		_shutdownRequested = true;
	}

	/////////////////////////////////////////////////////////////////////

	bool WorkerThread::OneEyeSleepMs(int time, int checkPeriod)
	{
		for(int timeToSleep = std::min(time, checkPeriod);
			timeToSleep > 0;
			timeToSleep = std::min(time, checkPeriod))
		{
			if(shutdownRequested())
				return true;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));
			
			time -= timeToSleep;
		}
		
		return false;	
	}

	////////////////////////////////////////////////////////////	
		
	int WorkerThread::activate()
	{	
		// Create processing thread
		if ( 0 != pthread_create(&_processingThread, 0 , processingThread, this))
		{
			MDW_LOG_FATAL("Processing thread creation failed");	
			exit(1);
		}
		MDW_LOG_INFO("Processing threads creation OK. Waiting for completion...");
		return 0;
	}
	
	////////////////////////////////////////////////////////////	
		
	int WorkerThread::waitForCompletion()
	{		
		pthread_join(_processingThread, 0);
		return 0;
	}

}
}
