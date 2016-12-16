#ifndef HTTP_CLIENT__H_
#define HTTP_CLIENT__H_
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <fstream> 
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
class httpclient
{
 private:
  tcp::socket socket_;
  boost::asio::ip::tcp::resolver::iterator citerator;
  boost::asio::streambuf request_;
  boost::asio::streambuf response_;
  tcp::resolver resolver_;
 
 public:
  httpclient(boost::asio::io_service& io_service,
	    const std::string& server, const std::string& path);
  
    void handle_resolve(const boost::system::error_code& err,
			tcp::resolver::iterator endpoint_iterator);
    
    void handle_connect(const boost::system::error_code& err,
			tcp::resolver::iterator endpoint_iterator);
    void handle_write_request(const boost::system::error_code& err);
    void handle_read_status_line(const boost::system::error_code& err);
    void handle_read_headers(const boost::system::error_code& err);
    void handle_read_content(const boost::system::error_code& err);
    void build_http_get_header(std::string server_ip, std::string json);
    
    boost::asio::streambuf& get_raw_response_strm(void)
      {
	return response_;
      }
    
};
#endif
