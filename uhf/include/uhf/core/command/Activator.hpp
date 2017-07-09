#pragma once

#include <memory>
#include "uhf/IComponentRegistry.hpp"


namespace uhf {
namespace command {
		
	/////////////////////////////////////////////////////////////////////
		
	class Activator
	{
	public:
		Activator();
		~Activator();
		bool activateComponents(uhf::IComponentRegistryPtr registry);

	};
}
}
