#pragma once

#include <map>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include "toolbox/Types.hpp"

namespace WTF
{

namespace configuration
{

	class ServiceConfiguration
	{
		
	public:
		ServiceConfiguration();
		
		const std::string& getServiceName() const;
		      std::string& getServiceName();
		
		const std::map< std::string, std::string >& getStaticParameters() const;
		      std::map< std::string, std::string >& getStaticParameters();
		
		static ServiceConfiguration load(boost::property_tree::ptree& node);
		
	private:
	
		std::string _serviceName;
		std::map< std::string, std::string > _staticParams;
	};
	
	}

}

