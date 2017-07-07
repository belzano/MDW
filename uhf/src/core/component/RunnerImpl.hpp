#pragma once

#include <string>
#include <memory>

namespace uhf {
namespace component {

	//////////////////////////////////////////////////////////////

	class RunnerImpl
	{
		public:	
			RunnerImpl();
			virtual ~RunnerImpl();
			
			int run();
			      
			void requestShutdown();
			bool shutdownRequested() const;
		  
		private:
			// Read the conf, Load libraries, instanciate/initialize components
			//void initialize();
	};
}
}
