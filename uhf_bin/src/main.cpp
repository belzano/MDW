#include <string>
#include <iostream>
#include "signal.h"

#include "uhf/core/component/Bootstrap.hpp"
#include "uhf/core/component/Broker.hpp"
#include "uhf/core/component/ExecutionContext.hpp"
#include "uhf/core/component/Runner.hpp"
#include "uhf/core/component/LoggerConsole.hpp"

//using namespace uhf::core;
using namespace uhf::core::component;


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

int main (int /*argc*/, char * const * /*argv*/)
{
    BrokerPtr broker = BrokerPtr(new Broker());
    
    // Create resources
    g_runner = RunnerPtr(new Runner());
    g_runner->setBroker(broker);
    broker->registerComponent(g_runner);
     
    ExecutionContextPtr executionContext = ExecutionContextPtr(new ExecutionContext());
    executionContext->setBroker(broker);
    broker->registerComponent(executionContext);
    executionContext->setApplicationName("agent");

    LoggerConsolePtr logger = LoggerConsolePtr(new LoggerConsole());
    logger->setBroker(broker);
    broker->registerComponent(logger);
    
    BootstrapPtr bootstrap = BootstrapPtr(new Bootstrap());
    bootstrap->setBroker(broker);
    broker->registerComponent(bootstrap);
    //bootstrap->loadComponents(executionContext->getConfigurationDir() + "/conf.json");
    bootstrap->loadComponents("/home/belzano/github/MDW/etc/bootstrap.json");
    
    std::cout << "Hooking SIGTERM" << std::endl;
    signal(SIGTERM, handle_term);
    
    g_runner->run();

    std::cout << "g_runner->run() returned. Exiting." << std::endl;	
    
    return 0;
}
