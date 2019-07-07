#include"../include/api.hpp"
#include<boost/asio.hpp>

using boost::asio::ip::tcp;

string api::call()
{
  // Get a list of endpoints corresponding to the server name.
  boost::asio::io_service io_service;
  tcp::resolver resolver(io_service);
  tcp::resolver::query query(this->url, "http");
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  // Try each endpoint until we successfully establish a connection.
  tcp::socket socket(io_service);
  boost::asio::connect(socket, endpoint_iterator);

  // Form the request.
  boost::asio::streambuf request;
  std::ostream request_stream(&request);
  request_stream << "GET " << this->subfolder << " HTTP/1.0\r\n";
  request_stream << "Host: " << this->url << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";

  // Send the request.
  boost::asio::write(socket, request);

  // Read the response status line.
  boost::asio::streambuf response;
  boost::asio::read_until(socket, response, "]");

  // Check that response is OK.
  std::istream response_stream(&response);
  std::string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;
  std::getline(response_stream, status_message);

  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return "Error";
    }
  if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return "Error";
    }

  // Read the response headers, which are terminated by a blank line.
  boost::asio::read_until(socket, response, "\r\n\r\n");

  // Process the response headers.
  std::string header;
  while(std::getline(response_stream, header) && header != "\r"){}

  // Write whatever content we already have to output.
  std::string output;
  if(response.size() > 0)
    std::getline(response_stream, output);

  return output;
}