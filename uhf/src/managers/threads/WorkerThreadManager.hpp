#pragma once

#include <list>
#include <memory>

namespace uhf {
namespace threads {
		
	class WorkerThread;
	
	/////////////////////////////////////////////////////////////////////
		
	class WorkerThreadManager
	{
		public:
			WorkerThreadManager();
			
			void initialize();
			
			void activate();
			void deactivate();
			
			void waitForCompletion();
			
			void registerWorker(WorkerThread*){}

		private:
			std::list<WorkerThread*> m_workers;		
	};
}
}
