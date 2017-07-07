#include "BackendConfiguration.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>
#include <boost/foreach.hpp>

namespace WTF
{

namespace configuration
{
	
	BackendConfiguration::BackendConfiguration()
	{
	
	}
	
	BackendConfiguration BackendConfiguration::load(boost::property_tree::ptree& node)
	{
		using namespace boost::property_tree;
		MDW_LOG_INFO("Loading BE Configuration..."); 
		
		BackendConfiguration conf;
	 
		BOOST_FOREACH(ptree::value_type &v, node.get_child("libraries"))
		{
			std::string libname = v.second.data();
			MDW_LOG_INFO("Library required for BE:" << libname); 
			conf.getLibraries().insert(libname); //[v.first.data()] = v.second.data();
		}	
		
		BOOST_FOREACH(ptree::value_type &v, node.get_child("handlers"))
		{
			std::string verb = v.first.data();
			MDW_LOG_INFO("New verb handled:" << verb); 
			conf.getHandlers().insert( {verb, ServiceConfiguration::load(v.second) } );
		}	
		
		MDW_LOG_INFO("Default handler:"); 
		conf.getDefaultHandler() = ServiceConfiguration::load( node.get_child("defaulthandler") );
		
		return conf;
	}
	
}
	

}

