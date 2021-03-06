#include "Bootstrap.hpp"
#include "LibraryManager.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/ptree/Helper.hpp"

#include "uhf/IComponentRegistry.hpp"
#include "uhf/core/ComponentFactory.hpp"
#include "uhf/core/ComponentMakerRegistry.hpp"
#include "LibraryManager.hpp"
////////////////////////////////////////////////////////////

namespace uhf {
namespace manager {

    ////////////////////////////////////////////////////////////
    
	bool Bootstrap::doBootstrap(const std::string& bootstrapFile, uhf::IComponentRegistryPtr registry)
	{		
		MDW_LOG_SCOPE_CHRONO("Bootstrap::doBootstrap");
		
		_bootstrapFile = bootstrapFile;
		
		std::list<IObjectPtr> dependencies;
		
		// Step 1: Parse Json config
		BootstrapPtr config = loadConfiguration();
		if (config.get() == nullptr){
			MDW_LOG_ERROR("Cannot load configuration. Exiting.");
			return false;	
		}
		MDW_LOG_DEBUG("Parsed Bootstrap configuration: ");
		
		// Step 2:  Load specified libraries
		MDW_LOG_INFO("Initializing libraries. ("<< config->getLibraries().size() <<" to load)")
		
		uhf::core::LibraryManager libraryManager;
		libraryManager.initialize(config->getLibraries());
		libraryManager.activate();
		MDW_LOG_INFO("libraries initialization: Done.")
		std::list<Library> loadedLibraries = libraryManager.getLoadedLibraries();
		for (auto library : loadedLibraries) {
			dependencies.push_back(std::dynamic_pointer_cast<uhf::IObject>(library));
		}
		
		// Step 3: instanciate components
		if (!createComponents(config, registry, dependencies)){
			MDW_LOG_ERROR("Failed to create or initialize components. Exiting.");
			return false;	
		}		

		MDW_LOG_DEBUG("Component creation complete: " << registry);		
		return true;
	}

    ////////////////////////////////////////////////////////////
    /*     			
		std::shared_ptr<uhf::core::configuration::Bootstrap> m_configuration;

		//std::shared_ptr<ProcessConfiguration> m_processConfig;
     */
    BootstrapPtr Bootstrap::loadConfiguration()
    {
		MDW_LOG_DEBUG("Parsing Bootstrap configuration.")
		toolbox::ptree::Node bootstrapConfigAsJson;
		toolbox::ptree::helper::ReadPtree(_bootstrapFile, bootstrapConfigAsJson);
				
		// Ok now we can load the conf
		BootstrapPtr configuration;
		toolbox::ptree::fromJsonFile(_bootstrapFile, configuration);
		return configuration;
	}
	
	/*
	  		// Get all dynamic type in the config file.
		std::set<std::string> unkownDynTypes;
		getUnregisteredTypes(bootstrapConfigAsJson, unkownDynTypes);
		
		if (!unkownDynTypes.empty())
		{
			for(auto dynType: unkownDynTypes)
			{
				MDW_LOG_ERROR("Unknown required dynamic entity type [" << dynType << "]")
			}
			return false;
		}
	 
	 * */
	
    ////////////////////////////////////////////////////////////
/*
    void Bootstrap::getUnregisteredTypes(toolbox::ptree::Node& bootstrapConfigAsJson, std::set<std::string>& unkownDynTypes)
    {
		// Get all dynamic type in the config file.
		std::set<std::string> dynTypes;
		toolbox::ptree::helper::DistinctTagValues("$type", bootstrapConfigAsJson, dynTypes);
		
		for(auto dynType: dynTypes)
		{
			if (toolbox::entity::Factory::instance().isRegistered(dynType))
			{
				continue;
			}
			if (uhf::core::ComponentMakerRegistry::instance().isRegistered(dynType))
			{
				continue;
			}
			unkownDynTypes.insert(dynType);
		}
		return;
	}
*/
    ////////////////////////////////////////////////////////////
/*
    void Bootstrap::tryMissingLibLoading(std::set<std::string>& unkownDynTypes)
    {
		// Compute libraries required
		std::set<std::string> libraries;
		
		for(auto dynType: unkownDynTypes)
		{
			std::vector<std::string> split = toolbox::split(dynType, ':');
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
*/
    ////////////////////////////////////////////////////////////
  
	bool Bootstrap::createComponents(BootstrapPtr configuration, 
										 uhf::IComponentRegistryPtr registry,
										 std::list<IObjectPtr>& dependencies)
    {
		for (ComponentInstancePtr componentInstanceConfig : configuration->getComponents())
		{
			if (! createComponent(componentInstanceConfig, registry, dependencies))
			{
				MDW_LOG_ERROR("Failed to create component [" << componentInstanceConfig << "]");
				return false;
			}
		}
		return true;
	}
	
    ////////////////////////////////////////////////////////////
  
	bool Bootstrap::createComponent(ComponentInstancePtr componentInstanceConfig, 
									uhf::IComponentRegistryPtr registry,
									std::list<IObjectPtr>& dependencies)
	{
		IComponentPtr componentInstance = uhf::core::ComponentFactory::instance().make(componentInstanceConfig->getTypename());
		if (componentInstance == nullptr) {
			return false;
		}
		
		std::list<uhf::IPropertyPtr> properties;
		for (auto ptreeProp : componentInstanceConfig->getProperties()) 
		{
			properties.push_back(std::dynamic_pointer_cast<uhf::IProperty>(ptreeProp));
		}
		uhf::IComponentConfigurationPtr componentConfig = std::dynamic_pointer_cast<uhf::IComponentConfiguration>(componentInstanceConfig->getConfiguration());
		
		bool initResult = componentInstance->initialize(componentInstance, registry, properties, dependencies, componentConfig);
		return initResult;
	}

}
}
