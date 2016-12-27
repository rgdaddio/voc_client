#include "client_db.h"
#include "client_downloader.h"
#include <string>      
#include <iostream>  
#include <sstream> 
#include <boost/regex.hpp>

static int downloader(json_object *str, int file_type);
static void parse_url(const std::string& url, std::string& domain, std::string& path, std::string& proto);

std::map<std::string, std::string> manifest_processing(void)
{
  sqlite3 *db = open_voc_db();
  std::map<std::string, std::string> message = get_voc_access_vals(db);
  std::cout << "manifest processing" << std::endl;
  //system("generate_voc_html.py");
  close_voc_db(db);
  return message;
  
}


int install_cache(std::string json)
{
  sqlite3 *db = open_voc_db();
  std::cout << "json to install" << json << std::endl;
  json_object * jobj = json_tokener_parse(json.c_str());
  if(jobj)
    creat_cache_table_entry(db, json); //this loads json into db send json array obj
  std::cout << "object type " << json_object_get_type(jobj) << std::endl;
  std::cout << "array length " << json_object_array_length(jobj);
  for(int i = 0; i < json_object_array_length(jobj); i++)
    {
      json_object *lobj = json_object_array_get_idx(jobj, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      bool status = json_object_object_get_ex(lobj, "streams", &objtor);
      std::cout << "Stream status: " << status << std::endl; 
      for(int i = 0; i < json_object_array_length(objtor); i++)
	{
	  if(i == 1)//just grab the first one for now FIXME
	    break;
	  json_object *pobj = json_object_array_get_idx(objtor, i);
	  std::cout<< "video streams: " << json_object_to_json_string_ext(pobj, 0 ) << " type " 
		   << json_object_get_type(pobj) <<std::endl;
	  json_object *str = json_object_object_get(pobj,"url");
	  std::cout << "str 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << json_object_get_string(str) << std::endl;
	  downloader(str, 1);
	}
      status = json_object_object_get_ex(lobj, "thumbFile", &objtor);
      downloader(objtor, 2);
    }
  
  return 0;
}

static int downloader(json_object *str, int file_type)
{
  
  std::string path;
  std::string domain;
  std::string proto;
  parse_url(json_object_get_string(str), domain, path, proto);
  std::cout << "next download" << std::endl;
  std::cout << "downloader domain: " << domain << " downloader path " << path << std::endl;

  std::cout << "object done!!!!!!!!!!!!!!!!" << std::endl;
  if(proto.compare("https") == 0)
    https_downloader(domain, path, file_type);
  if(proto.compare("http") == 0)
    http_downloader(domain, path, file_type);
  return 0;
}


static void parse_url(const std::string& url, std::string& domain, std::string& path, std::string& proto)
{
    boost::regex ex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
    boost::cmatch what;
    if(regex_match(url.c_str(), what, ex)) 
    {
      proto    = std::string(what[1].first, what[1].second);
      domain   = std::string(what[2].first, what[2].second);
      std::string port     = std::string(what[3].first, what[3].second);
      path     = std::string(what[4].first, what[4].second);
      std::string query    = std::string(what[5].first, what[5].second);
      std::cout << "[" << url << "]" << std::endl;
      std::cout << proto << std::endl;
      std::cout << "domain " << domain << std::endl;
      std::cout << port << std::endl;
      std::cout << "path " << path << std::endl;
      std::cout << query << std::endl;
      std::cout << "-------------------------------" << std::endl;
    }
}
