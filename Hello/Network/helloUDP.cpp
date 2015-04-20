#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
/*
-lboost_system -lboost_thread might work.
*/
using boost::asio::ip::udp;
enum { max_length = 1024 };

int main(int argc, char* argv[])
{
char request[max_length];
try
{

    boost::asio::io_service io_service;

    udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), "10.192.15.180" , "3002");
    udp::resolver::iterator iterator = resolver.resolve(query);

    using namespace std; // For strlen.
    std::cout << "Write to me: ";
    while(1)
    {
        std::cin.getline(request, max_length);
        size_t request_length = strlen(request);
        s.send_to(boost::asio::buffer(request, request_length), *iterator);

        char reply[max_length];
        udp::endpoint sender_endpoint;
        size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
        std::cout << "Say:";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
        std::cout << "Say What?" ;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  std::cin.getline(request, max_length);
  return 0;
}