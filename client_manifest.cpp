#include "client_db.h"
#include <string>      
#include <iostream>  
#include <sstream> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>

//using boost::property_tree::ptree;
namespace pt = boost::property_tree;
static int downloader(json_object *str, int file_type);
static void parse_url(const std::string& url, std::string& domain, std::string& path);

std::map<std::string, std::string> manifest_processing(void)
{
  sqlite3 *db = open_voc_db();
  std::map<std::string, std::string> message = get_voc_access_vals(db);
  std::cout << "manifest processing" << std::cout;
  //system("generate_voc_html.py");
  close_voc_db(db);
  return message;
  
}


int install_cache(std::string json)
{
  std::cout << "json to install" << json << std::endl;
  json_object * jobj = json_tokener_parse(json.c_str());
  std::cout << "object type " << json_object_get_type(jobj) << std::endl;
  std::cout << "array length " << json_object_array_length(jobj);
  for(int i = 0; i < json_object_array_length(jobj); i++)
    {
      json_object *lobj = json_object_array_get_idx(jobj, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      bool status = json_object_object_get_ex(lobj, "streams", &objtor);
      for(int i = 0; i < json_object_array_length(objtor); i++)
	{
	  json_object *lobj = json_object_array_get_idx(objtor, i);
	  std::cout<< "video streams: " << json_object_to_json_string_ext(lobj, 0 ) << " type " 
		   << json_object_get_type(lobj) <<std::endl;
	  json_object *str = json_object_object_get(lobj,"url");
	  std::cout << "str 1 " << json_object_get_string(str) << std::endl;
	  downloader(str, 1);
	  str = json_object_object_get(lobj,"thumbFile");
	  std::cout << "str 2" << json_object_get_string(str) << std::endl;
	  downloader(str, 2);
	}
    }
  //std::stringstream ss;
  //ss.str(json);
  //pt::ptree root;
  //pt::read_json(ss, root);
  //pt::const_iterator iter;

  //std::string v = pt.get<std::string>("file");
  //ptree::const_iterator end = pt.end();
  //for(pt::const_iterator iter = pt::begin(); iter != pt::end(); iter++)
  //  {
  //    std::cout << iter->first << "," << iter->second.data() << std::endl;
  //  }
}

static int downloader(json_object *str, int file_type)
{
  
  std::string path;
  std::string domain;
  parse_url(json_object_get_string(str), domain, path);
  
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(domain, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  std::cout << "downloader domain: " << domain << " downloader path " << path << std::endl;
  xtype type = xtype::download;
  client c(io_service, context, iterator, domain, "test", "test", "test", path, type);
  std::cout << "object done!!!!!!!!!!!!!!!!" << std::endl;
  //std::ofstream outfile;
  io_service.run();
  if(file_type == 1)
    {
      std::ofstream outfile("tester.mp4", std::ios::out | std::ios::app | std::ios::binary);
      outfile << &(c.get_raw_response_strm());
    }
  if(file_type == 2)
    {
      std::ofstream outfile("tester.jpg", std::ios::out | std::ios::app | std::ios::binary);
      outfile << &(c.get_raw_response_strm());
    }
  
  //std::cout << "manifest: " << jstr << std::endl;

}


static void parse_url(const std::string& url, std::string& domain, std::string& path)
{
    boost::regex ex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
    boost::cmatch what;
    if(regex_match(url.c_str(), what, ex)) 
    {
      std::string protocol = std::string(what[1].first, what[1].second);
      domain   = std::string(what[2].first, what[2].second);
      std::string port     = std::string(what[3].first, what[3].second);
      path     = std::string(what[4].first, what[4].second);
      std::string query    = std::string(what[5].first, what[5].second);
      std::cout << "[" << url << "]" << std::endl;
      std::cout << protocol << std::endl;
      std::cout << "domain " << domain << std::endl;
      std::cout << port << std::endl;
      std::cout << "path " << path << std::endl;
      std::cout << query << std::endl;
      std::cout << "-------------------------------" << std::endl;
    }
}
