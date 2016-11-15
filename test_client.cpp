#include "client.h"
#include <json/json.h>
#include <json/json_object.h>
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
    std::cout << "\njson: " << c.get_response_json() << std::endl;
    
    std::string jstr = c.get_response_json();

    //TEST JSON-c
    json_object *new_obj = json_tokener_parse(jstr.c_str());
    new_obj = json_object_object_get(new_obj, "accessToken");
    std::string token = json_object_get_string(new_obj);
    std::cout << "ATOKEN: : " << token << std::endl;
     
 }catch (std::exception& e){
     std::cerr << "Exception: " << e.what() << "\n";
    }
    std::cin.get();
  return 0;
}
