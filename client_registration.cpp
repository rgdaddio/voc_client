#include "client_db.h"
#include "client_json.h"

int handle_registration_json(std::string jstr, std::string server)
{
  std::string testsql = "SELECT * from voc_user";
  std::string testtable = "SELECT name FROM sqlite_master WHERE type='table' AND name='voc_user'";
  sqlite3 *db = open_voc_db();
  
  int rc = create_user_table(db);
  if(rc == 0)
    {
      rc = create_uuid_table(db);
      rc = create_provider_table(db);
      rc = create_category_table(db);
      rc = create_cache_table(db);
      rc = create_content_table(db);
      rc = create_consumption_table(db);
      rc = create_ad_consumption_table(db);
      rc = create_playing_table(db);
      rc = create_user_table_entry(db, jstr, server);
      std::cout<< "DB regisistration complete" << std::endl;
    }
  close_voc_db(db);
  return 0;
}

int handle_provider_list(std::string jstr, std::string server)
{
  sqlite3 *db = open_voc_db();
  std::string upsert_query_start = "INSERT OR REPLACE INTO provider VALUES ";
  std::string upsert_query =  upsert_query_start + parse_provider_list(jstr);
  execute_query(db, upsert_query.c_str(), "provider");
  return 0;
}

std::string validate_user_for_registration(void)
{
  std::string testtable = "SELECT name FROM sqlite_master WHERE type='table' AND name='voc_user'";
  sqlite3 *db = open_voc_db();
  std::string json = "error";
  int rc = create_user_table(db);
  if(rc == 0)
    json  =  get_voc_user_json(db, testtable);
  close_voc_db(db);
  return json;
}
