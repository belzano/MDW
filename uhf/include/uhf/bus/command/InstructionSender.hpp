#pragma once

#include "uhf/bus/Message.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
		
	class CommandSender
	{
	public:
		CommandSender() {}
		~CommandSender() {}
		
		void onUpdate() 
		{
			// tryDequeue
			
			// Lookup for Consumer<uhf::bus::MessagePtr>
			
		}
	
	protected:
		// std::string _queue_name
	};
	
}
}
}
