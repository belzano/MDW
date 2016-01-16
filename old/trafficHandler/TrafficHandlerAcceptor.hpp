#pragma once

#include "TrafficHandlerConnection.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,  const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  tcp::acceptor acceptor_;
};
