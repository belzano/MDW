#pragma once

#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    

namespace logger
{
	class Stream;

	class Manager
	{
		public:
			Manager();
			
			void activate();
			void deactivate();
			void waitFordeactivation();

			void registration(Stream* stream);
			void deregistration(Stream* stream);
			
			bool shutdownRequested() {return m_shutdownRequested;}
			void dequeueStreams();
			
		private:
			// Locked list. 
			std::set<Stream*> 	m_streams;
			boost::mutex 		m_lock;
			
			// Processor
			pthread_t  			m_processor;
			bool 				m_shutdownRequested;

						
		public:				
			void signal()
			{
				_logToDequeue.notify_one(); 
			}

			void wait()
			{
				boost::unique_lock<boost::mutex> lock(_logToDequeue_mutex);
				_logToDequeue.wait(lock);
			}
			
		private: 
			boost::mutex 			  	_logToDequeue_mutex;
			boost::condition_variable 	_logToDequeue;
	};

}
