#include "HttpService.hpp"

#include "uhf/service/Service.hpp"
#include "uhf/http/ServiceRegistry.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdint.h>


namespace uhf {
namespace http {


///////////////////////////////////////////////////////////////

HttpService::HttpService()	
{

}

///////////////////////////////////////////////////////////////

int HttpService::invoke(std::shared_ptr<uhf::service::InvocationRequest> iRequest)	
{
	
	// Cast into httpInvocationRequest
	std::shared_ptr<uhf::http::InvocationRequest> theHttpRequest 
				= std::dynamic_pointer_cast< uhf::http::InvocationRequest,	
											 uhf::service::InvocationRequest>(iRequest);
	
	if (theHttpRequest.get() == nullptr)
	{
		// Cast failed. This was not an http request!
		return -1;
	}
	
	std::string httpServiceName = theHttpRequest->getHttpServiceName();
	
	// Get the http service in this request
	std::shared_ptr<uhf::http::Service> theHttpService = ServiceRegistry::getService(httpServiceName);
	if (theHttpService.get() == nullptr)
		return -1;
	
	return theHttpService->invoke(theHttpRequest);
}

}
}

// Registration
WTF_REGISTER_SERVICE(uhf::http::HttpService, HTTP)
