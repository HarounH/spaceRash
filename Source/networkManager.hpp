#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <boost/array.hpp>
#include <boost/bimap.hpp>
#include <boost/asio.hpp>
#include "boost/lexical_cast.hpp"
#include <boost/thread.hpp>
#include "mQ.hpp"
#include <memory>
#include <array>
#include <unordered_map>

#define NETWORK_BUFFER_SIZE 4096
#define time_out

typedef boost::bimap<long long, boost::asio::ip::udp::endpoint> ClientList;
typedef ClientList::value_type Client;
typedef std::pair<std::string, long long> ClientMessage;

using namespace std;
using boost::asio::ip::udp;

class NetworkManager{
	private:

		boost::mutex mutex;

		// NETWORK MEMBER FUNCTIONS
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint server_endpoint;
		boost::asio::ip::udp::endpoint remote_endpoint;
		std::string myIP;
		unsigned short myPort;
		boost::thread service_thread;
		boost::thread death_thread;	//TODO


		unordered_map<long long,int> timeLeft; //
		unordered_map<long long, bool> has_dropped;   
		std::array<char, NETWORK_BUFFER_SIZE> recv_buffer;  // statically allocated container class used as a buffer for receiving data

		// SERVER machinery
		message_queue< pair<std::string, long long> > messages;
		long long nextClientID;
		ClientList clients;

		// DATA
		unsigned long long receivedMessages;
		unsigned long long receivedBytes;
		unsigned long long sentMessages;
		unsigned long long sentBytes;




		void send(const std::string& message, boost::asio::ip::udp::endpoint target_endpoint);
		
		void handle_receive(const boost::system::error_code&, std::size_t);


		void start_receive();


	public:

		// CTOR and DTOR
		NetworkManager(string IP, unsigned short server_port, string local_ip, unsigned short local_port = 2000);

		
		NetworkManager(string local_ip, unsigned short local_port = 2000);

		
		long long addClient(string IP, unsigned short server_port);
		
		~NetworkManager();

		

		void run_service();

		void SendToClient(const std::string& message, long long clientID);

		void insert_client(boost::asio::ip::udp::endpoint endpoint);

		long long get_client_id(boost::asio::ip::udp::endpoint endpoint);
		long long get_client_id(string, unsigned short);

		bool findClient(string ip, unsigned short port);
		void detectDeath();
		
		void SendToAllExcept(const std::string& message, long long clientID);


		void SendToAll(const std::string& message);

		ClientMessage popMessage();

	    std::string getMyIP();

		unsigned short getMyPort();

		long long numberOfClients();
		// STAT QUERIES
		unsigned long long GetStatReceivedMessages() {return receivedMessages;}
		unsigned long long GetStatReceivedBytes()	   {return receivedBytes;}
		unsigned long long GetStatSentMessages()     {return sentMessages;}
		unsigned long long GetStatSentBytes()        {return sentBytes;}

};

#endif