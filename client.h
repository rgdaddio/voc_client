#ifndef _CLIENT__H_
#define _CLIENT__H_
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <string.h>
#include "json/json.h"
#include "json/json_object.h"
#include <sqlite3.h>
#include <string>
#include <sstream>
using boost::asio::ip::tcp;
enum class xtype {registration=1, get_manifest, download};
class client
{
  private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  boost::asio::ip::tcp::resolver::iterator citerator;
  boost::asio::streambuf request_;
  boost::asio::streambuf response_;
  tcp::resolver resolver_;
  std::string schma;
  std::string tenant;
  std::string pubkey;
  std::string servr;
  std::string cjson;
  std::string cpath;
  std::ostringstream sline;
  xtype ltype;
  
  public:
  client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
	 boost::asio::ip::tcp::resolver::iterator endpoint_iterator, std::string server,std::string schema_name,
	 std::string tenant_id, std::string public_key, std::string path, xtype type);

  bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

  void handle_resolve(const boost::system::error_code& err);
  void handle_start(const boost::system::error_code& error);
  void handle_connect(const boost::system::error_code& err);
  void handle_write_request(const boost::system::error_code& err);
  void handle_read_status_line(const boost::system::error_code& err);
  void handle_read_headers(const boost::system::error_code& err, size_t bytes_transferred);
  void handle_read_content(const boost::system::error_code& err, size_t bytes_transferred);
  void build_http_post_header(std::string server_ip, std::string json);
  void build_http_get_header(std::string server_ip, std::string json);
  std::string get_reg_json(void);
  std::string get_req_json(void);

  std::string get_response_json(void)
    {
      return cjson;
    }
  std::string get_rest_path(void)
    {
      return cpath;
    }

  boost::asio::streambuf& get_raw_response_strm(void)
    {
      return response_;
    }


};
#endif
