#include "BusMessageListener.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

/*
#include "platform.h"
#include <iostream>
#include <string>
#include <signal.h>
#include <pthread.h>
*/

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

////////////////////////////////////////////////////////////////

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

////////////////////////////////////////////////////////////////

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service) 
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), 13))
  {
    start_accept();
  }

private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  tcp::acceptor acceptor_;
};


////////////////////////////////////////////////////////////////

namespace WTF
{
		
	BusMessageListener::BusMessageListener( int port)
		: _port(port)
	{}

	////////////////////////////////////////////////////////////	

	int BusMessageListener::activate()
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
			MDW_LOG_ERROR("Caught exception" << std::cerr << e.what() << ".");
		}
	
		return 0;
	}
		
	////////////////////////////////////////////////////////////	

	int BusMessageListener::deactivate()
	{
		return 0;		
	}

}