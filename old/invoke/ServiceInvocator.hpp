#pragma once

#include <map>
#include <string>
#include <set>
#include <memory>

#include "QueryReply.hpp"

#include "wtf/api/Service.hpp"
#include "wtf/api/ServiceFactory.hpp"
#include "LibLoader.hpp"

#include "BackendConfiguration.hpp"
#include "ServerConfiguration.hpp"

using std::map;
using std::string;
using std::set;

namespace  WTF
{

class ServiceInvocator
{
public:

    ServiceInvocator();
    
    bool invoke(const Query&, Reply&);
        
private:
	std::shared_ptr<Service> resolveUrl(const std::string& url);
	
    void _getInvalidResponse(string& response);
   
    configuration::ServerConfiguration _config;	 
    configuration::BackendConfiguration _be_config;	
	std::set<LibLoader> _loadedLibsList;
};

} // namespace WTF ends

