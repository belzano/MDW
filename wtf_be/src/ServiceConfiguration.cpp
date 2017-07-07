#include "ServiceConfiguration.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>
#include <map>
#include <boost/foreach.hpp>


namespace WTF
{

namespace configuration
{
	
	ServiceConfiguration::ServiceConfiguration()
	{
	
	}
	
	const std::string& ServiceConfiguration::getServiceName() const
	{ 
		return _serviceName; 
	}
	
	std::string& ServiceConfiguration::getServiceName() 
	{ 
		return _serviceName; 
	}
		
	const std::map< std::string, std::string >& ServiceConfiguration::getStaticParameters() const
	{ 
		return _staticParams;
	}
	
	std::map< std::string, std::string >& ServiceConfiguration::getStaticParameters()   
	{ 
		return _staticParams;
	}	
	
	ServiceConfiguration ServiceConfiguration::load(boost::property_tree::ptree& node)
	{
		using namespace boost::property_tree;
		
		ServiceConfiguration conf;
  
		conf.getServiceName() = node.get_child("servicename").data();	
		MDW_LOG_INFO(" - service :" << conf.getServiceName());

		BOOST_FOREACH(ptree::value_type &v, node.get_child("staticparams"))
		{
			MDW_LOG_INFO(" - static param: " <<v.first.data() << ":" << "[" << v.second.data() << "]");
			conf.getStaticParameters().insert( { v.first.data(), v.second.data()} );
		}
				
		return conf;
	}
	
	
}
	

}

