#pragma once

#include <memory>
#include "uhf/IBroker.hpp"

#include "Configuration.hpp"
#include "LibraryManager.hpp"

namespace uhf {
namespace core {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
	
	class ProcessConfiguration;
		
	class BootstrapImpl
	{
	public:
		void loadComponents(const std::string& configFilename, IBrokerPtr broker);

	protected:
		void loadConfiguration(const std::string& configFilename);
		
	private:
		std::shared_ptr<configuration::Bootstrap> m_configuration;
		LibraryManager	m_libraryManager;
		//std::shared_ptr<ProcessConfiguration> m_processConfig;
	};
}
}
}
