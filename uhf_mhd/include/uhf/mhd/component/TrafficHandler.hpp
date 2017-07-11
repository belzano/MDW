#pragma once

#include "toolbox/entity/Entity.hpp"
#include "uhf/IComponent.hpp"
#include "uhf/IComponentRegistry.hpp"
#include "uhf/core/aspects/IActivable.hpp"

struct MHD_Daemon;

namespace uhf {
namespace mhd {
namespace component {

	/////////////////////////////////////////////////////////////////////
		
	class TrafficHandler: public IComponent, public uhf::component::IActivable, public toolbox::entity::Entity
	{
	public:
		
		TrafficHandler();
		virtual ~TrafficHandler();
		
		void onActivate() override;
		void onPassivate()override;
			
	private:
		MHD_Daemon* m_impl = nullptr;		
		int _port;
	};
	
	//MDW_SHARED_POINTER(TrafficHandler)

}
}
}
