#include "ThreadRunner.hpp"

#include "toolbox/ExecutionContext.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"
#include "toolbox/ptree/Helper.hpp"

#include <thread>
#include <chrono>
#include <signal.h>

namespace uhf {
namespace manager {
 
	/////////////////////////////////////////////////////////////////////

	ThreadRunner::ThreadRunner()
	{
	
	}
	
	/////////////////////////////////////////////////////////////////////

	ThreadRunner::~ThreadRunner()
	{
	
	}

	/////////////////////////////////////////////////////////////////////

//	void RunnerImpl::activate() 
	//{
		//std::string filename = toolbox::ExecutionContext::instance().getDirCfg() + _name + "/" + "init.json";
		//WTF_LOG_INFO("Process::initialize configuration from [" << filename << "]");

		//std::shared_ptr<ProcessConfiguration> config(new ProcessConfiguration());
		//bridge::ptree::helper::Bridge(filename, *config.get());

		//m_processManager->initialize() ;// TODO
	//}

	////////////////////////////////////////////////////////////	
		
	int ThreadRunner::asyncStart()
	{
// 		// Load the configuration. It will be looked up in conf_dir/Master/boot.json 
// 		// initialize the ProcessManager
// 		initialize();
// 		
// 		// Activate threads and processes
// 		WTF_LOG_INFO("activating managers");
// 		m_processManager->activate();
// 		
// 		while (! m_processManager->shutdownRequested())
// 		{
// 			sleep(100);
// 		}
// 		
// 		WTF_LOG_INFO("Deactivating managers");
// 		m_processManager->deactivate();
// 		
		return 0;
	}
	
	////////////////////////////////////////////////////////////	
			
	int ThreadRunner::asyncStop()
	{
		return 0;
	}
	
}
}
