#pragma once

#include "uhf/bus/Message.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
	
	template <class T>
	class Listener // : public Updatable
	{
	public:
		Listener() {}
		~Listener() {}
		
		void onUpdate() 
		{
			// tryDequeue
			
			// onMessageReceived(Message<T>);
		}
		
	protected:
	
		virtual void onMessageReceived(Message<T> ) = 0;

		// std::string _queue_name
	};
	
}
}
}
