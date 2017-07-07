#pragma once

#include <memory>
#include "uhf/IComponentRegistry.hpp"

#include "Configuration.hpp"
#include "LibraryManager.hpp"

namespace uhf {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
	
	class ProcessConfiguration;
		
	class BootstrapImpl
	{
	public:
		void loadComponents(const std::string& configFilename, IComponentRegistryPtr componentRegistry);

	protected:
		void loadConfiguration(const std::string& configFilename);
		
	private:
		std::shared_ptr<uhf::core::configuration::Bootstrap> m_configuration;
		uhf::core::LibraryManager m_libraryManager;
		//std::shared_ptr<ProcessConfiguration> m_processConfig;
	};
}
}
