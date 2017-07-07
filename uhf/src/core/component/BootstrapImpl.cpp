#include "BootstrapImpl.hpp"
#include "LibraryManager.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/ptree/Helper.hpp"

#include "uhf/IComponentRegistry.hpp"
#include "uhf/core/component/ExecutionContext.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace component {

    ////////////////////////////////////////////////////////////

    void BootstrapImpl::loadComponents(const std::string& configFilename, IComponentRegistryPtr componentRegistry)
    {	
		ExecutionContextPtr executionContext = componentRegistry->getComponentInstance<ExecutionContext>();
		
		
		// 1 - Read the config file 
		loadConfiguration(configFilename);
		
		// Instanciate/Initialize components
		//TODO loop on conf
		//	

    }

    ////////////////////////////////////////////////////////////

    void BootstrapImpl::loadConfiguration(const std::string& configFilename)
    {
		MDW_LOG_DEBUG("Parsing Bootstrap configuration.")
		toolbox::ptree::Node bootstrapConfigAsJson;
		toolbox::ptree::helper::ReadPtree(configFilename, bootstrapConfigAsJson);
		
		// Get all dynamic type in the config file.
		std::set<std::string> dynTypes, unkownDynTypes;
		toolbox::ptree::helper::DistinctTagValues("$type", bootstrapConfigAsJson, dynTypes);
		
		// Check if all types are instanciables. If not, try load lib?
		for(auto dynType: dynTypes)
		{
			if (! toolbox::entity::Factory::instance().isRegistered(dynType))
			{	
				MDW_LOG_INFO("Unknown required dynamic entity type [" << dynType << "]")
				unkownDynTypes.insert(dynType);
			}
		}

		if (!unkownDynTypes.empty())
		{
			// Compute libraries required
			std::set<std::string> libraries;
			
			for(auto dynType: unkownDynTypes)
			{
				std::vector<std::string> split = toolbox::split(dynType, '.');
				split.pop_back();
				std::string libname = "lib";
				for (auto token : split)
					libname += token;
				libname += ".so";					
				libraries.insert(libname);
			}

			//   - Load libraries
			std::list<std::string> libs(libraries.begin(), libraries.end());
			MDW_LOG_INFO("Initializing libraries. ("<< libs.size() <<" to load)")
			m_libraryManager.initialize(libs);
			m_libraryManager.activate();
			MDW_LOG_INFO("libraries initialization: Done.")
		}
		
		// Ok now we can load the conf
		toolbox::ptree::fromJsonFile(configFilename, m_configuration);
		MDW_LOG_DEBUG("Parsed Bootstrap configuration: "<< m_configuration)
	}
		      
}
}
