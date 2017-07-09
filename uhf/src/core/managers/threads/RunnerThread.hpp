#pragma once

#include "toolbox/Types.hpp"
#include "uhf/core/aspects/IRunnable.hpp"
#include "Thread.hpp"

namespace uhf{
namespace manager{	
	
	class RunnerThread : public Thread
	{
		public:	
			RunnerThread(const std::string& name, 
						uhf::component::IRunnablePtr );
						
			virtual void run() override;
			
		private:
			uhf::component::IRunnablePtr _runnable;
	};
}
}
