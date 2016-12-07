#include "client.h"
#include "client_json.h"
#include <json/json.h>
#include <json/json_object.h>
#include <string>

int get_manifest_from_server(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  std::cout << "get manifest called" << std::endl;
  boost::asio::io_service io_service;
  
  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(arv1, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  std::string path = "/Anaina/v0/Download-Manifest";
  client c(io_service, context, iterator, arv1, arv2, arv3, arv4, path);

  io_service.run();
  
  std::string jstr = c.get_response_json();
  std::cout << "manifest: " << jstr << std::endl;

  return 0;
}

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
    std::string path = "/Anaina/v0/Register";
    client c(io_service, context, iterator, argv[1], argv[2], argv[3], argv[4], path);
    
    io_service.run();
        
    std::string jstr = c.get_response_json();
    
    handle_registration_json(jstr, argv[1]);
    
    std::cout << "Registration DONE" << std::endl;
     
 }catch (std::exception& e){
     std::cerr << "Exception: " << e.what() << "\n";
    }

 while(1)
   {
     std::string mani = "cacheFill";
     std::string val;
     std::getline(std::cin,val);
     if(val.compare(0,6, "cacheFill"))
       get_manifest_from_server(argv[1], argv[2], argv[3], argv[4]);
     else
       std::cout << "mani " << val << std::endl;
   }
 return 0;
}


