#include "client.h"
#include "client_db.h"

//json-c interface file

//TEST JSON-c
static int creat_user_table_entry(sqlite3 *db, std::string jstr);
static std::string get_voc_id(json_object *j);
static std::string get_platform(json_object *j);
static std::string get_device_id(json_object *j);
static std::string get_device_type(json_object *j);
static std::string get_access_token(json_object *j);
static std::string get_refresh_token(json_object *j);

static std::string quotesql( const std::string& s ) 
{
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

static int creat_user_table_entry(sqlite3 *db, std::string jstr)
{
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  std::string userId = "test";
  std::string password = "test";
  std::string tnull = "NULL";
  int dummy = 0;
  std::string sqlstatement =
    "INSERT INTO voc_user (my_row, userid, password, device_id, platform, device_type, access_token, refresh_token, voc_id, congestion_detection, ads_frequency, daily_quota, daily_manifest, max_content_duration, play_ads, skip_policy_first_time, tod_policy, token_expiration, server, server_state) VALUES ("
    + quotesql(tnull.c_str()) + ","
    + quotesql(userId.c_str()) + ","
    + quotesql(password.c_str()) + ","
    + quotesql((get_device_id(new_obj)).c_str()) + ","
    + quotesql((get_platform(new_obj)).c_str()) + ","
    + quotesql((get_device_type(new_obj)).c_str()) + ","
    + quotesql((get_access_token(new_obj)).c_str()) + ","
    + quotesql((get_refresh_token(new_obj)).c_str()) + ","
    + quotesql((get_voc_id(new_obj)).c_str()) + "," 
    ");";
  
  std::cout << "sql stmt: " << sqlstatement << std::endl;
}

static std::string get_voc_id(json_object *j)
{
  std::string rc;
  std::cout << "vocid" << std::endl;
  json_object *tmp = json_object_object_get(j, "vocId");
  std::cout << json_object_get_string(tmp) << std::endl;
  return (rc = json_object_get_string(tmp));
}

static std::string get_platform(json_object *j)
{
  std::string rc;
  return (rc = "Linux");
}

static std::string get_device_id(json_object *j)
{
  std::string rc;
  return (rc = "000000DEADBEEF");
}

static std::string get_device_type(json_object *j)
{
  std::string rc;
  return (rc = "000000DEADBEEF");
}

static std::string get_access_token(json_object *j)
{
  std::string rc;
  std::cout << "accessToken" << std::endl;
  json_object *tmp = json_object_object_get(j, "accessToken");
  std::cout << json_object_get_string(tmp) << std::endl;
  return (rc = json_object_get_string(tmp));
}


static std::string get_refresh_token(json_object *j)
{
  std::string rc;
  std::cout << "refreshToken" << std::endl;
  json_object *tmp = json_object_object_get(j, "refreshToken");
  std::cout << json_object_get_string(tmp) << std::endl;
  return (rc = json_object_get_string(tmp));
}
