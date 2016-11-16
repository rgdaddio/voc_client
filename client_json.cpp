#include "client.h"
#include "client_db.h"

//json-c interface file

//TEST JSON-c
int handle_registration_json(std::string jstr)
{
  sqlite3 *db = open_voc_db();
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  new_obj = json_object_object_get(new_obj, "accessToken");
  
  std::string token = json_object_get_string(new_obj);
  std::cout << "ATOKEN: " << token << std::endl;
  close_voc_db(db);;
}
