#pragma once


#include <memory>
#include "uhf/service/InvocationRequest.hpp"

#include "toolbox/utils/Registry.hpp"


#define WTF_REGISTER_SERVICE(ServiceType, svckey)  WTF_REGISTRY_DO_REGISTRATION(uhf::service::Service, ServiceType, "" #svckey "")

namespace uhf {
namespace service {

	class InvocationRequest;

	class Service
	{   
	public:
		virtual ~Service() {}
	 
		virtual int invoke(std::shared_ptr<InvocationRequest> request) = 0;
	};


}
}  // namespace uhf
