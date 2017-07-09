#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

namespace uhf {
namespace component {

	//////////////////////////////////////////////////////////////

	class Process : public uhf::IComponent, public IActivable
	{
		public:	
			Process();
			virtual ~Process();
			
			int run();
		
			int handle_signal(int signo);
		
			bool shutdownRequested() const;
			void requestShutdown();
			
			const std::string& getName() { return _name; }		
		
		protected:
			virtual void onActivate() override;
			virtual void onPassivate() override;
			virtual int watchdog();
			virtual int waitForCompletion();
				
		protected:
			bool OneEyeSleepMs(int time, int checkPeriod = 100);
			
		private:
			std::string 	_name;		
			bool 			_shutdownRequested;
			bool 			_interactive;	
	};
	
	typedef std::shared_ptr<Process> ProcessPtr;
}
}
