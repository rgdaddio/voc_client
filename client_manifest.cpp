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
  system("generate_voc_html.py");
  close_voc_db(db);
  return message;
  
}


int install_cache(std::string json)
{
  std::cout << "json to install" << json << std::endl;
  json_object * jobj = json_tokener_parse(json.c_str());
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
