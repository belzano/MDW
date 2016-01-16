#include "Agent.hpp"
#include "BackendConfiguration.hpp"

#include "Server.hpp"

#include <iostream>
#include <string>
#include <list>

 #include <unistd.h>
 #include <pthread.h>

#include "wtf/toolbox/ExecutionContext.hpp"
#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

#define WTF_MASTER_BACKEND_NAME "Agent"

const char* WTF::ProcessTypeConfig<WTF::E_Agent>::Filename = "init_agent.json";


namespace WTF
{

	//////////////////////////////////////////////////////////////////////

	int Agent::watchdog()
	{
		checkProcesses();
		sleep(1);
		return 0;
	}

	//////////////////////////////////////////////////////////////////////
		
	void Agent::checkProcesses()
	{
		configuration::ApplicationServerNodeStatus& status = getAsNodeStatus();
		
		if (status.getProcesses().empty()) 
		{
			WTF_LOG_INFO("Check backends: Nothing to check, no BE registered!");
			return;
		}
		
		// Check and instanciate required workers	
		std::list<configuration::ProcessDescription>::iterator anIt;
		for(anIt  = status.getProcesses().begin();
			anIt != status.getProcesses().end();
			++anIt)
		{
			checkProcess( *anIt);
		}
	}

	/////////////////////////////////////////////////////////////////////

	void Agent::checkProcess(configuration::ProcessDescription& process)
	{
		if (process.getRuntimeInfo().getCurrentState() == WTF::configuration::E_Activated)
			return;

		createProcess(process);
	}

	/////////////////////////////////////////////////////////////////////

	void Agent::createProcess(configuration::ProcessDescription& process)
	{
		WTF_LOG_INFO("Creating process");
		pid_t forkRes = fork();
		if (forkRes)
		{
			// fork successful. Store the child PID on status
			WTF_LOG_INFO("Created process with PID "<< forkRes);
			process.getRuntimeInfo().setProcessId(forkRes);
			process.getRuntimeInfo().setCurrentState(WTF::configuration::E_Activated);
			return;
		}
		
		// initialize the new BE
		std::shared_ptr<Process> be;
		switch(process.getProcessType())
		{
			case ProcessType::E_BE_Server:
				be = std::shared_ptr<Process>( new Server(process.getName(), 8080 ) );
			break;
			default:
				WTF_LOG_FATAL("Cannot instanciate such BE type. Exiting.");
				exit(1);
			break;
		};
		be->run();
		
		exit(0);
	}

	//////////////////////////////////////////////////////////////////////

	void* commandsThread(void *param)
	{    
		WTF_LOG_INFO("Commands thread started OK");
		
		Agent* theBeInstance = (Agent*) param;
		while(! theBeInstance->shutdownRequested())
		{
			sleep(1);
		}
		
		WTF_LOG_INFO("Command thread exited");
		return 0;
	}

	//////////////////////////////////////////////////////////////////////

	void* monitoringThread(void *param)
	{    
		WTF_LOG_INFO("Monitoring thread started OK");
		
		Agent* theBeInstance = (Agent*) param;
		while(! theBeInstance->shutdownRequested())
		{
			MDW_LOG_DEBUG("Monitoring BE...");
			sleep(1);
		}
		
		WTF_LOG_INFO("Monitoring thread exited");
		return 0;
	}

	////////////////////////////////////////////////////////////

	Agent::Agent()
		: TypedProcess<WTF::E_Agent>(WTF_MASTER_BACKEND_NAME)
	{
		
	}

	////////////////////////////////////////////////////////////

	void Agent::initialize()
	{
		WTF_LOG_INFO("Agent agent: configuration loading");
		TypedProcess::initialize();
		WTF_LOG_INFO("Agent agent: configuration loaded");
		
		// Load the Application status database
		WTF_LOG_INFO("Agent agent: reading app node db");
		getAsNodeStatus().fromJson(toolbox::ExecutionContext::instance().getDirCfg() + "ApplicationNode/status_db.json");
		WTF_LOG_INFO("Agent agent: read app node db");
		
		WTF_LOG_INFO("Agent agent: Declared processes in application node: " << getAsNodeStatus().getProcesses().size());
	}

	////////////////////////////////////////////////////////////

	int Agent::activate()
	{
		WTF_LOG_INFO("MAG activation");
		
		// Create monitoring thread
		if ( 0 != pthread_create(&_mon_thread, 0 , monitoringThread, this))
		{
			WTF_LOG_FATAL("MAG Monitoring thread creation failed");	
			exit(1);
		}

		// Create commands thread
		if ( 0 != pthread_create(&_cmd_thread, 0 , commandsThread, this))
		{
			WTF_LOG_FATAL("MAG Command thread creation failed");	
			exit(1);
		}
		
		TypedProcess::activate();
		
		WTF_LOG_INFO("MAG activated");
		
		return 0;
	}

	////////////////////////////////////////////////////////////

	int Agent::waitForCompletion() 	
	{ 		
		// deactivate my threads
		pthread_join(_mon_thread, 0);    
		pthread_join(_cmd_thread, 0);    

		// deactivate the main process
		TypedProcess::waitForCompletion();
		
		WTF_LOG_INFO("MAG exiting");
		return 0;
	}
	
	////////////////////////////////////////////////////////////
	
	int Agent::deactivate() 	
	{ 		
		TypedProcess::deactivate();
		return 0;
	}
}
