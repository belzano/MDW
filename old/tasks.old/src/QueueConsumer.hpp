#pragma once

#include "wtf/api/WorkerThread.hpp"
#include "Queue.hpp"

namespace WTF {
namespace tasks {
	
	/////////////////////////////////////////////////////////////////////
		
	class QueueConsumer : public WTF::WorkerThread
	{
		public:
		
			QueueConsumer(QueuePtr);
		
			virtual int run() override;
			
		private:
			QueuePtr m_queue;
	};

}
}
