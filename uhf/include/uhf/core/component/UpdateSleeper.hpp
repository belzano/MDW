#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"

#include <chrono>
#include <ctime>

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class UpdateSleeper: public uhf::IComponent, public IUpdatable
    {
    public:
		UpdateSleeper();
		virtual ~UpdateSleeper(){}

		virtual void update() override;
		
	private:
		int _wishedLoopLenght;
		std::chrono::time_point<std::chrono::steady_clock> _lastLoopEndTs;
    };

    typedef std::shared_ptr<UpdateSleeper> UpdateSleeperPtr;
	
}
}
