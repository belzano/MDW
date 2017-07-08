#pragma once

#include <map>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include "toolbox/Types.hpp"
#include "toolbox/ptree/Helper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"


namespace uhf
{

namespace configuration
{

	class ServiceConfiguration
	{
		typedef std::map<std::string, std::string> StaticParameters;
		MAKE_ATTRIBUTE(std::string, ServiceName)
		MAKE_ATTRIBUTE(StaticParameters, StaticParameters)	
	};
	
	}

}

