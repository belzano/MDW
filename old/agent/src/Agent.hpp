#pragma once 

#include "Process.hpp"
#include "ProcessType.hpp"

#include "AgentConfiguration.hpp"
#include "ApplicationServerNodeStatus.hpp"

namespace WTF
{

	/////////////////////////////////////////////////////////////////////

	template <> struct ProcessTypeConfig<WTF::E_Agent> 			
	{ typedef WTF::configuration::AgentConfiguration Type; static const char* Filename;};
	
	/////////////////////////////////////////////////////////////////////

	class Agent : public TypedProcess<ProcessType::E_Agent>
	{
		public:	
			Agent();

		protected:			
			virtual void initialize() override;			
			virtual int activate() override;
			virtual int watchdog() override;
			virtual int deactivate() override;
			virtual int waitForCompletion() override;
			
		private:
			void checkProcesses();
			void checkProcess(configuration::ProcessDescription&);
			void createProcess(configuration::ProcessDescription&);
				
			pthread_t  _mon_thread;
			pthread_t  _cmd_thread;
			
			WTF::configuration::ApplicationServerNodeStatus& getAsNodeStatus() {return _asNodeStatus; }
			WTF::configuration::ApplicationServerNodeStatus _asNodeStatus;
	};

}
