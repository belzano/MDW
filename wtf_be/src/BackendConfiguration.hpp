#pragma once

#include <map>
#include <set>
#include <string>

#include "toolbox/Types.hpp"
#include "ServiceConfiguration.hpp"

#include <boost/property_tree/ptree.hpp>

namespace WTF
{

namespace configuration
{

	class BackendConfiguration
	{
		
	public:
		BackendConfiguration();
		
		const std::set<std::string>& getLibraries() const { return _libraries; }
		      std::set<std::string>& getLibraries()       { return _libraries; }
		
		const ServiceConfiguration& getDefaultHandler() const { return _defaultHandler; }
		      ServiceConfiguration& getDefaultHandler()       { return _defaultHandler; }
		
		const std::map< std::string, ServiceConfiguration>& getHandlers() const { return _handlers; }
		      std::map< std::string, ServiceConfiguration>& getHandlers()       { return _handlers; }
	
		static BackendConfiguration load(boost::property_tree::ptree& node);
		
	private:
	
		std::set<std::string> 	_libraries;
		ServiceConfiguration 	_defaultHandler;
		std::map< std::string, ServiceConfiguration> _handlers;
	};
	
	}

}

