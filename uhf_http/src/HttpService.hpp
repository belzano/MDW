#pragma once

#include "uhf/service/Service.hpp"
#include <toolbox/Types.hpp>

#include <string>
#include <map>

namespace uhf {
namespace http {

	//////////////////////////////////////////////////////////

	// A service::Service object to hook http services to uhf::service registry
	class HttpService : public uhf::service::Service
	{
		public :
			HttpService();
			virtual int invoke(std::shared_ptr<uhf::service::InvocationRequest>);
	};
}
}  // namespace uhf
