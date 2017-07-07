#pragma once

#include "ServiceTemplate.hpp"
#include <set>

using std::string;
using std::set;

class ServiceSystemInfo : public WTF::ServiceTemplate<ServiceSystemInfo>
{   
public:

    ServiceSystemInfo();

	virtual bool process(const std::string url,
					 const std::map<std::string, std::string>& urlargs, 			 
					 const std::map<std::string, toolbox::DataPtr>& postargs,
					 toolbox::DataPtr& response);
};

WTF_SERVICE_REGISTRATION( ServiceSystemInfo )

