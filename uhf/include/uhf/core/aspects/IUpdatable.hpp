#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class IUpdatable
    {
    public:
		IUpdatable();
		virtual ~IUpdatable();

		virtual void update() = 0;
    };

    typedef std::shared_ptr<IUpdatable> IUpdatablePtr;
	
}
}
