#ifndef _CLIENT_DB_H_
#define _CLIENT_DB_H_
#include "client.h"

extern sqlite3 *open_voc_db(void);
extern void close_voc_db(sqlite3 *db);
extern int create_user_table(sqlite3 *db);
extern int insert_voc_table(sqlite3 *db, std::string sql_stmt);
extern int select_voc_table(sqlite3 *db, std::string sql_stmt);
#endif
