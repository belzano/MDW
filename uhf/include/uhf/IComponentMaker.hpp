#pragma once

#include <string>
#include "toolbox/Types.hpp"
#include "toolbox/Typename.hpp"
#include "toolbox/utils/Registry.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/IComponentConfiguration.hpp"

namespace uhf {

    class IComponentMaker
    {
    public:
		// ctor
		IComponentMaker() {}

		//IComponentPtr make(IComponentConfigurationPtr);
		virtual IComponentPtr make() const = 0;
		
		// dtor
		virtual ~IComponentMaker() {}
    };

    typedef std::shared_ptr<IComponentMaker> IComponentMakerPtr;

}
