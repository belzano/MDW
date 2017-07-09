#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/core/aspects/IRunnable.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class Updater: public uhf::IComponent, public IUpdatable, public IRunnable
    {
    public:
		Updater() {}
		virtual ~Updater(){}

		virtual void update() override;
		virtual void run() override;
		
	private:
		void update(std::list<IUpdatablePtr>& updatables);
    };

    typedef std::shared_ptr<Updater> UpdaterPtr;
	
}
}
