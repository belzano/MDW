#pragma once

#include "toolbox/entity/Entity.hpp"
#include "uhf/IComponent.hpp"
#include "uhf/IBroker.hpp"

struct MHD_Daemon;

namespace uhf {
namespace http {

	/////////////////////////////////////////////////////////////////////
		
	class TrafficHandler: public IComponent, public toolbox::entity::Entity
	{
	public:
		
		TrafficHandler();
		virtual ~TrafficHandler();
		
		int activate();
		int deactivate();
	
		//int start();
		//void requestShutdown(){}
		
	private:
		int _port;
		MHD_Daemon* m_impl = nullptr;
	};
	//MDW_SHARED_POINTER(TrafficHandler)

}
}
