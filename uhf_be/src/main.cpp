#include <string>
#include <iostream>
#include "signal.h"

#include <stdio.h>
#include <unistd.h>

#include "toolbox/Logger.hpp"
#include "uhf/core/ComponentFactory.hpp"
#include "uhf/core/component/Bootstrap.hpp"
#include "uhf/core/component/ComponentRegistry.hpp"
#include "uhf/core/property/Activable.hpp"

#include "uhf/core/component/Runner.hpp"
#include "uhf/core/component/ILogger.hpp"
#include "uhf/kvs/component/KeyValueStorage.hpp"


using namespace uhf::component;
using namespace uhf;
using namespace uhf::core;
using namespace uhf::kvs;

//uhf::component::RunnerPtr g_runner = nullptr;

/////////////////////////////////////////////////////////////////////

void handle_term(int signo)
{
    std::cout << "Caught signal " << signo << ": Stopping soon." << std::endl;		
/*    if (g_runner.get() != nullptr)
    {
		g_runner->requestShutdown();
    }*/
}

////////////////////////////////////////////////////////////

int main (int argc, char * const * argv)
{
	std::string bootstrapFile = "";
	char opt = 0;
	while ((opt = getopt(argc, argv, "b:")) != -1) {
		switch(opt) {
		case 'b':
			bootstrapFile = optarg;
			MDW_LOG_DEBUG("Bootstrap file [" << bootstrapFile << "]");
			break;
		case '?':
			/* Case when user enters the command as
			 * $ ./cmd_exe -r
			 */
			if (optopt == 'b') {
				MDW_LOG_INFO("\nMissing mandatory bootstrap file option -b");
			} else {
				MDW_LOG_INFO("\nInvalid option received");
			}
			break;
		}
	}	
	
    ComponentRegistryPtr componentRegistry = ComponentRegistryPtr(new ComponentRegistry());
    std::list<uhf::IPropertyPtr> registryProperties;
    registryProperties.push_back(uhf::IPropertyPtr(new uhf::core::property::Activable()));
    bool initResult = componentRegistry->initialize(std::dynamic_pointer_cast<uhf::IComponent>(componentRegistry),
													componentRegistry,
													registryProperties, 
													uhf::IComponentConfigurationPtr(nullptr));
	if (!initResult){
		MDW_LOG_ERROR("Failed to initialize ComponentRegistry. Exiting.");
		exit(-1);
	}
	
    // Create resources
    //g_runner = RunnerPtr(new Runner());
    //g_runner->setComponentRegistry(componentRegistry);
    //componentRegistry->registerComponent(g_runner);
     
    /*
    uhf::kvs::component::KeyValueStoragePtr shellContext =  uhf::core::ComponentFactory::instance().make<uhf::kvs::component::KeyValueStorage>("uhf::kvs::component::EnvVar");
    shellContext->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(shellContext);
    shellContext->dataSet("UHF_APP_NAME", toolbox::MakeDataPtr("agent"));
    if (!appRootDir.empty()) {
		toolbox::DataPtr appRootDirArg = toolbox::MakeDataPtr(appRootDir);
		shellContext->dataSet("APP_ROOT_DIR", appRootDirArg);
	}

    uhf::component::ILoggerPtr logger = uhf::core::ComponentFactory::instance().make<uhf::component::ILogger>("uhf::logger::component::Console");
    logger->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(logger);
    */
    
    BootstrapPtr bootstrap = uhf::core::ComponentFactory::instance().make<Bootstrap>();
    bootstrap->initialize(bootstrap,
						componentRegistry,
						std::list<uhf::IPropertyPtr>(), 
						uhf::IComponentConfigurationPtr(nullptr));
    
    MDW_LOG_INFO("Bootstraping components from [" << bootstrapFile << "]");
    bootstrap->setBootstrapFile(bootstrapFile);
	bootstrap->run();
	
    MDW_LOG_INFO("Hooking SIGTERM");
    signal(SIGTERM, handle_term);
    
    //g_runner->run();

    MDW_LOG_INFO("g_runner->run() returned. Exiting." );	
    
    return 0;
}
