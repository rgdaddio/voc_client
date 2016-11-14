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

using boost::asio::ip::tcp;

class client
{
  private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  boost::asio::ip::tcp::resolver::iterator citerator;
  boost::asio::streambuf request_;
  boost::asio::streambuf response_;
  tcp::resolver resolver_;
  //char reply_[3451];
  std::string schma;
  std::string tenant;
  std::string pubkey;
  std::string servr;
  
  //boost::asio::streambuf reply_;
  //boost::asio::streambuf request_;
  public:
  client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
	 boost::asio::ip::tcp::resolver::iterator endpoint_iterator, std::string server,std::string schema_name,
	 std::string tenant_id, std::string public_key);

  bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

  void handle_resolve(const boost::system::error_code& err);
  void handle_start(const boost::system::error_code& error);
  void handle_connect(const boost::system::error_code& err);
  void handle_write_request(const boost::system::error_code& err);
  void handle_read_status_line(const boost::system::error_code& err);
  void handle_read_headers(const boost::system::error_code& err, size_t bytes_transferred);
  void handle_read_content(const boost::system::error_code& err, size_t bytes_transferred);
  void build_http_header(std::string server_ip, std::string json);

  std::string get_test_json(void)
    {
      std::string json ("{\"serverState\" :{\"schemaName\": \"pvoc_154tenant_11468515933296\",\"tenantId\": \"quincy_lab_1468860481\"},\"publicKey\": \"57f7fe493be4adfd0f8d80e42998b33cb3bdbde6465fa45b535e2\
e57e3d0b2ad\",\"platform\": \"linux\",\"deviceId\": \"623bce38-a1f4-11e6-bb6c-3417eb9985a6\", \"deviceType\": \"pc\", \"pushToken\": \"tt\", \"version\" : \"17.1.3\"}");

      return json;
    }
};
#endif
