#pragma once

#include "uhf/http/component/Consumer.hpp"

namespace uhf {
namespace sysmon {
namespace component {

	class ServiceDiskInfo : public uhf::http::component::Consumer
	{   
	public:

		ServiceDiskInfo();

		int process(uhf::http::InvocationRequestPtr request) override;
	};

}
}
}
