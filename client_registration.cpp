#include "client_db.h"

int handle_registration_json(std::string jstr, std::string server)
{
  std::string testsql = "SELECT * from voc_user";
  sqlite3 *db = open_voc_db();
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  new_obj = json_object_object_get(new_obj, "accessToken");
  
  std::string token = json_object_get_string(new_obj);
  int rc = create_user_table(db);
  //std::cout << "create status: " << rc << std::endl;
  rc = creat_user_table_entry(db, jstr, server);
  rc = select_voc_table(db, testsql); 
  close_voc_db(db);
}
