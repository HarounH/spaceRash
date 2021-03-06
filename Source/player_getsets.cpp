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

	auto objectitr = EveryOne.right.find(spaceObject);
	if(objectitr != EveryOne.right.end())
		return objectitr->second;
	else
		return -1;
}

UserSettings* Player::getSettings() {
	return settings;
}
void Player::getWindowSize(double &x,double &y){
	x = halfWindowSizeX ;
	y = halfWindowSizeY;
}

bool Player::getIsDead() {
	return isDead;
}

bool Player::getHasReachedGoal() {
	btVector3 check = fighter->getRigidBody()->getCenterOfMassPosition();
	check.setY(0);
	if ( (check-goalPos).length2() < 2500 ){
		return true;
	} else {
		return false;
	}
}
#endif