#pragma once

#include "toolbox/Types.hpp"

namespace uhf{
namespace manager{	

/*	
	typedef enum ThreadState 
	{
		
	} ThreadState;
	*/
	
	class Thread
	{
		public:	
			Thread(const std::string& name);
						
			virtual void initialize();
			virtual int activate();
			
			virtual void run() = 0;
			
			void pthreadRun();
			
			void requestShutdown();
			bool shutdownRequested() const;
			bool isCompleted() const;
			std::string getName() const { return _name; }
			
			virtual int waitForCompletion();
			
		protected:
			bool OneEyeSleepMs(int time, int checkPeriod = 100);

			std::string 			_name;
			pthread_t  				_processingThread;
			bool 					_shutdownRequested;
			bool 					_completed;
	};
	
	typedef std::shared_ptr<Thread> ThreadPtr;

}
}
