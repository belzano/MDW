#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

namespace uhf {
namespace component {

    //class RunnerImpl;

    /////////////////////////////////////////////////////////////////////

    class Runner: public uhf::IComponent, public IActivable
    {
    public:
		Runner();
		virtual ~Runner();

		virtual void onActivate();
		virtual void onPassivate();

		//private:
		//RunnerImpl* m_impl;
    };

    typedef std::shared_ptr<Runner> RunnerPtr;
	
}
}
