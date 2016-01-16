
#include "toolbox/ExecutionContext.hpp"

#include <stdlib.h>

#include <cassert>
#include <exception>
#include <string>

#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

namespace toolbox {
	
	// Root path
	std::string getApplicationRootDir()
	{
		char* envVar = ::getenv("APP_ROOT_DIR");
		if (envVar != NULL)
			return std::string(envVar);
			
		std::cout << "env var $APP_ROOT_DIR is not defined: defaulting to current directory.";	
		return std::string("./");	
	}

	///////////////////////////////////////////////////////////////////////

	ExecutionContext* ExecutionContext::_instance = NULL;

	ExecutionContext& ExecutionContext::instance()
	{
		if (_instance != NULL)
			return *_instance;
		
		_instance = new ExecutionContext();	
		return *_instance;
	}	
	
	///////////////////////////////////////////////////////////////////////

	void ExecutionContext::init(const std::map<std::string, std::string>& env)
	{
		m_env = env;
	}

	///////////////////////////////////////////////////////////////////////

	std::string ExecutionContext::getDirCfg() const 
	{
		return getApplicationRootDir() + "/" + "cfg";
	}
	
	std::string ExecutionContext::getDirQueues() const
	{
		return getApplicationRootDir() + "/" + "queue";
	}
	
	std::string ExecutionContext::getMessageQueueName() const
	{
		return "default";
	}
	
	std::string ExecutionContext::getDirData() const
	{
		return getApplicationRootDir() + "/" + "data";
	}
	
	std::string ExecutionContext::getDirBin() const
	{
		return getApplicationRootDir() + "/" + "bin";
	}
	
	std::string ExecutionContext::getDirLib() const
	{
		return getApplicationRootDir() + "/" + "lib";
	}
	
	std::string ExecutionContext::getDirDataTestIn() const
	{
		return getApplicationRootDir() + "/" + "data/test/in/";
	}
	
	std::string ExecutionContext::getDirDataTestOut() const
	{
		return getApplicationRootDir() + "/" + "data/test/out/";
	}

}


