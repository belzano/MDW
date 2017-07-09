#pragma once

#include <memory>
#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

namespace uhf {
namespace component {
	
	class BootstrapImpl;
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap : public uhf::IComponent, public uhf::component::IActivable
	{
	public:
		Bootstrap();
		~Bootstrap();
		
		void setBootstrapFile(const std::string& bootstrapFilename);

		void onActivate() override;
		void onPassivate() override;

	private:
		std::string _bootstrapFilename;
	};
	
	typedef std::shared_ptr<Bootstrap> BootstrapPtr;
}
}
