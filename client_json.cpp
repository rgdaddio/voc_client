#include "client.h"
#include "client_db.h"
#include <iostream>
#include <string>
#include <sstream>
//json-c interface file

//TEST JSON-c

std::string quotesql( const std::string& s ) 
{
  return std::string("'") + s + std::string("'");
}

std::string quotesqlint(std::string s)
{
  return s;
}

bool quotsqlbool(bool b)
{
  return b;
}


std::string get_voc_id(json_object *j)
{
  std::string rc;
  std::cout << "vocid" << std::endl;
  json_object *tmp = json_object_object_get(j, "vocId");
  
  return (rc = json_object_get_string(tmp));
}

std::string get_platform(json_object *j)
{
  std::string rc;
  return (rc = "Linux");
}

std::string get_device_id(json_object *j)
{
  std::string rc;
  return (rc = "000000DEADBEEF");
}

std::string get_device_type(json_object *j)
{
  std::string rc;
  return (rc = "000000DEADBEEF");
}

std::string get_access_token(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "accessToken");
  return (rc = json_object_get_string(tmp));
}


std::string get_refresh_token(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "refreshToken");
  return (rc = json_object_get_string(tmp));
}

std::string get_congestion_detection(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "congestionDetection");
  if(!tmp)
    return "";
  return (rc = json_object_get_string(tmp));
}

std::string get_ads_frequency(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "adsFrequency");
  return (rc = json_object_get_string(tmp));
}

std::string get_daily_download_quota(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "dailyDownloadQuota");
  if(!tmp)
    return "";
  return (rc = json_object_get_string(tmp));
}

std::string get_daily_download_wifi(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyDownloadWifi");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string get_daily_download_cellular(json_object *j)
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

std::string get_sdk_capabilities(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "sdkCapabilities");
  return (rc = json_object_get_string(tmp));
}

std::string get_daily_download_manifest(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyManifestCount");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string get_max_content_duration(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "maxContentDuration");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string get_play_ads(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "playAds");
  return (rc = json_object_get_string(tmp));
}

std::string get_skip_policy(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "skipPolicyFirstTime");
  return (rc = json_object_get_string(tmp));
}

std::string get_tod_policy(json_object *j)
{
  std::string rc;
  json_object *tmp = json_object_object_get(j, "todPolicy");
  return (rc = json_object_get_string(tmp));
}


std::string get_token_expiration(json_object *j)
{
  int rc;
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "tokenExpiryDate");
  if(!tmp)
    return 0;
  s << json_object_get_int64(tmp);
  return s.str();
}

std::string get_server_state(json_object *j)
{
  std::string rc = "test";
  json_object *tmp = json_object_object_get(j, "serverState");
  if(!tmp)
    return rc;
  return (rc = json_object_get_string(tmp));
}



