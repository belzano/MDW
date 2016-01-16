#include "QueueConsumer.hpp"
#include "Queue.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <string>
#include <pthread.h>


namespace WTF {
namespace tasks {	
	
	QueueConsumer::QueueConsumer(QueuePtr queue)
		: WTF::WorkerThread("QueueConsumer")
		, m_queue(queue)
	{}

	////////////////////////////////////////////////////////////	

	int QueueConsumer::run()
	{
		// Check worker's semaphore
		// Dequeue from the queue
		TaskPtr aTask = m_queue->dequeue();
		
		if (aTask == nullptr)
			return 0;
			
		try
		{
			aTask->run();
		}
		catch (...)
		{
			MDW_LOG_ERROR("Exception while processing task"); // Bla BusMessage->Type()
			return -1;
		}
		
		// It's ok !
		return 0; 
	}
		
	////////////////////////////////////////////////////////////	

}
}
