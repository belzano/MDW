#include "BootstrapImpl.hpp"
#include "LibraryManager.hpp"

#include "toolbox/ptree/Helper.hpp"

#include "uhf/IBroker.hpp"
#include "uhf/core/component/ExecutionContext.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace core {
namespace component {

    ////////////////////////////////////////////////////////////

    void BootstrapImpl::loadComponents(const std::string& configFilename, IBrokerPtr broker)
    {	
	ExecutionContextPtr executionContext = broker->getComponentInstance<ExecutionContext>();
	
	// 1 - Parse the config file 
	toolbox::ptree::helper::Bridge(configFilename, m_configuration);
	MDW_LOG_INFO("Parsed Bootstrap configuration.")
	
	// Collect libraries required
	//   - Load libraries
	std::list<std::string> libraries;
	for(auto component: m_configuration->getComponents())
	{
	    MDW_LOG_DEBUG("Component: ")
	    for (auto library: component->m_libraries)
	      libraries.push_back(library);
	}
	MDW_LOG_INFO("Initializing libraries.")
	m_libraryManager.initialize(libraries);
	m_libraryManager.activate();
	MDW_LOG_INFO("libraries initialization: Done.")
	
	// Instanciate/Initialize components
	//TODO loop on conf
	//	

    }

		      
}
}
}