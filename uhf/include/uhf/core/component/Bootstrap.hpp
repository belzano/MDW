#pragma once

#include <memory>
#include "uhf/core/aspects/IRunnable.hpp"

namespace uhf {
namespace component {
	
	class BootstrapImpl;
		
	/////////////////////////////////////////////////////////////////////
		
	class Bootstrap : public uhf::component::IRunnable
	{
	public:
		Bootstrap();
		~Bootstrap();
		
		void setBootstrapFile(const std::string& configFilename);

		void run() override;

	private:
		
		BootstrapImpl* m_impl;
	};
	
	typedef std::shared_ptr<Bootstrap> BootstrapPtr;
}
}
