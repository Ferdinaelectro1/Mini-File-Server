#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include "Session.h"

using boost::asio::ip::tcp;

class Server : public std::enable_shared_from_this<Server>
{
    public:
      Server(boost::asio::io_context& io,short port);
      void start();

    private:
      tcp::acceptor _acceptor;
};