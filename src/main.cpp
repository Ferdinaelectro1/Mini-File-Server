#include <boost/asio.hpp>
#include <memory>
#include "../include/Server.h"

int main()
{
    try
    {
        boost::asio::io_context io;
        auto server = std::make_shared<Server>(io,12345);
        server->start();
        std::cout << "Server démarré"<< std::endl;
        io.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}