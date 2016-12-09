#include "client_db.h"
#include <string>      
#include <iostream>  
#include <sstream> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//using boost::property_tree::ptree;
namespace pt = boost::property_tree;

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
	  std::cout<< "video streams: " << json_object_to_json_string_ext(lobj, 0 ) << " type " << json_object_get_type(lobj) <<std::endl;
	  json_object *str = json_object_object_get(lobj,"url");
	  std::cout << "str " << json_object_get_string(str) << std::endl;
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
