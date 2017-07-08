
#include <string>
#include "toolbox/Types.hpp"
#include "uhf/service/Service.hpp"
#include "uhf/service/ServiceRegistry.hpp"
#include "uhf/service/ServiceInvocationTask.hpp"


namespace uhf {	
namespace service {
	
	///////////////////////////////////////////////////////////////////
	
	ServiceInvocationTask::ServiceInvocationTask()
		: uhf::tasks::Task("ServiceInvocation")
	{
		
	}
	
	///////////////////////////////////////////////////////////////////
	
	int ServiceInvocationTask::run()
	{
		// Get the Service from the invocationrequest serviceType
		std::shared_ptr<Service> theService = ServiceRegistry::getService( m_invocationRequest->getType() );
		// TODO check if null
		
		// Invoke it
		return theService->invoke(m_invocationRequest);
	}
	
	///////////////////////////////////////////////////////////////////
	
}
}
