#include "client.h"
#include "client_manifest.h"
#include<iostream>
#include <jsoncpp/json/json.h>

//
//This is the primary interface to the boost asio system
//for https/ssl.
//
//In a 'c' system these interfaces could be swapped out for
//a more sockets based system or a messaging middleware package
//like nanomsg.
//
//This handles both messaging and is an "internal" interface. 
//Typically handling internal operations such as getManifest
//or Registration. External access should be done with the
//http_client or https_client modules.
//

using boost::asio::ip::tcp;

client::client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
	       boost::asio::ip::tcp::resolver::iterator endpoint_iterator, std::string server,std::string schema_name,
	       std::string tenant_id, std::string public_key, std::string path, xtype type)
  : socket_(io_service, context),
    citerator(endpoint_iterator),
    resolver_(io_service),
    schma(schema_name),
    tenant(tenant_id),
    pubkey(public_key),
    servr(server),
    cpath(path),
    ltype(type)
  {
    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    std::string json = "";
    if(type == xtype::registration)
      json = get_reg_json();
    else if(type == xtype::get_manifest)
      json = get_req_json();
    else if(type == xtype::status)
      json = get_status_json();
    else
      std::cout << "No POST operation" << std::endl; 
    
    if(type ==  xtype::registration || type == xtype::get_manifest || type == xtype::status)
      build_http_post_header(servr, json);
    else
      std::cout << "Unknown operation type" << std::endl;
    
    // Start an asynchronous resolve to translate the server and service names
    // into a list of endpoints.
    socket_.set_verify_mode(boost::asio::ssl::context::verify_peer);
    socket_.set_verify_callback(boost::bind(&client::verify_certificate, this, _1, _2));
    tcp::resolver::query query(server, "443"); //This could handle DNS if need be.
    resolver_.async_resolve(query,
			    boost::bind(&client::handle_resolve, this,
					boost::asio::placeholders::error));
  }

client::client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
               boost::asio::ip::tcp::resolver::iterator endpoint_iterator, std::string server, std::string json)
  : socket_(io_service, context),
    citerator(endpoint_iterator),
    resolver_(io_service),
    servr(server),
    ijson(json)
{

  socket_.set_verify_mode(boost::asio::ssl::context::verify_peer);
  socket_.set_verify_callback(boost::bind(&client::verify_certificate, this, _1, _2));
  tcp::resolver::query query(server, "443"); //This could handle DNS if need be.                                                 
  resolver_.async_resolve(query,
			  boost::bind(&client::handle_resolve, this,
				      boost::asio::placeholders::error));
}
//Currently by-passed we still use ssl but we don't do cert validation for now.
bool client::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
  {
    //JUST A DUMMY fOR NOW
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    //std::cout << "Verifying:\n" << subject_name << std::endl;
    
    //return preverified;                                                                                                   
    return true;
  }


void client::handle_resolve(const boost::system::error_code& err)
  {
    if (!err)
      {
	// Attempt a connection to the first endpoint in the list. Each endpoint
	// will be tried until we successfully establish a connection.
	//tcp::endpoint endpoint = *endpoint_iterator;
	boost::asio::async_connect(socket_.lowest_layer(),citerator,
				   boost::bind(&client::handle_start, this,
					       boost::asio::placeholders::error));
      }
    else
      {
	std::cout << "Error: " << err.message() << "\n";
      }
  }

void client::handle_start(const boost::system::error_code& error)
  {
    if(!error){
      std::cout << "Connection OK!" << std::endl;
      socket_.async_handshake(boost::asio::ssl::stream_base::client, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
    }else{
      std::cout << "Connect failed: " << error.message() << std::endl;
    }
  }

void client::handle_connect(const boost::system::error_code& err)
  {
    if (!err)
      {
	// The connection was successful. Send the request.
	boost::asio::async_write(socket_, request_,
				 boost::bind(&client::handle_write_request, this,
					     boost::asio::placeholders::error));
      }
    else if (citerator != tcp::resolver::iterator())
      {
	// The connection failed. Try the next endpoint in the list.
	////socket_.lowest_layer().close(); FIXME

	async_connect(socket_.lowest_layer(),citerator,
			      boost::bind(&client::handle_connect, this,
					  boost::asio::placeholders::error));
      }
    else
      {
	std::cout << "Handle connect Error: " << err.message() << "\n";
      }
  }

void client::handle_write_request(const boost::system::error_code& err)
  {
    if (!err)
      {
	// Read the response status line.
	boost::asio::async_read_until(socket_, response_, "\r\n",
				      boost::bind(&client::handle_read_status_line, this,
						  boost::asio::placeholders::error));
      }
    else
      {
	std::cout << "handle write Error: " << err.message() << "\n";
      }
  }

void client::handle_read_status_line(const boost::system::error_code& err)
  {
    if (!err)
      {
	// Check that response is OK.
	std::istream response_stream(&response_);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	std::string status_message;
	std::string content_length;
	response_stream >> content_length;
	std::getline(response_stream, status_message);
	if (!response_stream || http_version.substr(0, 5) != "HTTP/")
	  {
	    std::cout << "Invalid response\n";
	    return;
	  }
	if (status_code != 200)
	  {
	    std::cout << "Response https returned with status code ";
	    std::cout << status_code << "\n";
	    return;
	  }

	// Read the response headers, which are terminated by a blank line.
	boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
				      boost::bind(&client::handle_read_headers, this,
						  boost::asio::placeholders::error,
						  boost::asio::placeholders::bytes_transferred));
      }
    else
      {
	std::cout << "status line d Error: " << err << "\n";
      }
  }

