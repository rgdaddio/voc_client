#include "client.h"
#include "client_json.h"
#include <stdio.h>
#include <stdlib.h>

//sqalite interface file
sqlite3 *open_voc_db(void)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  
  rc = sqlite3_open("rgd.db", &db);
  
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    NULL;
  }else{
    fprintf(stderr, "Opened database successfully\n");
    return db;
  }
}


void close_voc_db(sqlite3 *db)
{
  sqlite3_close(db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  if(NotUsed)
    std::map<std::string, std::string> used = *static_cast <std::map<std::string, std::string> *>(NotUsed);

  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    if(NotUsed)
      (*static_cast <std::map<std::string, std::string> *>(NotUsed)).insert(std::make_pair(azColName[i], argv[i] ? argv[i] : "NULL"));
  }
  printf("%d\n\n", i);
  return 0;
}


int create_user_table(sqlite3 *db)
{
  int rc;
  char *zErrMsg = 0;
  const char *sql = "create table if not exists voc_user ("\
    "userid text,"\
    "password text,"\
    "device_id text,"\
    "platform text,"\
    "device_type text,"\
    "access_token text,"\
    "refresh_token text,"\
    "voc_id text,"\
    "congestion_detection text,"\
    "ads_frequency text,"\
    "daily_quota integer,"\
    "daily_manifest integer,"\
    "daily_download_wifi integer,"\
    "daily_download_cellular integer,"\
    "congestion text,"		      \
    "sdk_capabilities text,"\
    "max_content_duration integer,"\
    "play_ads text,"\
    "skip_policy_first_time text,"\
    "tod_policy text,"\
    "token_expiration integer,"\
    "server text,"\
    "server_state text,"\
    "my_row integer primary key autoincrement);";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if(rc != SQLITE_OK){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }else{
    fprintf(stdout, "User table created sucessfully\n");
  }
  return 0;
}

int insert_voc_table(sqlite3 *db, std::string sql_stmt)
{
  int rc;
  char *zErrMsg = 0;
  rc = sqlite3_exec(db, sql_stmt.c_str(), callback, 0, &zErrMsg);
  if(rc != SQLITE_OK){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }else{
    fprintf(stdout, "User table insert sucess\n");
  }
  return 0;
}

int select_voc_table(sqlite3 *db, std::string sql_stmt, bool ret=false)
{
  int rc;
  char *zErrMsg = 0;
  std::map<std::string, std::string> value_map;
  if(ret == false){
    rc = sqlite3_exec(db, sql_stmt.c_str(), callback, 0, &zErrMsg);
  }
  else
    rc = sqlite3_exec(db, sql_stmt.c_str(), callback, &value_map, &zErrMsg);
  
  if(rc != SQLITE_OK){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }else{
    fprintf(stdout, "User table select sucess\n");
  }

  for ( auto column : value_map )
    {
      std::cout  << column.first << " < " << column.second << ">" << std::endl;
    }       
  if(value_map.empty())
    return 1;
  else 
    return 0;

}


int creat_user_table_entry(sqlite3 *db, std::string jstr, std::string server)
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
    + quotesql((get_daily_download_quota(new_obj)).c_str()) + ","
    + quotesqlint((get_daily_download_manifest(new_obj)).c_str()) + ","
    + quotesqlint((get_daily_download_wifi(new_obj)).c_str()) + ","
    + quotesqlint((get_daily_download_cellular(new_obj)).c_str()) + ","
    + quotesql((get_sdk_capabilities(new_obj)).c_str()) + ","
    + quotesqlint((get_max_content_duration(new_obj)).c_str()) + ","
    + quotesql((get_play_ads(new_obj)).c_str()) + ","
    + quotesql((get_skip_policy(new_obj)).c_str()) + ","
    + quotesql((get_tod_policy(new_obj)).c_str()) + ","
    + quotesqlint((get_token_expiration(new_obj)).c_str()) + ","
    + quotesql(server.c_str()) + ","
    + quotesql((get_server_state(new_obj)).c_str()) +
    ");";
  insert_voc_table(db, sqlstatement);
  //std::cout << "sql stmt: " << sqlstatement << std::endl;
}


std::string get_voc_user_json(sqlite3 *db, std::string stmt)
{
  int rc = 0;
  std::string json = "test";
  std::string ustmt = "select device_id, platform, voc_id, access_token, refresh_token, server, server_state from voc_user";
  //std::string dstmt = "DELETE from voc_user where my_row='1';";
  rc = select_voc_table(db, stmt);
  std::cout << "get_voc_user_json "<< rc << std::endl;
  if(rc == -1)
    {
      std::cout << "table value1: " << rc << std::endl;
      return json;
    }
  
  //rc = select_voc_table(db, dstmt);
  std::cout << "table valuex: " << rc << std::endl;
  rc = select_voc_table(db, ustmt, true);
  if(rc)
    json.clear();
  std::cout << "table value2: " << rc << std::endl;
  return json;
}
