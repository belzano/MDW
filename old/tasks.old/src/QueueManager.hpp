#pragma once

#include <map>
#include <memory>

#include <boost/thread/mutex.hpp>
#include "Queue.hpp"

namespace WTF {
namespace tasks {	
	
	typedef std::shared_ptr<Queue> QueuePtr;
	typedef std::string QueueName;
	
	/////////////////////////////////////////////////////////////////////
		
	class QueueManager 
	{
		public:
			QueueManager();
			virtual ~QueueManager();
			
			QueuePtr getOrCreate(const QueueName& name);
			
		private:
			std::map<QueueName, QueuePtr> 	m_queues;
			boost::mutex 					m_mutex;
	};
	
}
}
