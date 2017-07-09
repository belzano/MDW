#include <chrono>
#include <thread>

#include "toolbox/Logger.hpp"

#include "uhf/core/component/UpdateSleeper.hpp"


namespace uhf {
namespace component {

	UpdateSleeper::UpdateSleeper()
	 : _wishedLoopLenght(1000) // 1 FPS
	 , _lastLoopEndTs(std::chrono::steady_clock::now())
	{

	}

	/////////////////////////////////////////////////////////////////////

	void UpdateSleeper::update()
	{
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		std::chrono::duration<double> loopDurationInSeconds = now - _lastLoopEndTs;
		int elapsedInMillis = 1000 * loopDurationInSeconds.count();
		int timeToSleepMs = std::max(0, _wishedLoopLenght - elapsedInMillis);
		
		if (timeToSleepMs > 0) {
			
			MDW_LOG_DEBUG("Update loop lenght adjustment: Sleeping for " << timeToSleepMs);
			std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleepMs));
		}

		_lastLoopEndTs = std::chrono::steady_clock::now();
	}

}
}


