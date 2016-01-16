#include "logger/Module.hpp"
#include "Manager.hpp"

namespace logger
{
	///////////////////////////////////////////////

	Module& Module::Instance()
	{
		static Module theModule;
		return theModule;
	}

	///////////////////////////////////////////////

	Module::Module()
	{
		_manager = new Manager();
	}

	///////////////////////////////////////////////

	Module::~Module()
	{
		delete _manager;
	}
	
	///////////////////////////////////////////////

	void Module::activate()
	{
		_manager->activate();
	}

	///////////////////////////////////////////////

	void Module::deactivate()
	{
		_manager->deactivate();
	}
	
	///////////////////////////////////////////////

	void Module::setConfiguration(std::shared_ptr<Configuration> config)
	{
		_config = config;
		
		// Trigger refresh on streams
	}

	///////////////////////////////////////////////

	std::shared_ptr<Configuration> Module::getConfiguration()
	{
		return _config;
	}

	///////////////////////////////////////////////

	Manager& Module::getManager()
	{
		return *_manager;
	}

	///////////////////////////////////////////////

}
