#include <boost/chrono.hpp>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <ctime>
using boost::asio::ip::udp;

class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      socket_(io_service, udp::endpoint( boost::asio::ip::address_v4::any(), port))
  {
      std::fill(data_, data_ + max_length, 0);
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&server::handle_receive_from, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive_from(const boost::system::error_code& error,
      size_t bytes_recvd)
  {
    if (!error && bytes_recvd > 0)
    {
        std::cout  << "Connection from: " << sender_endpoint_.address().to_string() << " " << sender_endpoint_.port() << std::endl;

      socket_.async_send_to(
          boost::asio::buffer(data_, strlen(data_)), sender_endpoint_,
          boost::bind(&server::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }

  void handle_send_to(const boost::system::error_code& /*error*/,
      size_t /*bytes_sent*/)
  {  

      std::fill(data_, data_ + max_length, 0);
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&server::handle_receive_from, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

  }

private:
  boost::asio::io_service& io_service_;
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 300 };
  char data_[max_length];
};

int main(int argc, char* argv[])
{
  try
  {
    std::cout << "Starting server" << std::endl;

    boost::asio::io_service io_service;
    short port = 3002;
    using namespace std; 
    server s(io_service, port);
    std::cout << "Server started. Listening on port:" <<port << std::endl;
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}