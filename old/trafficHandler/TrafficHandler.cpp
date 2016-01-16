#include "TrafficHandler.hpp"
#include "TrafficHandlerConnection.hpp"
#include "TrafficHandlerAcceptor.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

////////////////////////////////////////////////////////////////

namespace WTF
{
		
	TrafficHandler::TrafficHandler( int port)
		: _port(port)
	{}

	////////////////////////////////////////////////////////////	

	int TrafficHandler::activate()
	{
		try
		{
			/*
			 boost::asio::ip::tcp::acceptor acceptor(io_service);
			boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
			acceptor.open(endpoint.protocol());
			acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			acceptor.bind(endpoint);
			acceptor.listen();
			* */
						
			boost::asio::io_service io_service;
			tcp_server server(io_service);
			io_service.run();
		}
		catch (std::exception& e)
		{
			MDW_LOG_DEBUG("Caught exception" << std::cerr << e.what() << ".");
		}
	
		return 0;
	}
		
	////////////////////////////////////////////////////////////	

	int TrafficHandler::deactivate()
	{
		return 0;		
	}

}
