#include <chrono>
#include <thread>

#include "toolbox/Logger.hpp"

#include "uhf/core/component/Sleeper.hpp"


namespace uhf {
namespace component {

	Sleeper::Sleeper()
	 : _sleepTimeMs(1000)
	{

	}

	/////////////////////////////////////////////////////////////////////

	void Sleeper::update()
	{
		MDW_LOG_INFO("Sleeper is sleeping (update())");
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleepTimeMs));
	}

	/////////////////////////////////////////////////////////////////////

	void Sleeper::run()
	{
		MDW_LOG_INFO("Sleeper is sleeping (run())");
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleepTimeMs));	
	}

}
}


