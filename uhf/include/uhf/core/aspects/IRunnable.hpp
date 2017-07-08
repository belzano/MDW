#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    class RunnerImpl;

    /////////////////////////////////////////////////////////////////////

    class IRunnable: public IComponent
    {
    public:
		IRunnable();
		virtual ~IRunnable();

		virtual void run() = 0;
    };

    typedef std::shared_ptr<IRunnable> IRunnablePtr;
	
}
}
