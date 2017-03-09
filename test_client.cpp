#include "client.h"
#include "client_json.h"
#include "client_manifest.h"
#include "client_registration.h"
#include <json/json.h>
#include <json/json_object.h>
#include <string>


std::string make_request(std::string ip_address,  std::string schema_name,
                std::string tenant_id, std::string sdk_key,
                std::string path, xtype type){

  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(ip_address, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);

  client c(io_service, context, iterator, ip_address, schema_name, tenant_id, sdk_key, path, type);

  io_service.run();

  std::string jstr = c.get_response_json();

  //std::cout << jstr << std::endl;

  return jstr;
}

int send_status(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  std::string path = "/Anaina/v0/Status";
  xtype type = xtype::status;
  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);
  return 0;
}

int get_manifest_from_server(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  std::string path = "/Anaina/v0/Download-Manifest";
  xtype type = xtype::get_manifest;

  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);

  if(!jstr.empty()){
    install_cache(jstr);
    system("test/generate_voc_html.py"); //Create output file Jon's python script
  }
  return 0;
}

int hello_voc(std::string arv1, std::string arv2, std::string arv3, std::string arv4)
{
  std::string path = "/Anaina/v0/HelloVoC";
  xtype type = xtype::registration; // xtype::hello?

  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);

  std::cout << jstr << std::endl;

  return 0;
}

int get_provider_list(std::string arv1, std::string arv2, std::string arv3, std::string arv4){
  std::string path = "/Anaina/v0/Provider-List";
  xtype type = xtype::get_manifest; // xtype::provider_list?
  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);
  std::cout << jstr << std::endl;
  handle_provider_list(jstr, arv1);
  return 0;
}

int get_topic_list(std::string arv1, std::string arv2, std::string arv3, std::string arv4){
  std::string path = "/Anaina/v0/topic_list";
  xtype type = xtype::get_manifest; // xtype::provider_list?
  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);
  std::cout << jstr << std::endl;
  return 0;
}

int get_profile(std::string arv1, std::string arv2, std::string arv3, std::string arv4){
  std::string path = "/Anaina/v0/profile";
  xtype type = xtype::get_manifest; // xtype::provider_list?
  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);
  std::cout << jstr << std::endl;
  return 0;
}

int get_policy(std::string arv1, std::string arv2, std::string arv3, std::string arv4){
  std::string path = "/Anaina/v0/getPolicy";
  xtype type = xtype::get_manifest; // xtype::provider_list?
  std::string jstr = make_request(arv1, arv2, arv3, arv4, path, type);
  std::cout << jstr << std::endl;
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

    std::string user = validate_user_for_registration();
    if(user.empty())
      register_user(argv[1], argv[2], argv[3], argv[4]);
    else
      std::cout << "User is previously registered " << std::endl;

  }catch (std::exception& e){
    std::cerr << "Caught input Exception: " << e.what() << "\n";
  }

 while(1)
   {
     std::cout << "\nOptions: <cacheFill> <hello> <getProviderList> <getTopicList> <getProfile> <getPolicy> <^C> " << std::endl;
     //std::string mani = "cacheFill";
     std::string val;
     std::getline(std::cin,val);

     if(val.compare("cacheFill") == 0){
       get_manifest_from_server(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("hello") == 0){
        hello_voc(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("getProviderList") == 0){
        get_provider_list(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("getTopicList") == 0){
        get_topic_list(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("getProfile") == 0){
        get_profile(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("getPolicy") == 0){
        get_policy(argv[1], argv[2], argv[3], argv[4]);
     }
     else if(val.compare("status") == 0){
        send_status(argv[1], argv[2], argv[3], argv[4]);
     }
    else{
       std::cout << "Unknown Option " << val << std::endl;
    }
   }
 return 0;
}


