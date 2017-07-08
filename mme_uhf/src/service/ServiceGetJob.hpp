#pragma once

#include "uhf/http/InvocationRequest.hpp"
#include "uhf/http/component/Consumer.hpp"
#include <set>

namespace mme {
	
	class ServiceGetJob : public uhf::http::component::Consumer
	{   
	public:
		ServiceGetJob();
		
		virtual int process(uhf::http::InvocationRequestPtr) override;

	};

}
//WTF_SERVICE_REGISTRATION( ServiceGetJob )

