#pragma once

#include <memory>
#include "uhf/IComponent.hpp"
#include "uhf/IBroker.hpp"

namespace uhf {
namespace core {
namespace component {
	
	class BootstrapImpl;
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap : public IComponent
	{
	public:
		constexpr static const char* TypeName = "uhf::core::component::Bootstrap";
	
		Bootstrap(IBrokerPtr broker);
		~Bootstrap();
		
		void loadComponents(const std::string& configFilename);

	private:
		
		BootstrapImpl* m_impl;
	};
	
	typedef std::shared_ptr<Bootstrap> BootstrapPtr;
}
}
}
