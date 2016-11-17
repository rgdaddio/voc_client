#include "client.h"
#include "client_db.h"

//json-c interface file

//TEST JSON-c
static int creat_user_table_entry(sqlit3 *db, std::string jstr);
static std::string quotesql( const std::string& s ) {
  return std::string("'") + s + std::string("'");
}
int handle_registration_json(std::string jstr)
{
  sqlite3 *db = open_voc_db();
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  new_obj = json_object_object_get(new_obj, "accessToken");
  
  std::string token = json_object_get_string(new_obj);
  std::cout << "ATOKEN: " << token << std::endl;
  std::cout << "GOTTTTTTTTTT " << std::endl;
  int rc = create_user_table(db);
  std::cout << "create status: " << rc << std::endl;
  rc = creat_user_table_entry(db, jstr); 
  close_voc_db(db);
}

static int creat_user_table_entry(sqlit3 *db, std::string jstr)
{
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  std::string userId = "test";
  std::string password = "test";
  string sqlstatement =
    "INSERT INTO voc_user (my_row, userid, password, device_id, platform, device_type, access_token, refresh_token, voc_id, congestion_detection, ads_frequency, daily_quota, daily_manifest, max_content_duration, play_ads, skip_policy_first_time, tod_policy, token_expiration, server, server_state) VALUES ("
    NONE,
    + quotesql(userId) + ","
    + quotesql(password) + ","
    + quotesql() + ","
    + quotesql(password) + ");";
  
}
