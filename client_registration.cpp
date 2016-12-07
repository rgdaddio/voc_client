#include "client_db.h"

int handle_registration_json(std::string jstr, std::string server)
{
  std::string testsql = "SELECT * from voc_user";
  std::string testtable = "SELECT name FROM sqlite_master WHERE type='table' AND name='voc_user'";
  sqlite3 *db = open_voc_db();
  
  int rc = create_user_table(db);
  rc = create_uuid_table(db);
  rc = create_provider_table(db);
  rc = create_category_table(db);
  rc = create_cache_table(db);
  rc = create_content_table(db);
  rc = create_consumption_table(db);
  rc = create_ad_consumption_table(db);
  rc = create_playing_table(db);
  std::string json  =  get_voc_user_json(db, testtable);
  if(json.empty())
    {
      rc = creat_user_table_entry(db, jstr, server);
    }      
  else
    std::cout<< "This device is already registered" << std::endl;
 
  close_voc_db(db);
}
