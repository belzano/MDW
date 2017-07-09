#include "UpdaterThread.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <thread>
#include <chrono>
#include <signal.h>


namespace uhf {
namespace manager {
	
	/////////////////////////////////////////////////////////////////////

	UpdaterThread::UpdaterThread(const std::string& name,
								uhf::component::IUpdatablePtr iUpdatable) 
		: Thread(name),
		_updatable(iUpdatable)
	{
		
	}
	
	/////////////////////////////////////////////////////////////////////

	void UpdaterThread::run() 
	{
		while(!shutdownRequested())
		{
			_updatable->update();
		}
	}

}
}
