#include "client.h"

//sqalite interface file
sqlite3 *open_voc_db(void)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  
  rc = sqlite3_open("test.db", &db);
  
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
