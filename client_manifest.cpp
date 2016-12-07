#include "client_db.h"


std::string manifest_processing(void)
{
  sqlite3 *db = open_voc_db();
  std::string test = get_voc_access_vals(db);
  std::cout << "manifest processing" << std::cout;
  return test;
  close_voc_db(db);
}
