#ifndef PLAYER_GET_SET_CPP
#define PLAYER_GET_SET_CPP
#include "player.hpp"

BulletWorld* Player::getBulletWorld() { return bulletWorld; }
void Player::setFighterType(OBJECT_TYPE _type) { fighterType = _type;}
OBJECT_TYPE Player::getFighterType() { return fighterType; }
SpaceObject* Player::getFighter() { return fighter; }
SpaceObject* Player::getSpaceObject(int ID){
	auto objectitr = EveryOne.left.find(ID);
	if(objectitr != EveryOne.left.end())
		return objectitr->second;
	else
		return nullptr;
}
int Player::getID(SpaceObject* spaceObject){
	int temporary = -1;
	try{
		temporary = EveryOne.right.at(spaceObject);
	}catch(std::out_of_range & e ){
		return -1;
	}
	return temporary;	
}

UserSettings* Player::getSettings() {
	return settings;
}
void Player::getWindowSize(double &x,double &y){
	x = halfWindowSizeX ;
	y = halfWindowSizeY;
}
#endif