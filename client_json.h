#ifndef _CLIENT_JSON_H
#define _CLIENT_JSON_H
#include "client.h"

int handle_registration_json(std::string jstr, std::string server);
std::string get_voc_id(json_object *j);
std::string get_platform(json_object *j);
std::string get_device_id(json_object *j);
std::string get_device_type(json_object *j);
std::string get_access_token(json_object *j);
std::string get_refresh_token(json_object *j);
std::string get_congestion_detection(json_object *j);
std::string get_ads_frequency(json_object *j);
std::string get_daily_download_quota(json_object *j);
std::string get_daily_download_wifi(json_object *j);
std::string get_daily_download_cellular(json_object *j);
std::string get_sdk_capabilities(json_object *j);
std::string get_daily_download_manifest(json_object *j);
std::string get_max_content_duration(json_object *j);
std::string get_play_ads(json_object *j);
std::string get_skip_policy(json_object *j);
std::string get_tod_policy(json_object *j);
std::string get_token_expiration(json_object *j);
std::string get_server_state(json_object *j);
std::string quotesql( const std::string& s);
std::string quotesqlint(std::string s);
bool quotsqlbool(bool b);


#endif
