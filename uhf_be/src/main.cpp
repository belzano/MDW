#include <string>
#include <iostream>
#include "signal.h"

#include <stdio.h>
#include <unistd.h>

#include "toolbox/Logger.hpp"

#include "uhf/core/command/Activator.hpp"

#include "uhf/core/component/Process.hpp"
#include "uhf/core/component/ComponentRegistry.hpp"

#include "uhf/bootstrap/command/Bootstrap.hpp"

using namespace uhf;

uhf::component::ProcessPtr g_process = nullptr;

/////////////////////////////////////////////////////////////////////

void handle_term(int signo)
{
	MDW_LOG_INFO("Intercepted signal " << signo << ".");		
    if (g_process != nullptr)
    {
		// Deactivate signal 
		signal(signo, SIG_IGN);
		
		g_process->handle_signal(signo);
		
		//reactivate
		signal(signo, handle_term);
    }
}

////////////////////////////////////////////////////////////

int parse_args(int argc, char * const * argv, std::string& bootstrapFile)
{
	char opt = 0;
	while ((opt = getopt(argc, argv, "b:")) != -1) {
		switch(opt) {
		case 'b':
			bootstrapFile = optarg;
			MDW_LOG_DEBUG("Bootstrap file [" << bootstrapFile << "]");
			break;
		case '?':
			if (optopt == 'b') {
				MDW_LOG_INFO("Missing mandatory bootstrap file option -b");
			} else {
				MDW_LOG_INFO("Invalid option received");
			}
			return -1;
			break;
		}
	}
	return 0;	
}

////////////////////////////////////////////////////////////

int main (int argc, char * const * argv)
{
	std::string bootstrapFile = "";
	parse_args(argc, argv, bootstrapFile);


	component::ComponentRegistryPtr componentRegistry(new component::ComponentRegistry());

    g_process = component::ProcessPtr(new component::Process());  
    bool processInit = g_process->initialize(g_process,
										  componentRegistry,
										  std::list<uhf::IPropertyPtr>(), 
										  uhf::IComponentConfigurationPtr());
	if (!processInit) {
		MDW_LOG_ERROR("Failed to initialize component::Process. Exiting.");
		return -1;
	}
	MDW_LOG_INFO("Hooking SIGTERM");
    signal(SIGTERM, handle_term);
    signal(SIGINT, handle_term);
	

    MDW_LOG_INFO("Bootstraping components from [" << bootstrapFile << "]");
    if (! uhf::command::Bootstrap().doBootstrap(bootstrapFile, componentRegistry))
    {
		MDW_LOG_INFO("Bootstraping failed. Exiting");
		return -1;
	}

    MDW_LOG_INFO("Activating components");
    uhf::command::Activator().activateComponents(componentRegistry);
    
    MDW_LOG_INFO("Process: Run");
	g_process->run();

    MDW_LOG_DEBUG("g_process->run() returned. Exiting." );	
    
    return 0;
}
