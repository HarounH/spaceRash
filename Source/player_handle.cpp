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
			if(client_id == -1) {
				//if not found then add to list of clients
				int nextClientId = network->addClient(msg.newConnectorIP, msg.newConnectorPort);
				//add this spaceObject to list of objects
				SpaceObject *newObject = new SpaceObject(msg.ship.objType);
				newObject->init(bulletWorld);
				if( add_object(newObject) ) {
					int nextPlayerId = getID(newObject);
					addtoNtoP(nextClientId, nextPlayerId);
					cout << "added.\n";
					addtoNametoP(msg.playerName, nextPlayerId);
				}
				//send this message to everyone else
				for(int i = 1; i < 4; i++)
					sendMessage(string("connectDummy"));

				myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				sendMessageToClient(network_int);

				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				float temp[16];
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				cout << "1. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				bool flag = false;
				while(!flag)
				{
					flag = true;
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = false;
							break;
						}
					}
					usleep(15000);
				}
				*(myMessage) = msg;
				myMessage->msgType = (int) SETCONNECTDATA;
				myMessage->playerName = settings->name;
				btVector3 np(0, 0, 0);
				getNextValidPosition(np);
				btTransform yourTrans;
				yourTrans.setIdentity();
				yourTrans.setOrigin(np);
				yourTrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				flag = false;
				while(!flag)
				{
					flag = true;
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = false;
							break;
						}
					}
					usleep(15000);
				}
				numPlayers--;
				deferSetConnect = true;
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
					cout << "added.\n";
					addtoNtoP(nextClientId, nextPlayerId);
					addtoNametoP(msg.playerName, nextPlayerId);
				}
				for(int i = 1; i < 4; i++)
					sendMessage(string("connectDummy"));

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.000001f);
				myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				sendMessageToClient(network_int);

				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				myMessage->playerName = settings->name;
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				bool flag = false;
				while(!flag)
				{
					flag = true;
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = false;
							break;
						}
					}
					usleep(15000);
				}
				cout << network->numberOfClients() << "\n";
				cout << "2. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				*(myMessage) = msg;
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				flag = false;
				while(!flag)
				{
					flag = true;
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = false;
							break;
						}
					}
					usleep(15000);
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
				for(int i = 1; i < 4; i++)
					sendMessage(string("connectDummy"));

				newObject->getRigidBody()->setWorldTransform(t);
				bulletWorld->dynamicsWorld->stepSimulation(0.000001f);
				cout << "3. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
				myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				sendMessageToClient(network_int);

				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				myMessage->playerName = settings->name;
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				bool flag = false;
				while(!flag)
				{
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = true;
							break;
						}
					}
					usleep(15000);
				}

				*(myMessage) = msg;
				confirmed.resize(network->numberOfClients(), false);
				for(int i = 0; i < (int)confirmed.size(); i++)
					confirmed[i] = false;
				flag = false;
				while(!flag)
				{
					flag = true;
					sendMessage();
					receiveMessage();
					for(int i = 0; i < (int)confirmed.size(); i++)
					{
						if(confirmed[i] == false)
						{
							flag = false;
							break;
						}
					}
					usleep(15000);
				}
			}
			else
			{
				myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
				sendMessageToClient(network_int);
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
			cout << "4. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";
			myMessage->setData((int) CONFIRMDATA, network->getMyIP(), network->getMyPort());
			sendMessageToClient(network_int);
		}
	}

	if((msg.msgType & CONFIRMDATA) && network_int != -1)
		confirmed[network_int - 1] = true;
	
	if (msg.msgType & GENDATA) {
		//get the spaceObject and set its state?
		SpaceObject* obj = which_spaceObject(network_int);
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
				bulletWorld->dynamicsWorld->stepSimulation(0.000001f);

				//send this message to everyone else
				myMessage->setData((int) SETCONNECTDATA, network->getMyIP(), network->getMyPort());
				btTransform mytrans = fighter->getRigidBody()->getWorldTransform();
				myMessage->playerName = settings->name;
				mytrans.getOpenGLMatrix(temp);
				(myMessage->ship).transform.assign(temp , temp + 15);

				usleep(20000);
				sendMessage();
				cout << network->numberOfClients() << "\n";
				cout << "2. " << msg.newConnectorIP << " " << msg.newConnectorPort << "\n";

				*(myMessage) = msg;
				usleep(20000);
				sendMessage();
			}
		}

	}

	// if (msg.msgType & LASERDATA) {
	// 	SpaceObject* obj = which_spaceObject(network_int);
	// 	if(obj != nullptr)
	// 	{
	// 		obj->setActiveWeapon(msg.wpnType);
	// 		btVector3 laserFrom, laserTo;
	// 		msg.getData(laserFrom, laserTo);
	// 		obj->getActiveWeapon()->fireProjectile(laserFrom, laserTo);
	// 		if(msg.hitPlayerName == settings->name)
	// 		{
	// 			fighter->hit_by_laser();
	// 		}
	// 	}
		
	// }
}

#endif