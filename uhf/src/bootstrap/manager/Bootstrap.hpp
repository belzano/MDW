#pragma once

#include <memory>
#include <list>
#include "uhf/IComponentRegistry.hpp"

#include "Configuration.hpp"


using uhf::bootstrap::configuration::BootstrapPtr;
using uhf::bootstrap::configuration::ComponentInstancePtr;

namespace uhf {
namespace manager {
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap
	{
	public:
		bool doBootstrap(const std::string& bootstrapFile, 
						 uhf::IComponentRegistryPtr registry);
		
	protected:
		BootstrapPtr loadConfiguration();
		
		bool createComponents(BootstrapPtr,
							uhf::IComponentRegistryPtr registry, 
							std::list<IObjectPtr>& depencies);
		
		bool createComponent(ComponentInstancePtr, 
							 uhf::IComponentRegistryPtr registry, 
							 std::list<IObjectPtr>& depencies);
		/*
		void getUnregisteredTypes(toolbox::ptree::Node& bootstrapConfig, 
		                          std::set<std::string>& unkownDynTypes);
		
		void tryMissingLibLoading(std::set<std::string>& unkownDynTypes);
  */
	private:
		std::string _bootstrapFile;
	};
}
}
