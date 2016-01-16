#include "ServiceConfiguration.hpp"

#include "wtf/toolbox/Logger.hpp"

#include <iostream>
#include <map>
#include <boost/foreach.hpp>



template<>
void ptreeToObject<std::map<std::string, std::string> >	(const boost::property_tree::ptree& iNode, std::map<std::string, std::string>& oResult)
{
	ptreeToObjectMap<std::string, std::string>(iNode, oResult);
}

template<> 
void objectToPtree<std::map<std::string, std::string> >	(const std::map<std::string, std::string>& oResult, boost::property_tree::ptree& iNode)
{
	objectMapToPtree<std::string, std::string>(oResult, iNode);
}


namespace WTF
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

