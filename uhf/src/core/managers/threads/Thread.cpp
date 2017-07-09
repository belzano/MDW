#include "Thread.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <thread>
#include <chrono>
#include <signal.h>


/////////////////////////////////////////////////////////////////////

void* processingThread(void *param)
{
	MDW_LOG_INFO("Thread started OK");
	
	uhf::manager::Thread* theThread = (uhf::manager::Thread*) param;
	theThread->pthreadRun();
	
	MDW_LOG_INFO("Thread exited");
	return 0;
}

namespace uhf {
namespace manager {
	
	/////////////////////////////////////////////////////////////////////

	Thread::Thread(const std::string& name) 
		: _name(name)
	{
		
	}
		
	/////////////////////////////////////////////////////////////////////

	void Thread::pthreadRun() 
	{
		_completed = false;
		
		run();
		
		_completed = true;
		// Notify the manager so he can clean me up ?
	}	
	
	/////////////////////////////////////////////////////////////////////

	void Thread::initialize() 
	{
	
	}

	/////////////////////////////////////////////////////////////////////

	bool Thread::shutdownRequested() const
	{
		return _shutdownRequested;
	}

	/////////////////////////////////////////////////////////////////////

	bool Thread::isCompleted() const
	{
		return _completed;
	}

	/////////////////////////////////////////////////////////////////////

	void Thread::requestShutdown()
	{
		MDW_LOG_INFO("Shutdown requested!");
		_shutdownRequested = true;
	}

	/////////////////////////////////////////////////////////////////////

	bool Thread::OneEyeSleepMs(int time, int checkPeriod)
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
		
	int Thread::activate()
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
		
	int Thread::waitForCompletion()
	{
		pthread_join(_processingThread, 0);
		return 0;
	}

}
}
