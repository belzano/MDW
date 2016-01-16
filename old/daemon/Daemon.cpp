#include "Daemon.hpp"

#include <iostream>
#include <string>

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

////////////////////////////////////////////////////////////		

namespace WTF
{
		
	Daemon::Daemon(const std::string& name)
		: Backend(name)
		{}

	////////////////////////////////////////////////////////////	
		
	void Daemon::initialize()
	{	
		Backend::initialize();
	}
		

}
