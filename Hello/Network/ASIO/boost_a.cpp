
#include <boost/asio.hpp>
#include <iostream>

int main( int argc, char * argv[] )
{
	boost::asio::io_service io_service;
	boost::asio::io_service::work work( io_service );
	// work = boost::none;
	io_service.run();

	std::cout << "Do you reckon this line displays?" << std::endl;

	return 0;
}


/*
typedef boost::bimap<__int64, udp::endpoint> ClientList;
typedef ClientList::value_type Client;
typedef std::pair<std::string, __int64> ClientMessage;

class Server{
	private:

		boost::asio::io_service io_service;
		udp::socket socket;
		udp::endpoint server_endpoint;
		udp::endpoint remote_endpoint;
		boost::thread service_thread;


		void send(std::string message, udp::endpoint target_endpoint)
		{
		    socket.send_to(boost::asio::buffer(message), target_endpoint);
		    sentBytes += message.size();
		    sentMessages++;
		}
		



		unsigned __int64 receivedMessages;
		unsigned __int64 receivedBytes;
		unsigned __int64 sentMessages;
		unsigned __int64 sentBytes;

	public:
		Server(unsigned short local_port){}
		}
		~Server()

		void start_receive()
		{
		    socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
		        boost::bind(&NetworkServer::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}




		void run_service()
		{
		    start_receive();
		    while (!io_service.stopped()){
		        try {
		            io_service.run();
		        } catch( const std::exception& e ) {
		            LogMessage("Server network exception: ",e.what());
		        }
		        catch(...) {
		            LogMessage("Unknown exception in server network thread");
		        }
		    }
		    LogMessage("Server network thread stopped");
		};




		void SendToClient(std::string message, unsigned __int64 clientID, bool guaranteed) 
		{
		    try {
		        send(message, clients.left.at(clientID));
		    }
		    catch (std::out_of_range) {
		        LogMessage("Unknown client ID");
		    }
		}



		unsigned __int64 get_client_id(udp::endpoint endpoint)
		{
		    unsigned __int64 cit = clients.right.find(endpoint);
		    if (cit != clients.right.end())
		        return (*cit).second;

		    nextClientID++;
		    clients.insert(Client(nextClientID, endpoint));
		    return nextClientID;
		}


		unsigned __int64 GetStatReceivedMessages() {return receivedMessages;}
		unsigned __int64 GetStatReceivedBytes()	   {return receivedBytes;}
		unsigned __int64 GetStatSentMessages()     {return sentMessages;}
		unsigned __int64 GetStatSentBytes()        {return sentBytes;}

};*/