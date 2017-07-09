#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/core/aspects/IRunnable.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class Sleeper: public uhf::IComponent, public IUpdatable, public IRunnable
    {
    public:
		Sleeper();
		virtual ~Sleeper(){}

		virtual void update() override;
		virtual void run() override;
		
	private:
		int _sleepTimeMs;
    };

    typedef std::shared_ptr<Sleeper> SleeperPtr;
	
}
}
