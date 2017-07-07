

#include "uhf/core/ComponentMakerRegistry.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>

using namespace uhf;
using namespace uhf::core;

ComponentMakerRegistry& ComponentMakerRegistry::instance()
{
	static ComponentMakerRegistry instance;
	return instance;
}

////////////////////////////////////////////////////////////////////
    
IComponentMakerPtr ComponentMakerRegistry::getComponentMaker(const std::string& componentName) const
{
	MDW_LOG_DEBUG("looking for maker ["<< componentName	<< "]");	

	std::map<std::string, IComponentMakerPtr >::const_iterator it;
	it = _makers.find(componentName);
	if (it == _makers.end())
	{
		MDW_LOG_DEBUG("maker not found ["<< componentName	<< "]");
		return IComponentMakerPtr(NULL); 
	}	
	
	MDW_LOG_DEBUG("maker found ["<< componentName << "]");
	return it->second;
}

////////////////////////////////////////////////////////////////////

void ComponentMakerRegistry::registerComponentMaker(const std::string& componentName, 
									                IComponentMakerPtr iMaker)
{

	std::map<std::string, IComponentMakerPtr >::iterator it;
	it = _makers.find(componentName);
	if (it != _makers.end())
	{
		// Warning: overriding existing service
	}
	_makers[componentName] = iMaker;
	
	MDW_LOG_INFO("Maker registration ["<< componentName << "] " );
}

