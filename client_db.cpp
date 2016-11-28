#include "client.h"
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
  printf("hit the call back\n");
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}


int create_user_table(sqlite3 *db)
{
  int rc;
  char *zErrMsg = 0;
  char *sql = "create table if not exists voc_user ("\
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
    "content_policy text,"\
    "congestion text,"\
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
