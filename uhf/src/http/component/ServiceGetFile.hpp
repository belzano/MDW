#pragma once

#include "uhf/http/component/Consumer.hpp"

namespace uhf {
namespace http {
namespace component {

	class ServiceGetFile : public Consumer
	{   
	public:
		
		ServiceGetFile();

		int process(uhf::http::InvocationRequestPtr request) override;

	};
 
}
}
}
