#include "client.h"
#include "client_db.h"
#include <iostream>
#include <string>
#include <sstream>
//json-c interface file

//TEST JSON-c
static int creat_user_table_entry(sqlite3 *db, std::string jstr, std::string server);
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

std::string quotesqlint(std::string s)
{
  return s;
}

static bool quotsqlbool(bool b)
{
  return b;
}

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


static std::string get_voc_id(json_object *j)
{
  std::string rc;
  std::cout << "vocid" << std::endl;
  json_object *tmp = json_object_object_get(j, "vocId");
  
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
  json_object *tmp = json_object_object_get(j, "accessToken");
  return (rc = json_object_get_string(tmp));
}


static std::string get_refresh_token(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "refreshToken");
  return (rc = json_object_get_string(tmp));
}

static std::string get_congestion_detection(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "congestionDetection");
  if(!tmp)
    return "";
  return (rc = json_object_get_string(tmp));
}

static std::string get_ads_frequency(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "adsFrequency");
  return (rc = json_object_get_string(tmp));
}

static std::string daily_download_quota(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "dailyDownloadQuota");
  if(!tmp)
    return "";
  return (rc = json_object_get_string(tmp));
}

std::string daily_download_wifi(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyDownloadWifi");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string daily_download_cellular(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyDownloadCellular");
  if(!tmp){
    std::cout << "FAIL on get !!!!!!!!!!!!\n" << std::endl;
    std::string sc = "";
    return sc;
  }
  s << json_object_get_int64(tmp);
  return s.str();
}

static std::string get_sdk_capabilities(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "sdkCapabilities");
  return (rc = json_object_get_string(tmp));
}

std::string daily_download_manifest(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyManifestCount");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string max_content_duration(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "maxContentDuration");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

static std::string get_play_ads(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "playAds");
  return (rc = json_object_get_string(tmp));
}

static std::string get_skip_policy(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "skipPolicyFirstTime");
  return (rc = json_object_get_string(tmp));
}

static std::string get_tod_policy(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "todPolicy");
  return (rc = json_object_get_string(tmp));
}


std::string token_expiration(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "tokenExpiryDate");
  if(!tmp)
    return 0;
  s << json_object_get_int64(tmp);
  return s.str();
}

static std::string get_server_state(json_object *j)
{
  std::string rc = "test";
  json_object *tmp = json_object_object_get(j, "serverState");
  if(!tmp)
    return rc;
  return (rc = json_object_get_string(tmp));
}


static int creat_user_table_entry(sqlite3 *db, std::string jstr, std::string server)
{
  json_object *new_obj = json_tokener_parse(jstr.c_str());
  std::string userId = "test";
  std::string password = "test";
  std::string tnull = "NULL";
  int dummy = 0;

  std::string sqlstatement =
    "INSERT INTO voc_user (my_row, userid, password, device_id, platform, device_type, access_token, refresh_token, voc_id, congestion_detection, ads_frequency, daily_quota, daily_manifest, daily_download_wifi, daily_download_cellular, sdk_capabilities, max_content_duration, play_ads, skip_policy_first_time, tod_policy, token_expiration, server, server_state) VALUES ("
    + quotesqlint(tnull.c_str()) + ","
    + quotesql(userId.c_str()) + ","
    + quotesql(password.c_str()) + ","
    + quotesql((get_device_id(new_obj)).c_str()) + ","
    + quotesql((get_platform(new_obj)).c_str()) + ","
    + quotesql((get_device_type(new_obj)).c_str()) + ","
    + quotesql((get_access_token(new_obj)).c_str()) + ","
    + quotesql((get_refresh_token(new_obj)).c_str()) + ","
    + quotesql((get_voc_id(new_obj)).c_str()) + ","
    + quotesql((get_congestion_detection(new_obj)).c_str()) + ","
    + quotesql((get_ads_frequency(new_obj)).c_str()) + ","
    + quotesql((daily_download_quota(new_obj)).c_str()) + ","
    + quotesqlint((daily_download_manifest(new_obj)).c_str()) + ","
    + quotesqlint((daily_download_wifi(new_obj)).c_str()) + ","
    + quotesqlint((daily_download_cellular(new_obj)).c_str()) + ","
    + quotesql((get_sdk_capabilities(new_obj)).c_str()) + ","
    + quotesqlint((max_content_duration(new_obj)).c_str()) + ","
    + quotesql((get_play_ads(new_obj)).c_str()) + ","
    + quotesql((get_skip_policy(new_obj)).c_str()) + ","
    + quotesql((get_tod_policy(new_obj)).c_str()) + ","
    + quotesqlint((token_expiration(new_obj)).c_str()) + ","
    + quotesql(server.c_str()) + ","
    + quotesql((get_server_state(new_obj)).c_str()) +
    ");";
  insert_voc_table(db, sqlstatement);
  //std::cout << "sql stmt: " << sqlstatement << std::endl;
}
