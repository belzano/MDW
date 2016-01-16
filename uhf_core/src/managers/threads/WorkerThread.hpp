#pragma once

#include "toolbox/Types.hpp"

namespace uhf{
namespace threads{	
	
	class WorkerThread 
	{
		public:	
			WorkerThread(const std::string& name);
						
			virtual void initialize();
			virtual int activate();
			
			virtual int run() = 0;
			
			void requestShutdown();
			bool shutdownRequested() const;
			
			virtual int waitForCompletion();
			
		protected:
			bool OneEyeSleepMs(int time, int checkPeriod = 100);
			
		private:
			std::string 			_name;
			pthread_t  				_processingThread;
			
			bool 			_shutdownRequested;
	};
}
}
