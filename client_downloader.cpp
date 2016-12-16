#include "client.h"
#include "http_client.h"
#include <string>
#include <iostream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>

int https_downloader(std::string domain, std::string path, int file_type)
{

  std::cout << "next download" << std::endl;
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver(io_service);
  boost::asio::ip::tcp::resolver::query query(domain, "443");
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
  std::cout << "downloader domain: " << domain << " downloader path " << path << std::endl;
  xtype type = xtype::download;
  client c(io_service, context, iterator, domain, "test", "test", "test", path, type);
  std::cout << "object done!!!!!!!!!!!!!!!!" << std::endl;

  io_service.run();
  if(file_type == 1)
    {
      boost::asio::streambuf hold;
      std::ofstream outfile("tester.mp4", std::ios::out | std::ios::app | std::ios::binary);
      std::cout << "writing type 1 " << (c.get_raw_response_strm()).size() << std::endl;
      outfile << &(c.get_raw_response_strm());
    }
  if(file_type == 2)
    {
      std::ofstream outfile("tester.jpg", std::ios::out | std::ios::app | std::ios::binary);
      std::cout << "writing type 2" << std::endl;
      outfile << &(c.get_raw_response_strm());
    }
  return 0;
}

int http_downloader(std::string domain, std::string path, int file_type)
{
  std::cout << "HTTP downloader called" << std::endl;
  boost::asio::io_service io_service;
  httpclient c(io_service, domain, path);
  io_service.run();

  if(file_type == 1)
    {
      boost::asio::streambuf hold;
      std::ofstream outfile("tester.mp4", std::ios::out | std::ios::app | std::ios::binary);
      std::cout << "writing type 1 " << (c.get_raw_response_strm()).size() << std::endl;
      outfile << &(c.get_raw_response_strm());
    }
  if(file_type == 2)
    {
      std::ofstream outfile("tester.jpg", std::ios::out | std::ios::app | std::ios::binary);
      std::cout << "writing type 2" << std::endl;
      outfile << &(c.get_raw_response_strm());
    }
  return 0;
}
