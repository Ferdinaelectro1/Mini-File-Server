#include "../include/Session.h"

Session::Session(tcp::socket socket) : _socket(std::move(socket)){}

void Session::start()
{
    _do_read();
}

//lire les données envoyer par le client et le répondre puis relancer une nouvelle lecture
void Session::_do_read()
{
    auto self = shared_from_this();
    _socket.async_read_some(boost::asio::buffer(buffer),[this,self](const boost::system::error_code& ec,size_t length){
        if(!ec)
        {
            std::string msg(buffer,length);
            std::cout << "Message reçu : "<< msg;
            std::string response = parser.parse(msg);
            _write(response);
            _do_read();
        }
        else if(ec == boost::asio::error::eof)
        {
            std::cout << "Le client a coupé sa connexion !" << std::endl;
        }
        else
        {
            std::cerr << "Erreur : "<< ec.message()<<std::endl;
        }
    });
}

void Session::_write(const std::string& msg)
{    
    auto self = shared_from_this();
    _socket.async_write_some(boost::asio::buffer(msg),[this,self](const boost::system::error_code& ec, std::size_t){
        if(!ec)
        {
            std::cout << "Message envoyé" << std::endl;
        }
        else
        {
            std::cerr << "Erreur : "<<ec.message() << std::endl;
        }
    });
}