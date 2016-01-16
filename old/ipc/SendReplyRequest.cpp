#include "SendReplyRequest.hpp"

#include <string>
#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"


////////////////////////////////////////////////////////////

namespace WTF
{
		SendReplyRequest::SendReplyRequest(const std::string& service) 
			: BusMessage("SENDREPLY")
			, m_service(service)
		{
			
		}
}
