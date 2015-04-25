#ifndef PLAYER_HANDLE_CPP
#define PLAYER_HANDLE_CPP
#include "player.hpp"

void Player::handleMessage(Message msg, int network_int) {
	bool deferSetConnect = false;
	//I need, the spaceObject's int-index, the spaceObject's linear velocity, angular velocity, health, ammo and so on.
	if ((msg.msgType & CONNECTDATA) && didStart) {
		//might need to add to list of clients
		if(network->getMyIP() != msg.newConnectorIP) { 
			//check if this client corresponding to this IP and port already exists
			long long client_id = network->get_client_id(msg.newConnectorIP, msg.newConnectorPort);
			if(client_id == -1) { //client is not present in the network. Add him and tell the others.
				//if not found then add to list of clients

				/* Begin addition part. */
				int nextClientId = network->addClient(msg.newConnectorIP, msg.newConnectorPort);
				//add this spaceObject to list of objects
				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				iplist.push_back(make_pair(msg.newConnectorIP, msg.newConnectorPort));

				btVector3 np(0, 0, 0);
				getNextValidPosition(np);
				btTransform yourTrans;
				yourTrans.setIdentity();
				yourTrans.setOrigin(np);

				newObject->init(bulletWorld);
				newObject->getRigidBody()->setWorldTransform(yourTrans);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(nextClientId, nextPlayerId);
					cout << "added.\n";
					addtoNametoP(msg.playerName, nextPlayerId);
				}

				//send this message to everyone else
				// myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				// sendMessageToClient(nextClientId);

				/* Send over your data. */
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				myMessage->playerName = settings->name;
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				float temp[16];
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				cout << "1. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				
				sendMessage();

				/* ^ That part sends my IP address and position to everybody, but is really only meant for the new connector. */

				/* Next part, i tell everyone what the new kid's location should be. */
				*(myMessage) = msg;
				myMessage->msgType = (int) SETCONNECTDATA;
				
				yourTrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);

				sendMessage();

				for(auto it = iplist.begin(); it != iplist.end(); it++)
				{
					long long alreadyExistingID = network->get_client_id(it->first, it->second);
					SpaceObject* correspondingObject = which_spaceObject(alreadyExistingID);
					btTransform correspondingTrans = correspondingObject->getRigidBody()->getWorldTransform();
					float temp2[16];
					correspondingTrans.getOpenGLMatrix(temp2);
					(myMessage->ship).transform.assign(temp2 , temp2 + 15);
					myMessage->setData((int) SETCONNECTDATA, it->first, it->second);
					auto pit = NameToP.right.find(alreadyExistingID);
					if(pit != NameToP.right.end())
						myMessage->playerName = pit->second;
					else
						cout << "Something's not right here\n";
					sendMessage();
				}

				numPlayers--; //TODO : WHY?
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
				iplist.push_back(make_pair(msg.newConnectorIP, msg.newConnectorPort));
				btTransform t;
				float temp[16];
				for(int i=0; i<16; ++i) {
					temp[i] = msg.ship.transform[i];
				}
				t.setFromOpenGLMatrix(temp);

				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					cout << "added.\n";
					addtoNtoP(nextClientId, nextPlayerId);
					addtoNametoP(msg.playerName, nextPlayerId);
				}
				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.0f);
				// myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				// sendMessageToClient(nextClientId);

				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				myMessage->playerName = settings->name;
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				
				sendMessage();

				cout << network->numberOfClients() << "\n";
				cout << "2. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				*(myMessage) = msg;
				
				sendMessage();

				for(auto it = iplist.begin(); it != iplist.end(); it++)
				{
					long long alreadyExistingID = network->get_client_id(it->first, it->second);
					SpaceObject* correspondingObject = which_spaceObject(alreadyExistingID);
					btTransform correspondingTrans = correspondingObject->getRigidBody()->getWorldTransform();
					float temp2[16];
					correspondingTrans.getOpenGLMatrix(temp2);
					(myMessage->ship).transform.assign(temp2 , temp2 + 15);
					myMessage->setData((int) SETCONNECTDATA, it->first, it->second);
					auto pit = NameToP.right.find(alreadyExistingID);
					if(pit != NameToP.right.end())
						myMessage->playerName = pit->second;
					else
						cout << "Something's not right here\n";
					sendMessage();
				}

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
					cout << "added.\n";
					addtoNametoP(msg.playerName, nextPlayerId);
				}

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.0f);
				cout << "3. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				// myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				// sendMessageToClient(client_id);

				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				myMessage->playerName = settings->name;
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				
				sendMessage();

				*(myMessage) = msg;

				sendMessage();
				
				for(auto it = iplist.begin(); it != iplist.end(); it++)
				{
					long long alreadyExistingID = network->get_client_id(it->first, it->second);
					SpaceObject* correspondingObject = which_spaceObject(alreadyExistingID);
					btTransform correspondingTrans = correspondingObject->getRigidBody()->getWorldTransform();
					float temp2[16];
					correspondingTrans.getOpenGLMatrix(temp2);
					(myMessage->ship).transform.assign(temp2 , temp2 + 15);
					myMessage->setData((int) SETCONNECTDATA, it->first, it->second);
					auto pit = NameToP.right.find(alreadyExistingID);
					if(pit != NameToP.right.end())
						myMessage->playerName = pit->second;
					else
						cout << "Something's not right here\n";
					sendMessage();
				}

			}
			// else
			// {
			// 	myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
			// 	sendMessageToClient(network_int);
			// }
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
			bulletWorld->dynamicsWorld->stepSimulation(0.0f);
			hasSetInitialPosition = true;
			cout << "4. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
			// myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
			// sendMessageToClient(network_int);
		}
	}
	
	if (msg.msgType & GENDATA) {
		//get the spaceObject and set its state?
		SpaceObject* obj = which_spaceObject(msg.playerName); //TODO: Change to player name
		if(obj != nullptr)
		{
			obj->setState(msg.ship);			
		}
		else {
			cout << "Not in everyone.\n";
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
					addtoNametoP(msg.playerName, nextPlayerId);
				}

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.0f);

				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				myMessage->playerName = settings->name;
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);

				sendMessage();
				cout << network->numberOfClients() << "\n";
				cout << "2. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";

				*(myMessage) = msg;
				sendMessage();
			}
		}

	}

	if (msg.msgType & LASERDATA) {
		SpaceObject* obj = which_spaceObject(msg.playerName); //TODO: Change to player name
		if(obj != nullptr)
		{
			// obj->setActiveWeapon(msg.wpnType); //cause of segfault.
			btVector3 laserFrom, laserTo;
			msg.getData(laserFrom, laserTo);
			obj->getActiveWeapon()->fireProjectile(laserFrom, laserTo);
			if(msg.hitPlayerName == settings->name)
			{
				fighter->hit_by_laser();
			}
		}
	}

	if(msg.msgType & DIEDATA) {
		SpaceObject* obj = which_spaceObject(msg.playerName); //TODO: Change to player name
		if(obj != nullptr)
		{
			removeFromEveryone(obj);
		}
	}

	if(msg.msgType & WINDATA) {
		SpaceObject* obj = which_spaceObject(msg.playerName); //TODO: Change to player name
		if(obj != nullptr)
		{

		}
	}
}

#endif