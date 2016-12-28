#include "client.h"
#include "client_db.h"
#include "client_downloader.h"
#include <iostream>
#include <string>
#include <sstream>
#include <boost/uuid/sha1.hpp>
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

std::string get_sha1(const std::string& str)
{
  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes(str.data(), str.size());
  unsigned hash[5] = {0};
  sha1.get_digest(hash);

  // Back to string                                                                                                                                    
  char buf[41] = {0};

  for (int i = 0; i < 5; i++)
    {
      std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }

  return std::string(buf);
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
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyDownloadWifi");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string get_daily_download_cellular(json_object *j)
{
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
  std::stringstream s;
  json_object *tmp = json_object_object_get(j, "dailyManifestCount");
  if(!tmp)
    return 0;
  s << json_object_get_int(tmp);
  return s.str();
}

std::string get_max_content_duration(json_object *j)
{
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


#if 0
std::string get_registration_json(void)
{
  std::ostringstream oss;
  oss << "{" << "\"serverState\"" << ":" << "{" << "\"schemaName\"" << ":" << "\"" << schma << "\"" << "," << "\"tenantId\"" ":" 
      << "\""<< tenant << "\"" << "}" << "," << "\"publicKey\"" << ":" << "\"" << pubkey << "\"" << "," << "\"platform\"" ":" "\"linux\"" 
      << "," << "\"deviceId\"" ":" << "\"623bce38-a1f4-11e6-bb6c-3417eb9985a6\"" << "," << "\"deviceType\"" << ":" << "\"pc\"" 
      << "," << "\"pushToken\"" << ":" << "\"tt\"" << "," << "\"version\"" << ":" << "\"17.2.3\"""}";    
  std::cout << "str: " << oss.str() << std::endl;
  return oss.str();
}
#endif

std::string get_local_file(json_object *j) //j is an array object
{
  std::string err = "error";
  for(int i = 0; i < json_object_array_length(j); i++)
    {
      json_object *lobj = json_object_array_get_idx(j, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      json_object *lfile;
      bool status = json_object_object_get_ex(lobj, "streams", &objtor); //TBD check status
      std::cout << "streams status: " << status << std::endl;
      status = json_object_object_get_ex(lobj, "uniqueId", &lfile); //TBD check status
      std::cout << "unique Id: " << json_object_get_string(lfile) << std::endl;
      for(int i = 0; i < json_object_array_length(objtor); i++)
	{
	  if(i == 1)//just grab the first one for now FIXME
	    break;
	  json_object *pobj = json_object_array_get_idx(objtor, i);
	  std::cout<< "video streams: " << json_object_to_json_string_ext(pobj, 0 ) << " type " 
		   << json_object_get_type(pobj) <<std::endl;
	  std::string local_file = get_sha1(json_object_get_string(lfile));
	  json_object *str = json_object_object_get(pobj,"url");
	  std::cout << "str 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << json_object_get_string(str) << std::endl;
	  //return json_object_get_string(str);
	  std::cout << "sha local file: " << local_file + ".1" << std::endl;
	  downloader(str, 1, local_file + ".1"); //need this but not now
	  return (local_file + ".1");
	}
    }
  return err;
}

std::string get_local_thumb_file(json_object *j) //j is an array object
{
  
  std::string err = "error";
  
  for(int i = 0; i < json_object_array_length(j); i++)
    {
      json_object *lobj = json_object_array_get_idx(j, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      json_object *lfile;
      bool status;
      if((status = json_object_object_get_ex(lobj, "thumbFile", &objtor)))
	{
	  status = json_object_object_get_ex(lobj, "uniqueId", &lfile);
	  std::string local_thumb = json_object_get_string(lfile);
	  downloader(objtor, 2, local_thumb + ".2");
	  return (local_thumb + ".2"); 
	  //return json_object_get_string(objtor);
	}  
    }
  return err;
}

std::string get_local_nfo(json_object *j)
{
  std::string err = "not done";
  return err;
}


std::string get_video_size(json_object *j)
{
  std::stringstream s;
  int test = 0xdeadbeef;
  std::string err = "error";
#if 0 //tbd  
  for(int i = 0; i < json_object_array_length(j); i++)
    {
      json_object *lobj = json_object_array_get_idx(j, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      bool status;
      if((status = json_object_object_get_ex(lobj, "thumbFile", &objtor)))
	{
	  return json_object_get_string(objtor);
	}  
    }
  return err;
}
#endif
#if 0
  json_object *tmp = json_object_object_get_ex(j, "dailyDownloadWifi");
  if(!tmp)
    return 0;
#endif
  s << test;
  return s.str();
}

std::string get_thumb_size(json_object *j)
{
  std::stringstream s;
  std::string err = "error";

  for(int i = 0; i < json_object_array_length(j); i++)
    {
      json_object *lobj = json_object_array_get_idx(j, i);
      std::cout << "in cache loop " << std::endl;
      json_object *objtor;
      bool status;
      if((status = json_object_object_get_ex(lobj, "thumbSize", &objtor)))
	{
	  s << json_object_get_int(objtor);
	  return s.str();
	}  
    }
  return err;
}


