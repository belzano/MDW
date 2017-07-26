#pragma once

#include "uhf/bus/Message.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
		
	class MessageQueueWriter
	{
	public:
		MessageQueueWriter() {}
		~MessageQueueWriter() {}
		
		bool post(const uhf::bus::MessagePtr){ return true; }
	
	protected:
		// std::list<string> _tos
		
	};
	
}
}
}
