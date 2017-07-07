
#include "Service.hpp"
#include "ServiceRegistry.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>

using namespace  WTF;

ServiceRegistry& ServiceRegistry::instance()
{
	static ServiceRegistry instance;
	return instance;
}

////////////////////////////////////////////////////////////////////
    
std::shared_ptr<Service> ServiceRegistry::getService(const std::string& url) const
{
	MDW_LOG_DEBUG("looking on service ["<< url	<< "]");	
	
	std::map<std::string, std::shared_ptr<const ServiceFactory> >::const_iterator it;
	it = _factories.find(url);
	if (it == _factories.end())
	{
		MDW_LOG_DEBUG("Service not found ["<< url	<< "]");
		return std::shared_ptr<Service>((Service*)NULL); 
	}	
	
	MDW_LOG_DEBUG("Service found ["<< url	<< "]");
	std::shared_ptr<Service> service = it->second->newInstance();
	return service;
}

////////////////////////////////////////////////////////////////////

void ServiceRegistry::registerService(const std::string& url, 
									std::shared_ptr<ServiceFactory> theFactory)
{

	std::map<std::string, std::shared_ptr<const ServiceFactory> >::iterator it;
	it = _factories.find(url);
	if (it != _factories.end())
	{
		// Warning: overriding existing service
	}
	_factories[url] = theFactory;
	
	MDW_LOG_INFO("Service registration ["<< url << "] " );
}

