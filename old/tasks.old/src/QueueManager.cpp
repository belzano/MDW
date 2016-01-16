#include "QueueManager.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"


////////////////////////////////////////////////////////////

namespace WTF {
namespace tasks {	
	
	QueueManager::QueueManager()
	{
		
	}
	
	////////////////////////////////////////////////////////////

	QueueManager::~QueueManager()
	{
		
	}
	
	////////////////////////////////////////////////////////////

	QueuePtr QueueManager::getOrCreate(const QueueName& name)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		
		std::map<QueueName, QueuePtr>::const_iterator findIt = m_queues.find(name);
		if (findIt == m_queues.end())
		{
			findIt = m_queues.insert(
				{  name, std::shared_ptr<Queue>(new Queue()) } 
									).first;		
		}
		return findIt->second;
	}	
		
}
}
