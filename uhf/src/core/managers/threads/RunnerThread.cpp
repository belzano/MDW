#include "RunnerThread.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <thread>
#include <chrono>
#include <signal.h>


namespace uhf {
namespace manager {
	
	/////////////////////////////////////////////////////////////////////

	RunnerThread::RunnerThread(const std::string& name,
								uhf::component::IRunnablePtr iRunnable) 
		: Thread(name),
		_runnable(iRunnable)
	{
		
	}
	
	/////////////////////////////////////////////////////////////////////

	void RunnerThread::run() 
	{
		_runnable->run();
	}

}
}
