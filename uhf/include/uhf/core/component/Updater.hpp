#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
//#include "uhf/core/aspects/IRunnable.hpp"
#include "uhf/core/aspects/IActivable.hpp"

namespace uhf {
	
namespace manager {
	class Updater;
}
	
namespace component {

    /////////////////////////////////////////////////////////////////////

    class Updater: public uhf::IComponent, public IUpdatable, public IActivable //public IRunnable
    {
    public:
		Updater();
		virtual ~Updater();

		virtual void update() override;
		virtual void onActivate() override;
		virtual void onPassivate() override;
		
	private:
		uhf::manager::Updater* m_impl;
		void update(std::list<IUpdatablePtr>& updatables);
    };

    typedef std::shared_ptr<Updater> UpdaterPtr;
	
}
}
