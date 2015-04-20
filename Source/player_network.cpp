#ifndef NETWORK_INTEGRATION_CPP
#define NETWORK_INTEGRATION_CPP

#include "networkManager.hpp"
#include "helpers.hpp"
#include "player.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

void Player::startNetwork(string local_ip, unsigned short local_port) {
	network = new NetworkManager(local_ip, local_port);
}

void Player::connectToNetwork(string IP, unsigned short server_port, string local_ip, unsigned short local_port) {
	network = new NetworkManager(IP, server_port, local_ip, local_port);
	myMessage->setData((int)CONNECTDATA, network->getMyIP(), network->getMyPort());
	sendMessage();
}

void Player::setGeneralData() {
	fighter->getState(myMessage->ship);
	sendMessage();
}

void Player::sendMessage() {
	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << (*myMessage);
	std::string message = archive_stream.str();
	network->SendToAll(message);
}

void Player::translateMessage(ClientMessage inMessage) {
	Message message;
	std::istringstream archive_stream(inMessage.first);
	boost::archive::text_iarchive archive(archive_stream);
	archive >> message;
	handleMessage(message, inMessage.second);
}

void Player::receiveMessage() {
	ClientMessage inMessage = network->popMessage();
	if(inMessage.first != "")
		translateMessage(inMessage);
}

#endif