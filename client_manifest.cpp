#include "client_db.h"
#include "client_downloader.h"
#include <string>      
#include <iostream>  
#include <sstream> 
#include <boost/regex.hpp>

std::map<std::string, std::string> manifest_processing(void)
{
  sqlite3 *db = open_voc_db();
  std::map<std::string, std::string> message = get_voc_access_vals(db);
  close_voc_db(db);
  return message;
  
}

int install_cache(std::string json)
{
  sqlite3 *db = open_voc_db();

  json_object * jobj = json_tokener_parse(json.c_str());
  if(jobj)
    creat_cache_table_entry(db, json); //this loads json into db send json array obj
  close_voc_db(db);
  return 0;
}

