#ifndef PLAYER_HANDLE_CPP
#define PLAYER_HANDLE_CPP
#include "player.hpp"

void Player::handleMessage(Message msg, int network_int) {
	//I need, the spaceObject's int-index, the spaceObject's linear velocity, angular velocity, health, ammo and so on.
	if ((msg.msgType & CONNECTDATA) && didStart) {
		//might need to add to list of clients
		if(network->getMyIP() != msg.newConnectorIP) { 
			//check if this client corresponding to this IP and port already exists
			long long client_id = network->get_client_id(msg.newConnectorIP, msg.newConnectorPort);
			if(client_id == -1) {
				//if not found then add to list of clients
				int nextClientId = network->addClient(msg.newConnectorIP, msg.newConnectorPort);
				//add this spaceObject to list of objects
				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				newObject->init(bulletWorld);
				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(nextClientId, nextPlayerId);
				}
				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btVector3 mylv = fighter->getRigidBody()->getCenterOfMassPosition();
				(myMessage->ship).linearVelocity.clear();
				(myMessage->ship).linearVelocity.push_back(mylv.getX());
				(myMessage->ship).linearVelocity.push_back(mylv.getY());
				(myMessage->ship).linearVelocity.push_back(mylv.getZ());
				sendMessage();
				*(myMessage) = msg;
				btVector3 lv(0, 0, 0);
				getNextValidPosition(lv);
				(myMessage->ship).linearVelocity.clear();
				(myMessage->ship).linearVelocity.push_back(lv.getX());
				(myMessage->ship).linearVelocity.push_back(lv.getY());
				(myMessage->ship).linearVelocity.push_back(lv.getZ());
				sendMessage();
				numPlayers--;
			}
		}
	}
	
	if ((msg.msgType & SETCONNECTDATA) && !didStart) {
		if(network->getMyIP() != msg.newConnectorIP) { 
			//check if this client corresponding to this IP and port already exists
			long long client_id = network->get_client_id(msg.newConnectorIP, msg.newConnectorPort);
			if(client_id == -1) {
				//if not found then add to list of clients
				int nextClientId = network->addClient(msg.newConnectorIP, msg.newConnectorPort);
				//add this spaceObject to list of objects
				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				newObject->init(bulletWorld);
				btVector3 newPos;
				newPos.setX(msg.ship.linearVelocity[0]);
				newPos.setY(msg.ship.linearVelocity[1]);
				newPos.setZ(msg.ship.linearVelocity[2]);
				newObject->getRigidBody()->translate(newPos);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(nextClientId, nextPlayerId);
				}
				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btVector3 mylv = fighter->getRigidBody()->getCenterOfMassPosition();
				(myMessage->ship).linearVelocity.clear();
				(myMessage->ship).linearVelocity.push_back(mylv.getX());
				(myMessage->ship).linearVelocity.push_back(mylv.getY());
				(myMessage->ship).linearVelocity.push_back(mylv.getZ());
				sendMessage();
				*(myMessage) = msg;
				sendMessage();
			}
			else if(which_spaceObject(client_id) == nullptr) {
				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				newObject->init(bulletWorld);
				btVector3 newPos;
				newPos.setX(msg.ship.linearVelocity[0]);
				newPos.setY(msg.ship.linearVelocity[1]);
				newPos.setZ(msg.ship.linearVelocity[2]);
				newObject->getRigidBody()->translate(newPos);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(client_id, nextPlayerId);
				}
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btVector3 mylv = fighter->getRigidBody()->getCenterOfMassPosition();
				(myMessage->ship).linearVelocity.clear();
				(myMessage->ship).linearVelocity.push_back(mylv.getX());
				(myMessage->ship).linearVelocity.push_back(mylv.getY());
				(myMessage->ship).linearVelocity.push_back(mylv.getZ());
				sendMessage();
				myMessage = &msg;
				sendMessage();
			}
		}
		else if(!hasSetInitialPosition)
		{
			btVector3 newPos;
			newPos.setX(msg.ship.linearVelocity[0]);
			newPos.setY(msg.ship.linearVelocity[1]);
			newPos.setZ(msg.ship.linearVelocity[2]);
			fighter->getRigidBody()->translate(newPos);
			hasSetInitialPosition = true;
		}
	}
	
	if (msg.msgType & GENDATA) {
		//get the spaceObject and set its state?
		SpaceObject* obj = which_spaceObject(network_int);
		if(obj != nullptr)
		{
			obj->setState(msg.ship);			
		}
	}

	if (msg.msgType & LASERDATA) {
		SpaceObject* obj = which_spaceObject(network_int);
		if(obj != nullptr)
		{
			obj->setActiveWeapon(msg.wpnType);
			btVector3 laserFrom, laserTo;
			msg.getData(laserFrom, laserTo);
			obj->getActiveWeapon()->fireProjectile(laserFrom, laserTo);
		}
	}
}

#endif