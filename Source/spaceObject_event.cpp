#ifndef SPACE_OBJECT_EVENT_CPP
#define SPACE_OBJECT_EVENT_CPP
#include "spaceObject.hpp"

//TODO: Add a few functions to the spaceObject.hpp
void SpaceObject::initCommunications(State*& state, Message*& msg) {
	state = new State(); //default constructor.
	msg = new Message(); //default message.
}

void SpaceObject::makeMessage(State*& state,  Message*& msg) {
	btTransform myTransform;
	body->getMotionState()->getWorldTransform(myTransform);
	btVector3 lv = body->getLinearVelocity();
	btVector3 av = body->getAngularVelocity();
	state->setData( health, weapons[activeWeapon]->ammo , myTransform , lv ,  av , obj_type);

	msg->setData(
		GENDATA , 
		state ,
		weapons[activeWeapon]
		);
}

void SpaceObject::handleCollision(SpaceObject* other) {
	wasHit = true;
	//---------TODO Need to scale damage down---------//
	btScalar otherMass = other->getRigidBody()->getInvMass();
	if(otherMass==0){
		health/=3;
	}else{
		int damage = other->getRigidBody()->getLinearVelocity().length2()* body->getLinearVelocity().length2() * body->getInvMass() / otherMass;
		health-=damage;
	}
	//cout << "I'm at health=" << health << "\n";
	return;
}

void SpaceObject::toggle_weapon() {
	activeWeapon = (activeWeapon+1)%(weapons.size());
}

void SpaceObject::rotate(double pitch, double yaw) {
	btVector3 localXAxis  = quatRotate(body->getOrientation(),btVector3(1,0,0));
	localXAxis*=mouseScalePitch*pitch;
	body->applyTorque(localXAxis);

	btVector3 localYAxis  = quatRotate(body->getOrientation(),btVector3(0,1,0));
	localYAxis*=mouseScaleYaw*yaw;
	body->applyTorque(localYAxis);
	return;
}

//--------LIMIT ALL TO MAX VELOCITY----------//

//KEYBOARD FUNCTIONS AHEAD!
void SpaceObject::accelerate() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localZAxis  = quatRotate(body->getOrientation(),btVector3(0,0,-1));
	localZAxis*=scalingAcceleration;
	body->applyCentralImpulse(localZAxis);
}
void SpaceObject::decelerate() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localZAxis  = quatRotate(body->getOrientation(),btVector3(0,0,1));
	localZAxis*=scalingAcceleration;
	body->applyCentralImpulse(localZAxis);
}
void SpaceObject::strafe_left() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localXAxis  = quatRotate(body->getOrientation(),btVector3(-1,0,0));
	localXAxis*=scalingAcceleration;
	body->applyCentralImpulse(localXAxis);
}
void SpaceObject::strafe_right() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localXAxis  = quatRotate(body->getOrientation(),btVector3(1,0,0));
	localXAxis*=scalingAcceleration;
	body->applyCentralImpulse(localXAxis);
}
void SpaceObject::ascend() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localYAxis  = quatRotate(body->getOrientation(),btVector3(0,1,0));
	localYAxis*=scalingAcceleration;
	body->applyCentralImpulse(localYAxis);
}
void SpaceObject::descend() {
	if(body->getLinearVelocity().length2()>maxVelocity){
		return;
	}
	btVector3 localYAxis  = quatRotate(body->getOrientation(),btVector3(0,-1,0));
	localYAxis*=scalingAcceleration;
	body->applyCentralImpulse(localYAxis);
}


void SpaceObject::pitch_up() {
	if(body->getAngularVelocity().length2()>maxOmega){
		return;
	}
	btVector3 localXAxis  = quatRotate(body->getOrientation(),btVector3(1,0,0));
	localXAxis*=scalingOmega;
	body->applyTorque(localXAxis);

}
void SpaceObject::pitch_down() {
	if(body->getAngularVelocity().length2()>maxOmega){
		return;
	}
	btVector3 localXAxis  = quatRotate(body->getOrientation(),btVector3(-1,0,0));
	localXAxis*=scalingOmega;
	body->applyTorque(localXAxis);
}
void SpaceObject::yaw_left() {
	if(body->getAngularVelocity().length2()>maxOmega){
		return;
	}
	btVector3 localYAxis  = quatRotate(body->getOrientation(),btVector3(0,1,0));
	localYAxis*=scalingOmega;
	body->applyTorque(localYAxis);
}
void SpaceObject::yaw_right() {
	if(body->getAngularVelocity().length2()>maxOmega){
		return;
	}
	btVector3 localYAxis  = quatRotate(body->getOrientation(),btVector3(0,-1,0));
	localYAxis*=scalingOmega;
	body->applyTorque(localYAxis);
}
void SpaceObject::roll_left() {
	if((body->getAngularVelocity().length2())>(maxOmega*100.0)){
		return;
	}
	btVector3 localZAxis  = quatRotate(body->getOrientation(),btVector3(0,0,1));
	localZAxis*=30.0*scalingOmega;
	body->applyTorque(localZAxis);
}
void SpaceObject::roll_right() {
	if((body->getAngularVelocity().length2())>(maxOmega*100.0)){
		return;
	}
	btVector3 localZAxis  = quatRotate(body->getOrientation(),btVector3(0,0,-1));
	localZAxis*=30.0*scalingOmega;
	body->applyTorque(localZAxis);
}


void SpaceObject::fire_laser() {
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	btVector3 from = trans.getOrigin();
	std::cout << body->getOrientation().getX() << "," << body->getOrientation().getY() << "," << body->getOrientation().getZ() << "," << body->getOrientation().getW() << "\n";
	btVector3 to = from + quatRotate(trans.getRotation() , btVector3(0,0,-500));
		
	//Perform ray test.
	btCollisionWorld::ClosestRayResultCallback rayCallback( from, to );
	world->dynamicsWorld->rayTest(from,to,rayCallback);
	//get results.
	if ( rayCallback.hasHit() ) {
		((SpaceObject*)rayCallback.m_collisionObject->getUserPointer())->hit_by_laser();
		to = ((SpaceObject*)rayCallback.m_collisionObject->getUserPointer())->getRigidBody()->getCenterOfMassPosition();
	} //else, do nothing.
	weapons[activeWeapon] -> fireProjectile(from,to);
}

void SpaceObject::hit_by_laser() {
	std::cout << "i was hit by a laser. ";
}

#endif