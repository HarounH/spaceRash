#ifndef NETWORK_MANAGER_CPP
#define NETWORK_MANAGER_CPP
#include "networkManager.hpp"

NetworkManager::~NetworkManager(){
	io_service.stop();
	service_thread.join();
}

/*
void NetworkManager::detectDeath(){
	
	boost::mutex::scoped_lock lock(mutex);
	for (int i = 0; i < timeLeft.size(); i++){
		if (clock() - timeLeft[i] >= time_out) 
		 	{
		 		has_dropped[i] = true;

		 	}
	}

}


long long NetworkManager::dropped_id(){
	
	boost::mutex::scoped_lock lock(mutex);
	typedef unordered_map<long long, bool>::iterator _itr;
	_itr _end = has_dropped.end();
	for (_itr it = has_dropped.begin(); it != _end; it++)
	{
		if (it->second)
			return it->first;
	}

	return -1;

}

void NetworkManager::handleDrops(){
	for (int i = 0; i < has_dropped.size(); i++)
		if (has_dropped[i] == true)
			//
}
*/

NetworkManager::NetworkManager(string IP, unsigned short server_port, string local_ip, unsigned short local_port) : socket(io_service, udp::endpoint(udp::v4(), local_port)), service_thread(boost::bind(&NetworkManager::run_service, this))
{
	boost::asio::ip::udp::resolver resolver(io_service);
	boost::asio::ip::udp::resolver::query query(udp::v4(), IP, boost::lexical_cast< std::string >(server_port));
	boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
	myIP = local_ip;
	myPort = socket.local_endpoint().port();
	nextClientID = 0;
	receivedMessages = 0;
	receivedBytes = 0;
	sentMessages = 0;
	sentBytes = 0;
	remote_endpoint = *iterator;
	insert_client(remote_endpoint);
}

NetworkManager::NetworkManager(string local_ip, unsigned short local_port) : socket(io_service, udp::endpoint(udp::v4(), local_port)), service_thread(boost::bind(&NetworkManager::run_service, this))
{
	nextClientID = 0;
	receivedMessages = 0;
	receivedBytes = 0;
	sentMessages = 0;
	sentBytes = 0;
	myIP = local_ip;
	myPort = socket.local_endpoint().port();

}

long long NetworkManager::addClient(string IP, unsigned short server_port) {
	boost::asio::ip::udp::resolver resolver(io_service);
	boost::asio::ip::udp::resolver::query query(udp::v4(), IP, boost::lexical_cast< std::string >(server_port));
	boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
	remote_endpoint = *iterator;
	insert_client(remote_endpoint);
	return nextClientID;
}

void NetworkManager::start_receive()
{
    socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
    boost::bind(&NetworkManager::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void NetworkManager::send(const std::string& message, boost::asio::ip::udp::endpoint target_endpoint)
{
	socket.send_to(boost::asio::buffer(message), target_endpoint);
	sentBytes += message.size();
	sentMessages++;
}

void NetworkManager::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred){
	if (!error)
	{
	   	ClientMessage message = ClientMessage(std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred),  get_client_id(remote_endpoint));
		if (!message.first.empty())
		{
			boost::mutex::scoped_lock lock(mutex);
			messages.push(message);
			if(message.second != -1)
				timeLeft[message.second] = (int) clock();
			else
				timeLeft[nextClientID + 1] = (int) clock();
			cout << message.first <<"\n";
		}
		else
		{
			cout << "empty message\n";
		}
	    receivedBytes += bytes_transferred;
	    receivedMessages++;
	}
	else
	{
		cout << "error!" <<"\n";
	}

	start_receive();
}

void NetworkManager::run_service()
{
    start_receive();
    while (!io_service.stopped()){
        try {
            io_service.run();
        } catch( const std::exception& e ) {
            //LogMessage::error("NetworkManager network exception: ",e.what());
        }
        catch(...) {
            //LogMessage::error("Unknown exception in server network thread");
        }
    }
    //LogMessage::Debug("NetworkManager network thread stopped");
};

void NetworkManager::SendToClient(const std::string& message, long long clientID) 
{
    try {
        send(message, clients.left.at(clientID));
    }
    catch (std::out_of_range) {
        //LogMessage::error("Unknown client ID");
    }
}

void NetworkManager::insert_client(boost::asio::ip::udp::endpoint endpoint) {
	nextClientID++;
    clients.insert(Client(nextClientID, endpoint));
}

long long NetworkManager::get_client_id(boost::asio::ip::udp::endpoint endpoint) {
    auto cit = clients.right.find(endpoint);
    if (cit != clients.right.end())
        return (*cit).second;
    return nextClientID;
}

long long NetworkManager::get_client_id(string ip, unsigned short port) {
    boost::asio::ip::udp::resolver resolver(io_service);
	boost::asio::ip::udp::resolver::query query(udp::v4(), ip, boost::lexical_cast< std::string >(port));
	boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
	remote_endpoint = *iterator;
	auto cit = clients.right.find(remote_endpoint);
	if (cit != clients.right.end())
		return cit->second;
	else
		return -1;
}

bool NetworkManager::findClient(string ip, unsigned short port) {
	boost::asio::ip::udp::resolver resolver(io_service);
	boost::asio::ip::udp::resolver::query query(udp::v4(), ip, boost::lexical_cast< std::string >(port));
	boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
	remote_endpoint = *iterator;
	auto cit = clients.right.find(remote_endpoint);
    if (cit != clients.right.end())
    	return true;
    else
    	return false;
}

void NetworkManager::SendToAllExcept(const std::string& message, long long clientID) {
	typedef ClientList::const_iterator it;
	for (it iter = clients.begin(), iend = clients.end(); iter != iend; iter++){
		if (iter->left != clientID)
			SendToClient(message,  iter->left);
	}
}

void NetworkManager::SendToAll(const std::string& message){
	typedef ClientList::const_iterator it;
	for(it iter = clients.begin(), iend = clients.end();  iter != iend; ++iter ) {
		SendToClient(message,iter->left);
	}
}

ClientMessage NetworkManager::popMessage() {
	if(!messages.empty())
		return messages.pop();
	else return make_pair("", -1);

}
std::string NetworkManager::getMyIP() {
	return myIP;
}

unsigned short NetworkManager::getMyPort() {
	return myPort;
}

long long NetworkManager::numberOfClients() {
	return nextClientID;
}
#endif