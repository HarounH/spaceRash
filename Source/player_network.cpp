#ifndef NETWORK_INTEGRATION_CPP
#define NETWORK_INTEGRATION_CPP

#include "networkManager.hpp"
#include "helpers.hpp"
#include "player.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

void Player::setGameMode(std::string myip, unsigned short myport , bool startmode, std::string otherip, unsigned short otherport, int _numPlayers, int _numAIs) {
	if(startmode)
	{
		startNetwork(myip, myport);
		numPlayers = _numPlayers;
		numAIs = _numAIs;
		didStart = true;
	}
	else
	{
		connectToNetwork(otherip, otherport, myip, myport);
		didStart = false;
	}
}

void Player::startNetwork(string local_ip, unsigned short local_port) {
	network = new NetworkManager(local_ip, local_port);
}

void Player::connectToNetwork(string IP, unsigned short server_port, string local_ip, unsigned short local_port) {
	network = new NetworkManager(IP, server_port, local_ip, local_port);
	sendMessage(string("connectDummy"));
	myMessage->setData((int)CONNECTDATA, local_ip, local_port);
	myMessage->ship.objType = fighter->getType();
	myMessage->playerName = settings->name;
	sendMessage();
}

void Player::setGeneralData() {
	fighter->getState(myMessage->ship);
	myMessage->msgType = (int) GENDATA;
	myMessage->newConnectorIP = network->getMyIP();
	myMessage->newConnectorPort = network->getMyPort();
	myMessage->playerName = settings->name;
	if(fighter->didFire())
	{
		myMessage->msgType = myMessage->msgType | ((int) LASERDATA);
		myMessage->wpnType = fighter->getType();
		btVector3 to = fighter->laser_to();
		btVector3 from = fighter->laser_from();
		myMessage->setData(from, to);
		if(fighter->didHit())
		{
			SpaceObject* hitShip = fighter->getHitShip();
			myMessage->hitPlayerName = which_player_name(hitShip);
			fighter->didHit(false);
		}
		fighter->didFire(false);
	}
	sendMessage();
}

void Player::sendMessage(std::string message) {
	network->SendToAll(message);
}

void Player::sendMessage() {
	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << (*myMessage);
	std::string message = archive_stream.str();
	network->SendToAll(message);
}

void Player::sendMessageToClient(long long client_id) {
	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << (*myMessage);
	std::string message = archive_stream.str();
	network->SendToClient(message, client_id);
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
	if(inMessage.first == "go")
		startGame = true;
	else if(inMessage.first == "connectDummy")
		return;
	else if(inMessage.first != "")
		translateMessage(inMessage);
}
#endif