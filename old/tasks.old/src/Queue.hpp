#pragma once

#include <string>
#include <list>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

#include "wtf/toolbox/Types.hpp"

#include "wtf/tasks/Task.hpp"

typedef std::string QueueName;

namespace WTF {
namespace tasks {	
	
	class Queue
	{
	public:
		void enqueue(TaskPtr);
		TaskPtr dequeue();
		TaskPtr tryDequeue();
		
	private:
		std::list<TaskPtr> m_tasks;
		boost::mutex m_mutex;
		boost::condition_variable m_condition;
		U64 m_count;
	};
	
	typedef std::shared_ptr<Queue> QueuePtr;
}
}
