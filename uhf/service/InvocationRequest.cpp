#include "uhf/service/InvocationRequest.hpp"

namespace uhf {
namespace service {

	////////////////////////////////////////////////////////////
	
	InvocationRequest::InvocationRequest(ServiceType type)
		: m_type(type)
	{

	}

	////////////////////////////////////////////////////////////
	
	InvocationRequest::~InvocationRequest()
	{

	}
	
	////////////////////////////////////////////////////////////
	
	const InvocationRequest::ServiceType& InvocationRequest::getType() const
	{
		return m_type;
	}
}	
}		
