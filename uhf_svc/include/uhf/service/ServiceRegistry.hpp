#pragma once

#include <string>
#include <memory>
#include <map>

#include "uhf/service/Service.hpp"

namespace uhf {
namespace service {

class ServiceRegistry 
{
	public:
		static std::shared_ptr<Service> getService(const std::string&);
		
};

}
} // namespace uhf ends

