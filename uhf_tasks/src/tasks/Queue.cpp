#include "Queue.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <sstream>
#include <vector>
#include <iterator>


namespace uhf {
namespace tasks {	
	
	void Queue::enqueue(TaskPtr item)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		++m_count;
		m_tasks.push_back(item);
		m_condition.notify_one();
	}
	
	///////////////////////////////////////////////////////////////////
	
	TaskPtr Queue::dequeue()
	{	
		boost::mutex::scoped_lock lock(m_mutex);

		do
		{		
			if (m_count != 0)
			{
				TaskPtr item = m_tasks.front();
				m_tasks.pop_front();
				--m_count;
				return item;
			}	
			
			// wait notification before retrying to get an item
			m_condition.wait(lock);			
		}
		while(true);
		
		return nullptr;
	}
		
	///////////////////////////////////////////////////////////////////

	TaskPtr Queue::tryDequeue()
	{		
		boost::mutex::scoped_lock lock(m_mutex);
		if(m_count)
		{
			TaskPtr item = m_tasks.front();
			m_tasks.pop_front();
			--m_count;
			return item;
		}
		
		return nullptr;
	}		
		
}
}
