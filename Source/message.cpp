#ifndef MESSAGE_HPP
#define MESSAGE_HPP
using namespace std;

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

#include "helpers.hpp"
State::State() {
	health = 0;
	ammo = 0;
	objType = UFO;
}

State::~State(){}

State::State(State& other) {
	health = other.health;
	ammo = other.ammo;
	transform = other.transform;
	linearVelocity = other.linearVelocity;
	angularVelocity = other.angularVelocity;
	objType = other.objType;
}

State& State::operator= (State& other) {
	health = other.health;
	ammo = other.ammo;
	transform = other.transform;
	linearVelocity = other.linearVelocity;
	angularVelocity = other.angularVelocity;
	objType = other.objType;

	return *this;
}

State::State(int h,int am, btTransform& t, btVector3& lv , btVector3& av, OBJECT_TYPE _t) {
	health = h;
	ammo = am;
	float temp[16];
	t.getOpenGLMatrix(temp);
	transform.assign(temp , temp + 15);

	linearVelocity.push_back(lv.getX());
	linearVelocity.push_back(lv.getY());
	linearVelocity.push_back(lv.getZ());

	angularVelocity.push_back(av.getX());
	angularVelocity.push_back(av.getY());
	angularVelocity.push_back(av.getZ());
	objType = _t;
}

void State::setData(int h,int am, btTransform& t, btVector3& lv , btVector3& av, OBJECT_TYPE& _t) {
	health = h;
	ammo = am;
	float temp[16];
	t.getOpenGLMatrix(temp);
	transform.assign(temp , temp + 15);

	linearVelocity.clear();
	linearVelocity.push_back(lv.getX());
	linearVelocity.push_back(lv.getY());
	linearVelocity.push_back(lv.getZ());

	angularVelocity.clear();
	angularVelocity.push_back(av.getX());
	angularVelocity.push_back(av.getY());
	angularVelocity.push_back(av.getZ());
	objType = _t;
}

void State::getData(int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t) {
	h = health;
	am = ammo;
	float temp[16];
	for(int i=0; i<16; ++i) {
		temp[i] = transform[i];
	}
	t.setFromOpenGLMatrix(temp);
	velo.setX(linearVelocity[0]);
	velo.setY(linearVelocity[1]);
	velo.setZ(linearVelocity[2]);
	avelo.setX(linearVelocity[0]);
	avelo.setY(linearVelocity[1]);
	avelo.setZ(linearVelocity[2]);
	_t = objType;
}

// template<typename Archive>
// void State::serialize(Archive& ar, const unsigned int version) {
// 	ar & health;
// 	ar & transform;
// 	ar & linearVelocity;
// 	ar & angularVelocity;
// 	ar & objType;
// }


Message::Message(int prot , 
	int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
	btVector3& _laserFrom , btVector3& _laserTo , int& _wpnType , 
	std::string ip /*= ""*/ , unsigned short port /*= 0*/, std::string chatmsg /*= ""*/ , std::string worldfile /*= ""*/) : 
    ship(h, am, t, velo, avelo , _t) {
	
	msgType = prot;
	wpnType = _wpnType;
	newConnectorIP = ip;
	newConnectorPort = port;
	chatMessage = chatmsg;

	laserFrom.push_back(_laserFrom.getX());
	laserFrom.push_back(_laserFrom.getY());
	laserFrom.push_back(_laserFrom.getZ());

	laserTo.push_back(_laserTo.getX());
	laserTo.push_back(_laserTo.getY());
	laserTo.push_back(_laserTo.getZ());
	
}

Message::Message() {
	msgType = 0;
}

Message::Message(Message& other) : ship(other.ship) {
	msgType = other.msgType;
	chatMessage = other.chatMessage;
	laserFrom = other.laserFrom;
	laserTo = other.laserTo;
	wpnType = other.wpnType;
	newConnectorIP = other.newConnectorIP;
	newConnectorPort = other.newConnectorPort;
}

Message& Message::operator= (Message& other) {
	ship = other.ship;
	msgType = other.msgType;
	chatMessage = other.chatMessage;
	laserFrom = other.laserFrom;
	laserTo = other.laserTo;
	wpnType = other.wpnType;
	newConnectorIP = other.newConnectorIP;
	newConnectorPort = other.newConnectorPort;

	return *this;
}

void Message::setData(int prot , 
	int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
	btVector3& _laserFrom , btVector3& _laserTo ,int& _wpnType,
	std::string ip /*= ""*/ , unsigned short port /*= 0,*/ , std::string chatmsg /*= ""*/ , std::string worldfile /*= ""*/) {
	
	ship.setData(h, am, t, velo, avelo , _t);
	
	msgType = prot;
	wpnType = _wpnType;
	
	newConnectorIP = ip;
	newConnectorPort = port;
	chatMessage = chatmsg;
	worldData = worldfile;

	laserFrom.clear();
	laserFrom.push_back(_laserFrom.getX());
	laserFrom.push_back(_laserFrom.getY());
	laserFrom.push_back(_laserFrom.getZ());

	laserTo.clear();
	laserTo.push_back(_laserTo.getX());
	laserTo.push_back(_laserTo.getY());
	laserTo.push_back(_laserTo.getZ());
}

void Message::setData(int prot, std::string ip/* = ""*/, unsigned short port /*= 0*/) {
	newConnectorIP = ip;
	newConnectorPort = port;
	msgType = prot;
}

void Message::setData( int prot , State* state , Weapon* wpn ) {
	msgType = prot;
	ship = *state;
	//TODO
	laserFrom.clear();
	laserFrom.push_back(wpn->last_from.getX());
	laserFrom.push_back(wpn->last_from.getY());
	laserFrom.push_back(wpn->last_from.getZ());
	laserTo.clear();
	laserTo.push_back(wpn->last_to.getX());
	laserTo.push_back(wpn->last_to.getY());
	laserTo.push_back(wpn->last_to.getZ());
	return;
}

void Message::getData(btVector3& _laserFrom, btVector3& _laserTo) {
	_laserFrom.setX(laserFrom[0]);
	_laserTo.setX(laserTo[0]);
	_laserFrom.setY(laserFrom[1]);
	_laserTo.setY(laserTo[1]);
	_laserFrom.setZ(laserFrom[2]);
	_laserTo.setZ(laserTo[2]);
}

void Message::getData(int prot , 
	int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
	btVector3& _laserFrom , btVector3& _laserTo ,int& _wpnType,
	std::string& ip, unsigned short port, std::string& chatmsg, std::string& worldfile) {
	
	prot = msgType;
	_wpnType = wpnType;
	
	ip = newConnectorIP;
	port = newConnectorPort;
	
	worldfile = worldData;
	chatmsg = chatMessage;
	
	ship.getData(h, am, t, velo, avelo , _t);

	_laserFrom.setX(laserFrom[0]);
	_laserTo.setX(laserTo[0]);
	_laserFrom.setY(laserFrom[1]);
	_laserTo.setY(laserTo[1]);
	_laserFrom.setZ(laserFrom[2]);
	_laserTo.setZ(laserTo[2]);

}

// template<typename Archive>
// void Message::serialize(Archive& ar, const unsigned int version) {
// 	ar & msgType;
// 	ar & ship;
// 	ar & chatMessage;
// 	ar & laserFrom;
// 	ar & laserTo;
// 	ar & newConnectorIP;
// 	ar & newConnectorPort;
// 	ar & worldData;
// }


#endif