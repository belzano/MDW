#include <string>
#include <iostream>
#include "signal.h"

#include <stdio.h>
#include <unistd.h>

#include "toolbox/Logger.hpp"
#include "uhf/core/ComponentFactory.hpp"
#include "uhf/core/component/Bootstrap.hpp"
#include "uhf/core/component/ComponentRegistry.hpp"
#include "uhf/core/component/ExecutionContext.hpp"
#include "uhf/core/component/Runner.hpp"
#include "uhf/logger/component/Console.hpp"
#include "uhf/kvs/component/KeyValueStorage.hpp"

//using namespace uhf::core;
using namespace uhf::component;


RunnerPtr g_runner = nullptr;

/////////////////////////////////////////////////////////////////////

void handle_term(int signo)
{
    std::cout << "Caught signal " << signo << ": Stopping soon." << std::endl;		
    if (g_runner.get() != nullptr)
    {
	g_runner->requestShutdown();
    }
}

////////////////////////////////////////////////////////////

int main (int argc, char * const * argv)
{
	std::string appRootDir = "";
	
	char opt = 0;
	while ((opt = getopt(argc, argv, "r:")) != -1) {
		switch(opt) {
		case 'r':
			appRootDir = optarg;
			MDW_LOG_DEBUG("Application root dir " << appRootDir);
			break;
		case '?':
			/* Case when user enters the command as
			 * $ ./cmd_exe -r
			 */
			if (optopt == 'r') {
				MDW_LOG_INFO("\nMissing mandatory appRootDir option");
			} else {
				MDW_LOG_INFO("\nInvalid option received");
			}
			break;
		}
	}	
	
    ComponentRegistryPtr componentRegistry = ComponentRegistryPtr(new ComponentRegistry());
    
    // Create resources
    g_runner = RunnerPtr(new Runner());
    g_runner->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(g_runner);
     
    kvs::KeyValueStoragePtr shellContext =  uhf::core::ComponentFactory::instance().make<kvs::KeyValueStorage>("uhf::component::kvs::EnvVar");
    shellContext->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(shellContext);
    shellContext->dataSet("UHF_APP_NAME", toolbox::MakeDataPtr("agent"));
    if (!appRootDir.empty()) {
		toolbox::DataPtr appRootDirArg = toolbox::MakeDataPtr(appRootDir);
		shellContext->dataSet("APP_ROOT_DIR", appRootDirArg);
	}

    logger::ConsolePtr logger = uhf::core::ComponentFactory::instance().make<logger::Console>();
    logger->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(logger);
    
    
    BootstrapPtr bootstrap = uhf::core::ComponentFactory::instance().make<Bootstrap>();
    bootstrap->setComponentRegistry(componentRegistry);
    componentRegistry->registerComponent(bootstrap);
    
    std::string appRootDirEnvVar = toolbox::toString(shellContext->dataGet("APP_ROOT_DIR"));
    std::string bootstrapFile = appRootDirEnvVar + "/etc/bootstrap.json";
    MDW_LOG_INFO("Bootstraping components from [" << bootstrapFile <<"]");
    bootstrap->loadComponents(bootstrapFile);

    MDW_LOG_INFO("Hooking SIGTERM");
    signal(SIGTERM, handle_term);
    
    g_runner->run();

    MDW_LOG_INFO("g_runner->run() returned. Exiting." );	
    
    return 0;
}
