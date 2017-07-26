#pragma once

#include "uhf/bus/Message.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
	
	template <class T>
	class Sender
	{
	public:
		Sender() {}
		~Sender() {}
		
		bool post(const uhf::bus::MessagePtr<T>){ return true; }
	
	protected:
		// std::list<string> _tos
		
	};
	
}
}
}
