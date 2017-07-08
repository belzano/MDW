#include "ServiceConfiguration.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>
#include <map>
#include <boost/foreach.hpp>


namespace uhf
{

namespace configuration
{
/*	
	ServiceConfiguration ServiceConfiguration::load(boost::property_tree::ptree& node)
	{
		using namespace boost::property_tree;
		
		ServiceConfiguration conf;
  
		conf.getServiceName() = node.get_child("servicename").data();	
		MME_LOG_INFO(" - service :" << conf.getServiceName());

		BOOST_FOREACH(ptree::value_type &v, node.get_child("staticparams"))
		{
			MME_LOG_INFO(" - static param: " <<v.first.data() << ":" << "[" << v.second.data() << "]");
			conf.getStaticParameters().insert( { v.first.data(), v.second.data()} );
		}
				
		return conf;
	}
*/	
	
}
	

}

