#ifndef SPACE_OBJECT_GET_SETS_CPP
#define SPACE_OBJECT_GET_SETS_CPP

#include "spaceObject.hpp"

btRigidBody* SpaceObject::getRigidBody() {
	return body;
}

int SpaceObject::getHealth() {
	return health;
}

void SpaceObject::setHealth(int _h) {
	health = _h;
}

Weapon* SpaceObject::getActiveWeapon() {
	return weapons[activeWeapon];
}

void SpaceObject::setActiveWeapon(int w) {
	activeWeapon = w;
}

OBJECT_TYPE SpaceObject::getType() {
	return obj_type;
}

void SpaceObject::setType(OBJECT_TYPE _type) {
	obj_type = _type;
	return;
}

void SpaceObject::getTrans(float* mat) {
	btTransform trans_com;
	body->getMotionState()->getWorldTransform(trans_com);
	trans_com.getOpenGLMatrix(mat);
}

void SpaceObject::setPosition(btVector3 vec) {
	bool actstate = body->isActive();
	body->activate(true);
	btTransform trans = body->getCenterOfMassTransform();
	trans.setOrigin(vec);
	body->setCenterOfMassTransform(trans);
	body->activate(actstate);
}
#endif