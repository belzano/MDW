#pragma once

#include <list>
#include <memory>

namespace uhf {
namespace manager {
		
	class Thread;
	
	/////////////////////////////////////////////////////////////////////
	
	class ThreadManager
	{
		public:
			ThreadManager();
			
			void initialize();
			
			void activate();
			void deactivate();
			
			void waitForCompletion();
			
			void registerThread(std::shared_ptr<Thread>);

		private:
			std::list<std::shared_ptr<Thread> > m_workers;		
	};
}
}
