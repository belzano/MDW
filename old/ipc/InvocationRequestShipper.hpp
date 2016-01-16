#pragma once

#include "wtf/ipc/BusMessage.hpp"
#include "wtf/oltp/InvocationRequest.hpp"
#include <string>

namespace WTF
{
	/////////////////////////////////////////////////////////////////////	
	
	class InvocationRequest;
	
	class InvocationRequestShipper : public BusMessage
	{
	public:
	
		InvocationRequestShipper(const std::string& service);

		std::string 		m_service;
		InvocationRequest* 	m_invocationRequest;	
	};
		
}
