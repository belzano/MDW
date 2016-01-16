#pragma once

#include "BusMessage.hpp"

namespace WTF
{
	/////////////////////////////////////////////////////////////////////	
	
	class SendReplyRequest : public BusMessage
	{
	public:
	
		SendReplyRequest(const std::string& service);

		std::string 		m_service;
	};
		
}
