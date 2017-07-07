#pragma once

#include <string>
#include <memory>
#include <map>

#include "Service.hpp"
#include "ServiceFactory.hpp"

namespace  WTF
{

class ServiceRegistry
{
public:
    
    std::shared_ptr<Service> getService(const std::string&) const;

    void registerService(const std::string& url, 
						 std::shared_ptr<ServiceFactory> theFactory);

	static ServiceRegistry& instance();

private:

	std::map<std::string, std::shared_ptr<const ServiceFactory> > _factories;

};



//ServiceRegistry

} // namespace WTF ends

