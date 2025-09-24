#include "../include/Server.h"

Server::Server(boost::asio::io_context& io,short port) : _acceptor(io,tcp::endpoint(tcp::v4(),port)){}

void Server::start()
{
    auto self =  shared_from_this();
    _acceptor.async_accept([this,self](const boost::system::error_code &ec,tcp::socket socket){
        if(!ec)
        {
            std::cout << "Client connecté"<<std::endl;
            std::make_shared<Session>(std::move(socket))->start();
        }
        else
        {
            std::cerr << "Erreur : "<< ec.message();
        }
        start();
    });
}