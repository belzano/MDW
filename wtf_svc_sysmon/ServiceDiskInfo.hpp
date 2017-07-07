#pragma once

#include "ServiceTemplate.hpp"
#include <set>

using std::string;
using std::set;


class ServiceDiskInfo : public WTF::ServiceTemplate<ServiceDiskInfo>
{   
public:

    ServiceDiskInfo();
    
    virtual bool process(const std::string url,
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& postargs,
						 toolbox::DataPtr& response);

};