void client::handle_read_headers(const boost::system::error_code& err, size_t bytes_transferred)
  {
    
    if (!err)
      {
	// Process the response headers.
	std::istream response_stream(&response_);
	std::string header;
	while (std::getline(response_stream, header) && header != "\r")
	  //std::cout << "header " << header << "\n\n";
	  ;

	// Write whatever content we already have to output.
	if (response_.size() > 0) //&& ltype != xtype::download)
	  {
	    sline << &response_;
	    cjson = sline.str();
	  }
	  
	// Start reading remaining data until EOF.
	boost::asio::async_read(socket_, response_,
				boost::asio::transfer_at_least(1),
				boost::bind(&client::handle_read_content, this,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
      }
    else
      {
	std::cout << "b Error: " << err << "\n";
      }
  }

void client::handle_read_content(const boost::system::error_code& err, size_t bytes_transferred)
  {
    sline << &response_;
    cjson = sline.str();
    
    if(bytes_transferred != 0)
      {
	if (!err)
	  {
	    // Write all of the data that has been read so far.
	    // Continue reading remaining data until EOF.
	    boost::asio::async_read(socket_, response_,
				    boost::asio::transfer_at_least(1),
				    boost::bind(&client::handle_read_content, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	  }
	else if (err != boost::asio::error::eof)
	  {
	    std::cout << "c Error: " << err << "\n";
	  }
      }
  }


void client::build_http_post_header(std::string server_ip, std::string json)
{
  std::ostream request_stream(&request_);
  request_stream << "POST "  << cpath << " HTTP/1.1 \r\n";
  request_stream << "Host:"  << servr << "\r\n";
  request_stream << "User-Agent: C/1.0\r\n";
  request_stream << "Content-Type: application/json\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Content-Length: " << json.length() << "\r\n";
  request_stream << "Connection: close\r\n\r\n";  //NOTE THE Double line feed                                                                                                                             
  request_stream << json;
}


void client::build_http_get_header(std::string server_ip, std::string json)
{
  std::ostream request_stream(&request_);

  request_stream << "GET "  << cpath << " HTTP/1.1 \r\n";
  request_stream << "Host:"  << servr << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";  //NOTE THE Double line feed                                                              
}


std::string client::get_reg_json(void)
{
 
  Json::Value body(Json::objectValue);
  Json::Value serverState;
  serverState["schemaName"] = schma;
  serverState["tenantId"] = tenant;
  body["serverState"] = serverState;
  body["publicKey"] = pubkey;
  body["platform"] = "linux";
  body["deviceId"] = "623bce38-a1f4-11e6-bb6c-3417eb9985a6";
  body["deviceType"] = "pc";
  body["pushToken"] = "";
  body["version"] = "17.2.3";

  //better way to do this?
  Json::FastWriter fastWriter;
  std::string output = fastWriter.write(body);

  return output;
}


std::string client::get_status_json(void)
{
  //TODO will need to access the database and get status related variables to put in here 
  std::map<std::string, std::string> json = manifest_processing();

  Json::Value body(Json::objectValue);
  Json::Value serverState;
  serverState["schemaName"] = schma;
  serverState["tenantId"] = tenant;
  body["serverState"] = serverState;
  body["vocId"] = json["voc_id"];
  body["platform"] = "linux";
  body["deviceId"] = "623bce38-a1f4-11e6-bb6c-3417eb9985a6";
  body["deviceType"] = "pc";
  body["refreshToken"] = json["refresh_token"];
  body["accessToken"] = json["access_token"];
  body["version"] = "17.2.3";
  Json::Value deviceStatus;
  deviceStatus["charger"] = true;
  body["deviceStatus"] = deviceStatus;

  Json::FastWriter fastWriter;
  std::string output = fastWriter.write(body);
  return output;
}

std::string client::get_req_json(void)
{
  std::map<std::string, std::string> json = manifest_processing();
  Json::Value body(Json::objectValue);
  Json::Value serverState;
  serverState["schemaName"] = schma;
  serverState["tenantId"] = tenant;
  body["serverState"] = serverState;
  body["vocId"] = json["voc_id"];
  body["platform"] = "linux";
  body["deviceId"] = "623bce38-a1f4-11e6-bb6c-3417eb9985a6";
  body["deviceType"] = "pc";
  body["refreshToken"] = json["refresh_token"];
  body["accessToken"] = json["access_token"];
  body["version"] = "17.2.3";
  Json::Value deviceStatus;
  deviceStatus["charger"] = true;
  body["deviceStatus"] = deviceStatus;

  Json::FastWriter fastWriter;
  std::string output = fastWriter.write(body);
  return output;
}
