#pragma once

#include "ServiceTemplate.hpp"
#include <set>

using std::string;
using std::set;


class ServiceGetJob : public WTF::ServiceTemplate<ServiceGetJob>
{   
public:

    ServiceGetJob();
    
    virtual bool process(const std::string url,
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& postargs,
						 toolbox::DataPtr& response);

};

WTF_SERVICE_REGISTRATION( ServiceGetJob )

