#pragma once

#include "uhf/http/component/Consumer.hpp"

namespace uhf {
namespace sysmon {
namespace component {

	class ServiceProcInfo : public uhf::http::component::Consumer
	{   
	public:

		ServiceProcInfo();

		int process(uhf::http::InvocationRequestPtr request) override;
	};

}
}
}
