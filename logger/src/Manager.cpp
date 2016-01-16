#include "Manager.hpp"

using namespace logger;

/////////////////////////////////////////////////////////////////////

void* ThreadMain_dequeueStreams(void *param)
{
	std::cout << "Logging thread starting";
	
	logger::Manager* manager = (logger::Manager*) param;
	while(! manager->shutdownRequested())
	{
		// Wait for semaphore (job to do signal)
		manager->wait();
		
		// Proces dequeing
		manager->dequeueStreams();
	}
	
	std::cout << "Logging thread exited";
	return 0;
}

///////////////////////////////////////////////

Manager::Manager()
	: m_shutdownRequested(false)
{

}

///////////////////////////////////////////////

void Manager::activate()
{
	m_shutdownRequested = false;
	
	// Create processing thread
	if ( 0 != pthread_create(& m_processor, 0 , ThreadMain_dequeueStreams, this))
	{
		std::cerr << "Log dequeueing thread creation failed";
		exit(1);
	}
	
	std::cout << "Log dequeueing thread creation OK";
}

///////////////////////////////////////////////

void Manager::deactivate()
{
	m_shutdownRequested = true;
	
	// Push an event to the semaphore to force thread exit
	signal();
}

////////////////////////////////////////////////////////////	
	
void Manager::waitFordeactivation()
{
	deactivate();
	
	pthread_join(m_processor, 0);
}

///////////////////////////////////////////////

void Manager::registration(Stream* stream)
{
	// wait for lock
	boost::mutex::scoped_lock scoped_lock(m_lock);
	
	m_streams.insert(stream);	
}

///////////////////////////////////////////////

void Manager::deregistration(Stream* stream)
{
	// wait for lock	
	boost::mutex::scoped_lock scoped_lock(m_lock);

	m_streams.erase(stream);
}

///////////////////////////////////////////////

void Manager::dequeueStreams()
{
	// wait for lock	
	boost::mutex::scoped_lock scoped_lock(m_lock);
	
	// Loop on input stream buffers and push to out streams
	
	// TODO
	// TODO
	
}

///////////////////////////////////////////////		
