#include "InvocationRequestShipper.hpp"

#include <string>
#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"


////////////////////////////////////////////////////////////

namespace WTF
{
		InvocationRequestShipper::InvocationRequestShipper(const std::string& service) 
			: BusMessage("INVOCATION")
			, m_service(service)
		{
			
		}
}
