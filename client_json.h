#ifndef _CLIENT_JSON_H
#define _CLIENT_JSON_H
#include "client.h"

extern std::string get_registration_json(void);

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
std::string get_local_file(json_object *j);
std::string get_local_thumbfile(json_object *j);
std::string get_local_nfo(json_object *j);
std::string get_video_size(json_object *j);
std::string get_local_file_size(json_object *j);
std::string get_local_thumb_file(json_object *j);
std::string get_thumb_size(json_object *j);
std::string get_download_time();
std::string get_category(json_object *j);
std::string get_content_provider(json_object *j);
std::string get_unique_id(json_object *j);
std::string get_summary(json_object *j);
std::string get_title(json_object *j);
std::string get_time_stamp(json_object *j);
std::string get_duration(json_object *j);
std::string get_sdk_metadata(json_object *j);
std::string get_streams(json_object *j);
std::string get_adserver_url(json_object *j);
std::string get_tags(json_object *j);
std::string get_priority(json_object *j);
std::string get_object_type(json_object *j);
std::string get_thumb_attribs(json_object *j);
std::string get_object_attribs(json_object *j);
std::string get_children(json_object *j);
std::string get_policy_name(json_object *j);
std::string get_key_server_url(json_object *j);
std::string quotesql(const std::string& s);
std::string quotesqlint(std::string s);
bool quotsqlbool(bool b);


#endif
