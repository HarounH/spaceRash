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
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				float temp[16];
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				sendMessage();
				*(myMessage) = msg;
				myMessage->msgType = (int) SETCONNECTDATA;
				btVector3 np(0, 0, 0);
				getNextValidPosition(np);
				btTransform yourTrans;
				yourTrans.setIdentity();
				yourTrans.setOrigin(np);
				yourTrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
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
				btTransform t;
				float temp[16];
				for(int i=0; i<16; ++i) {
					temp[i] = msg.ship.transform[i];
				}
				t.setFromOpenGLMatrix(temp);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(nextClientId, nextPlayerId);
				}

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.000001f);

				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				sendMessage();

				*(myMessage) = msg;
				sendMessage();
			}
			else if(which_spaceObject(client_id) == nullptr) {

				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				newObject->init(bulletWorld);
				btTransform t;
				float temp[16];
				for(int i=0; i<16; ++i) {
					temp[i] = msg.ship.transform[i];
				}
				t.setFromOpenGLMatrix(temp);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(client_id, nextPlayerId);
				}

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.000001f);

				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				sendMessage();

				*(myMessage) = msg;
				sendMessage();
			}
		}
		else if(!hasSetInitialPosition)
		{
			btTransform t;
			float temp[16];
			for(int i=0; i<16; ++i) {
				temp[i] = msg.ship.transform[i];
			}
			t.setFromOpenGLMatrix(temp);
			fighter->getRigidBody()->setWorldTransform(t);
			bulletWorld->dynamicsWorld->stepSimulation(0.00001f);
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