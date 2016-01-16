#include "FrontEnd.hpp"
#include "BackendConfiguration.hpp"

#include "Server.hpp"

#include <iostream>
#include <string>
#include <list>

 #include <unistd.h>
 #include <pthread.h>

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

#define WTF_FRONTEND_BACKEND_NAME "FrontEnd"

const char* WTF::ProcessTypeConfig<WTF::E_FrontEnd>::Filename = "init_fe.json";

namespace WTF
{

	//////////////////////////////////////////////////////////////////////

	int FrontEnd::watchdog()
	{
		sleep(1);
		return 0;
	}

	////////////////////////////////////////////////////////////

	FrontEnd::FrontEnd()
		: TypedProcess<WTF::E_FrontEnd>(WTF_FRONTEND_BACKEND_NAME)
	{
		
	}

	////////////////////////////////////////////////////////////

	void FrontEnd::initialize()
	{
		TypedProcess::initialize();
		WTF_LOG_CONTEXT("FrontEnd: configuration loaded");
	}

	////////////////////////////////////////////////////////////

	int FrontEnd::activate()
	{
		WTF_LOG_INFO("FE activation");
		
		return TypedProcess::activate();
	}

	////////////////////////////////////////////////////////////

	int FrontEnd::deactivate() 	
	{ 		
		WTF_LOG_INFO("FE exiting");
		
		// deactivate the main process
		return TypedProcess<E_FrontEnd>::deactivate();
	}
	
	
	////////////////////////////////////////////////////////////

	int FrontEnd::waitForCompletion() 	
	{ 		
		WTF_LOG_INFO("FE exiting");
		
		// deactivate the main process
		return TypedProcess<E_FrontEnd>::waitForCompletion();
	}
}
