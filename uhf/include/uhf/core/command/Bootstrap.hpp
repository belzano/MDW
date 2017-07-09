#pragma once

#include <memory>
#include "uhf/IComponentRegistry.hpp"


namespace uhf {
namespace command {
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap
	{
	public:
		Bootstrap();
		~Bootstrap();
		bool doBootstrap(const std::string& bootstrapFile, uhf::IComponentRegistryPtr registry);

	};
}
}
