#pragma once

#include "uhf/http/component/Consumer.hpp"

namespace uhf {
namespace sysmon {
namespace component {

	class ServiceSystemInfo : public uhf::http::component::Consumer
	{   
	public:

		ServiceSystemInfo();

		int process(uhf::http::InvocationRequestPtr request) override;
	};

}
}
}

