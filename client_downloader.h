#ifndef __HTTPS_DOWNLOADER_H_
#define __HTTPS_DOWNLOADER_H_
int https_downloader(std::string domain, std::string path, int file_type);
int http_downloader(std::string domain, std::string path, int file_type);
int downloader(json_object *str, int file_type, std::string suffix);
#endif
