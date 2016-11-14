#include "client.h"

int main(int argc, char* argv[])
{
 try{

    if (argc != 5)
      {
	std::cout << "Usage: client <server> <schemaName> <tenantId> <publicKey>\n";
	return 1;
      }
    std::cout << " Server " << argv[1] << std::endl;
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], "443");
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
    
    client c(io_service, context, iterator, argv[1], argv[2], argv[3], argv[4]);
    io_service.run();
     }catch (std::exception& e){
     std::cerr << "Exception: " << e.what() << "\n";
    }
    std::cin.get();
  return 0;
}
