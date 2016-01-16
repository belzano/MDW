#pragma once

#include <string>
#include <memory>
#include <map>

#include "uhf/http/Service.hpp"

namespace uhf {
namespace http {

class ServiceRegistry 
{
	public:
		static std::shared_ptr<Service> getService(const std::string&);
		
};

}
} // namespace uhf ends

