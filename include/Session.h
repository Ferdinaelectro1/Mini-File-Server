#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include "Parser.h"

using boost::asio::ip::tcp;

class Session : public  std::enable_shared_from_this<Session>
{
    public:
       Session(tcp::socket socket);
       void start();

    private:
       char buffer[1024];
       tcp::socket _socket;
       Parser parser;

    private:
       void _do_read();   
       void _write(const std::string& msg);    
};