#ifndef _CLIENT_UTILITIES_H_
#define _CLIENT_UTILITIES_H_

//Returns map object which is passed in to other functions
std::unordered_map<std::string, std::string> hash_map_create();

//Takes map object and key value. Returns true if insert success false otherwise.
bool hash_map_insert_item(std::unordered_map<std::string, std::string> &hashMap, std::string key, 
			  std::string value);

//Returns number of elements deleted everything hash map elements are unique so it will be 0 or 1
int hash_map_delete_item(std::unordered_map<std::string, std::string> &hashMap, std::string key);

//Returns value from the key value pair
std::string hash_map_find_item(std::unordered_map<std::string, std::string> &hashMap, std::string key);

//Prints out entire map
void hash_map_interate(std::unordered_map<std::string, std::string> &hashMap);
#endif
