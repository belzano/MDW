#pragma once

#include <memory>
#include "uhf/service/InvocationRequest.hpp"

#include "task/Task.hpp"

namespace uhf {	
namespace service {
	
	class ServiceInvocationTask : public uhf::tasks::Task
	{
		public:
			ServiceInvocationTask();
			int run();
			
		private:
			std::shared_ptr<InvocationRequest> m_invocationRequest;
	};

}
}
