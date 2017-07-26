#pragma once

#include "uhf/bus/component/Listener.hpp"
#include "uhf/bus/Event.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
		
	class EventListener : public Listener<Event>
	{
	public:
		EventListener() {}
		~EventListener() {}

	protected:	
		virtual void onMessageReceived(Message<Event> ) override {
			// TODO lookup for Consumer<Event>
		}
	};
	
}
}
}
