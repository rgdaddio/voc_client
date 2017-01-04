#include "client.h"
#include "client_json.h"
#include "client_manifest.h"
#include "client_registration.h"
#include <json/json.h>
#include <json/json_object.h>
#include <string>

int get_manifest_from_server(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(arv1, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  std::string path = "/Anaina/v0/Download-Manifest";
  xtype type = xtype::get_manifest;
  if(type == xtype::get_manifest)
    std::cout << "valid type" << std::endl;
  client c(io_service, context, iterator, arv1, arv2, arv3, arv4, path, type);

  io_service.run();
  
  std::string jstr = c.get_response_json();
  //std::cout << "manifest: " << jstr << std::endl; //DEBUG
  if(!jstr.empty()){
    install_cache(jstr);
    system("test/generate_voc_html.py"); //Create output file
  }
  return 0;
}

int register_user(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  boost::asio::io_service io_service;

  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(arv1, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  std::string path = "/Anaina/v0/Register";
  xtype type = xtype::registration;
  client c(io_service, context, iterator, arv1, arv2, arv3, arv4, path, type);

  io_service.run();

  std::string jstr = c.get_response_json();

  handle_registration_json(jstr, arv1);

  //std::cout << "Registration DONE" << std::endl; //DEBUG
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
    //std::cout << " Server " << argv[1] << std::endl;
    std::string user = validate_user_for_registration();
    //std::cout << "user!! " << user << std::endl;
    if(user.empty())
      register_user(argv[1], argv[2], argv[3], argv[4]);
    else
      std::cout << "User is previously registered " << std::endl;
     
  }catch (std::exception& e){
    std::cerr << "Caught input Exception: " << e.what() << "\n";
  }

 while(1)
   {
     std::cout << "Options: <cacheFill> " << std::endl;
     std::string mani = "cacheFill";
     std::string val;
     std::getline(std::cin,val);
     //std::cout << "val!!!!!!!!!!!!!!!!!!!!!!!!! " << val << std::endl;
     if(val.compare("cacheFill") == 0)
       get_manifest_from_server(argv[1], argv[2], argv[3], argv[4]);
     else
       std::cout << "Unknown Option " << val << std::endl;
   }
 return 0;
}


