#ifndef SPACE_OBJECT_CPP
#define SPACE_OBJECT_CPP

#include "spaceObject.h"

Position SpaceObject::getPosition() {
	return com;
}
Quat SpaceObject::getQuatRot();
Velocity getVelocity();
Acceleration getAcceleration();
void setPosition(Position& p);
void setQuatRot(glm::vec3 _ea);
void setQuatRot(Quat& _q);
void setVelocity(Velocity& _v);
void setAcceleration(Acceleration& _acc);

#endif