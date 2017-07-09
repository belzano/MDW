#pragma once

#include <string>
#include <memory>

namespace uhf {
namespace manager {

	//////////////////////////////////////////////////////////////

	class ThreadRunner
	{
		public:	
			ThreadRunner();
			virtual ~ThreadRunner();
			
			int asyncStart();
					      
			int asyncStop();
			
			//bool shutdownRequested() const;
		  
		private:
			// Read the conf, Load libraries, instanciate/initialize components
			//void initialize();
	};
}
}
