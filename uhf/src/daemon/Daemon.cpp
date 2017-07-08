#include <chrono>
#include <thread>

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"


#include "uhf/job/API.hpp"
//#include "mme/Query.hpp"



/////////////////////////////////////////////////////////////////////

void mainLoop (job::Job& iMessage)
{
	MDW_LOG_DEBUG("Received a message to process" << iMessage.getKey());
	
	MDW_LOG_CONTEXT(iMessage.getKey());
	
	// Convert to query
	//API::Query theQuery(iMessage.getStorage());
	
	// process 
	//theQuery.process();
	
	MDW_LOG_DEBUG("Processing completed OK! " << iMessage.getKey());
}

/////////////////////////////////////////////////////////////////////

int main (int /*argc*/, char ** /*char* argv[]*/)
{
	MDW_LOG_INFO("Daemon process startup");
	
	// Get the jobmanager
	job::JobManager theJobMgr = job::init();
	
	uint missCount = 0;
	while (true)	
	{
		job::JobPtr aJob = theJobMgr.tryDequeue();
		if (aJob.get() != nullptr)
		{
			mainLoop(*aJob.get());
			missCount = 0;
			continue;
		}
		
		// Increment
		missCount++;
		if (missCount > 5) missCount = 5;
		
		uint sleepTime = missCount * missCount * 100;
		MDW_LOG_INFO("Nothing to do: sleeping for " << sleepTime << " ms" );

		std::chrono::milliseconds duration( sleepTime );
		std::this_thread::sleep_for(duration);
	}
}


