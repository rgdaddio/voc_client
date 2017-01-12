#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

typedef std::unordered_map<std::string, std::string>::iterator hash_map_iterator;

std::unordered_map<std::string, std::string> hash_map_create()
{
  std::unordered_map<std::string, std::string> hashMap;
  return hashMap;
}

bool hash_map_insert_item(std::unordered_map<std::string, std::string> &hashMap, std::string key, std::string value)
{
  std::pair<hash_map_iterator, bool> result;
  std::pair<std::string,std::string> lmap(key, value);
  result = hashMap.insert(lmap);
  
  if(result.second == false){
    std::cout << "Insert Failure" << std::endl;
  }
  return result.second;
}
    
int hash_map_delete_item(std::unordered_map<std::string, std::string> &hashMap, std::string key)
{
  return hashMap.erase(key);
}

std::string hash_map_find_item(std::unordered_map<std::string, std::string> &hashMap, std::string key)
{
  std::string empty;
  std::unordered_map<std::string,std::string>::const_iterator got = hashMap.find(key);

  if(got == hashMap.end())
    {
      std::cout << "empty" << std::endl;
      return empty;
    }
  else
    {
      return got->second;
    }
}

void hash_map_interate(std::unordered_map<std::string, std::string> &hashMap)
{
  for (std::pair<std::string, std::string> element : hashMap)
    {
      std::cout << element.first << " :: " << element.second << std::endl;
    }
}
