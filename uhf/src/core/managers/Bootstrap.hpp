#pragma once

#include <memory>
#include "uhf/IComponentRegistry.hpp"

#include "Configuration.hpp"
#include "LibraryManager.hpp"

using uhf::core::configuration::BootstrapPtr;
using uhf::core::configuration::ComponentInstancePtr;

namespace uhf {
namespace manager {
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap
	{
	public:
		bool doBootstrap(const std::string& bootstrapFile, uhf::IComponentRegistryPtr registry);
		
	protected:
		BootstrapPtr loadConfiguration();
		bool createComponents(BootstrapPtr,uhf::IComponentRegistryPtr registry);
		bool createComponent(ComponentInstancePtr, uhf::IComponentRegistryPtr registry);
		void getUnregisteredTypes(toolbox::ptree::Node& bootstrapConfig, std::set<std::string>& unkownDynTypes);
		void tryMissingLibLoading(std::set<std::string>& unkownDynTypes);
  
	private:
		std::string _bootstrapFile;
		uhf::core::LibraryManager m_libraryManager;
	};
}
}
