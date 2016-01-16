#include "Server.hpp"

#include <iostream>
#include <string>

#include "ServiceInvocator.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

////////////////////////////////////////////////////////////

namespace WTF
{
		
	Server::Server(const std::string& name, int port)
		: Backend(name)
		, _httpTrafficHandler(port)
		{}

	////////////////////////////////////////////////////////////	
		
	void Server::initialize()
	{	
		Backend::initialize();
	}

	////////////////////////////////////////////////////////////	

	int Server::activate()
	{		
		return _httpTrafficHandler.activate();
	}

	////////////////////////////////////////////////////////////	

	int Server::deactivate()
	{		
		return _httpTrafficHandler.deactivate();
	}

}
