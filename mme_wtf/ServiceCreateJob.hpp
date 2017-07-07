#pragma once

#include "ServiceTemplate.hpp"
#include <set>

using std::string;
using std::set;


class ServiceCreateJob : public WTF::ServiceTemplate<ServiceCreateJob>
{   
public:

    ServiceCreateJob();
    
    virtual bool process(const std::string url,
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& postargs,
						 toolbox::DataPtr& response);

};

WTF_SERVICE_REGISTRATION( ServiceCreateJob )
