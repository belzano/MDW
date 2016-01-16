#include "Batch.hpp"

#include <iostream>
#include <string>

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

namespace WTF
{
		
	Batch::Batch(const std::string& name)
		: Backend(name)
		{}
		
	////////////////////////////////////////////////////////////	
		
	int Batch::activate()
	{	
		// Create Traffic handling thread
		
		/*pthread_t  thread;
		if ( 0 != pthread_create(&thread, 0 , trafficHandlerThread, & _port))
		{
			MME_LOG_FATAL("traffic handling thread creation failed");	
			exit(1);
		}
			
		MME_LOG_INFO("traffic handling thread creation OK. Waiting for SIGTERM...");
		pthread_join(thread, 0);
		*/
		return 0;
	}


	////////////////////////////////////////////////////////////	
		
	void Batch::initialize()
	{	
		Backend::initialize();
	}

}
