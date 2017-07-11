#pragma once

#include "ThreadManager.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"

namespace uhf {
namespace manager {

    /////////////////////////////////////////////////////////////////////

    class Updater
    {
    public:
		Updater() {}
		virtual ~Updater(){}
		
		void start(uhf::component::IUpdatablePtr iUpdatable);
		void stop();
		
	private:
		ThreadManager _manager;
    };

    typedef std::shared_ptr<Updater> UpdaterPtr;
	
}
}
