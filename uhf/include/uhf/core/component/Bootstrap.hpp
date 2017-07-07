#pragma once

#include <memory>
#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {
	
	class BootstrapImpl;
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap : public IComponent
	{
	public:
		Bootstrap();
		~Bootstrap();
		
		void loadComponents(const std::string& configFilename);

	private:
		
		BootstrapImpl* m_impl;
	};
	
	typedef std::shared_ptr<Bootstrap> BootstrapPtr;
}
}
