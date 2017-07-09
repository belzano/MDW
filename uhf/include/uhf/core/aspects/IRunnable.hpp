#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class IRunnable
    {
    public:
		IRunnable();
		virtual ~IRunnable();

		virtual void run() = 0;
    };

    typedef std::shared_ptr<IRunnable> IRunnablePtr;
	
}
}
