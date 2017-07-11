#include "uhf/core/component/Process.hpp"
#include "uhf/core/component/ComponentRegistry.hpp"
#include "uhf/core/aspects/IActivable.hpp"
#include "uhf/core/property/Activable.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <thread>
#include <chrono>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


namespace uhf {
namespace component {
	
	/////////////////////////////////////////////////////////////////////

	Process::Process()
	 : _name("Anonymous")	
	 , _shutdownRequested(false)
	 , _interactive(false)
	{
	}
	
	/////////////////////////////////////////////////////////////////////

	Process::~Process()
	{
		
	}
	
	/////////////////////////////////////////////////////////////////////
	
	int Process::handle_signal(int signo)
	{
		MDW_LOG_INFO("Intercepted signal " << signo << ".");		

		if (signo == SIGSEGV) {
		  void *array[10];
		  size_t size;

		  // get void*'s for all entries on the stack
		  size = backtrace(array, 10);

		  // print out all the frames to stderr
		  fprintf(stderr, "Error: signal %d:\n", signo);
		  backtrace_symbols_fd(array, size, STDERR_FILENO);
		  exit(1);
		}
		
		if (!_interactive) { 
			MDW_LOG_INFO("Process is not in interactive mode. Interpreting signal " << signo << " as a shutdown request.");	
			requestShutdown();
		}
		else {			
			char  c;
			MDW_LOG_INFO("OUCH, did you hit Ctrl-C? "<< std::endl << "Do you really want to quit? [y/n]");
			c = getchar();
			if (c == 'y' || c == 'Y')
			  requestShutdown();

			getchar(); // Get new line character
		}
		return 0;
	}
	
	/////////////////////////////////////////////////////////////////////

	bool Process::shutdownRequested() const
	{
		return _shutdownRequested;
	}

	/////////////////////////////////////////////////////////////////////

	void Process::requestShutdown()
	{
		MDW_LOG_INFO("Shutdown requested!");
		_shutdownRequested = true;
	}

	/////////////////////////////////////////////////////////////////////

	bool Process::OneEyeSleepMs(int time, int checkPeriod)
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
		
	void Process::onActivate()
	{	

	}

	////////////////////////////////////////////////////////////	
		
	void Process::onPassivate()
	{		
		
	}
	
	////////////////////////////////////////////////////////////	
		
	int Process::watchdog()
	{		
		return 0;
	}
	
	////////////////////////////////////////////////////////////	
		
	int Process::waitForCompletion()
	{		
		return 0;
	}

	////////////////////////////////////////////////////////////	
		
	int Process::run()
	{			
		while (! shutdownRequested())
		{
			watchdog();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		
		// TODO shoudl we ask for deactivation of other components?
		//MDW_LOG_INFO("Deactivating managers");
		//passivate();
		
		MDW_LOG_INFO("Waiting for managers deactivation completion");
		waitForCompletion();		
		
		return 0;
	}
	
}	
}
