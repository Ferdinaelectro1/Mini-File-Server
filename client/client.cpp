#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <memory>
#include <thread>

using boost::asio::ip::tcp;

class Client : public std::enable_shared_from_this<Client>
{
    public:
       Client(boost::asio::io_context& io): _socket(io)
       {
          
       }
       void start(tcp::resolver::results_type endpoint,const std::string &file_name)
       {
          _file_name = file_name;
          do_connect(endpoint);
       }

       void sendToServer(const std::string &msg)
       {
         _file_name = msg;
         do_write(_file_name + '\n');
       }

    private:
       tcp::socket _socket;
       char read_buffer[4095];
       std::string _file_name;

    private:
       std::string get_file_name()
       {
           std::string file_name;
           std::getline(std::cin,file_name);
           return file_name;
       }

       void generate_file(const std::string& file_content)
       {
          std::ofstream file(_file_name);
          if(!file)
          {
            std::cerr << "Erreur lors de la création du fichier de sortie"<< std::endl;
            return;
          }
          file << file_content;
          file.close();
       }

       void do_connect(tcp::resolver::results_type endpoint)
       {
          auto self =  shared_from_this();
          boost::asio::async_connect(_socket,endpoint,[this,self](const boost::system::error_code& ec,tcp::endpoint){
              if(!ec)
              {
                std::cout << "Client connecté avec succès" << std::endl;
                do_write(_file_name+'\n');
              }
              else
              {
                 std::cerr << "Erreur lors de la connexion au serveur : "<< ec.message() << std::endl;
              }
          }
          );
       }

       void do_write(const std::string &msg)
       {
          auto self = shared_from_this();
          _socket.async_write_some(boost::asio::buffer(msg),[this,self](const boost::system::error_code& ec,size_t){
             if(!ec)
             {
                std::cout << "Requête lancé avec succès" << std::endl;
                do_read();
             }
             else
             {
                std::cerr << "Erreur "<<ec.message() << std::endl;
             }
          }
          ); 
       }

       void do_read()
       {
          auto self =  shared_from_this();
          _socket.async_read_some(boost::asio::buffer(read_buffer),[this,self](const boost::system::error_code& ec, size_t lenght){
                if(!ec)
                {
                    generate_file(std::string(read_buffer,lenght));
                    std::cout << "fichier reçu avec succès"<< std::endl;
                }
                else
                {
                    std::cerr << "Erreur : "<< ec.message() << std::endl;
                }
          });
       }


};

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage ./client file_name" << std::endl;
        exit(1);
    }

    std::string file_name = argv[1];

    try
    {
        boost::asio::io_context io;
        tcp::resolver resolver(io);

        auto endpoints = resolver.resolve("127.0.0.1","12345");
        auto client =  std::make_shared<Client>(io);
        client->start(endpoints,file_name);

        std::thread input_thread([client](){
           std::string input = "";
           while (std::getline(std::cin,input))
           {
              std::cout << ">> "<<input<<std::endl;
              if(input.size() == 0)
              {
                 break;
              }
              client->sendToServer(input);
           }
        });

        io.run();
        input_thread.join();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Erreur : "<<e.what()<<std::endl;
    }
    return 0;
}