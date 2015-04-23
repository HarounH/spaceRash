#ifndef SPACE_OBJECT_HPP
#define SPACE_OBJECT_HPP
/* bullets! */
#include <btBulletDynamicsCommon.h>
#include "helpers.hpp"
#include "obj_Loader.hpp"
/**
	What follows are the file paths and so on.
*/

class SpaceObject {
public:
	/* constructors */
	SpaceObject(OBJECT_TYPE _type);
	~SpaceObject();

	/** functions for loading, etc. */
	void 	init(BulletWorld* _world);
	void 	physics_init();
	void 	readPhysicsFile();
	void 	createCompoundShape();
	void 	render_init();

	void 	loadRenderGeometry(/*objpath*/);
		//void render_geometry(); declared in the rendering section.

	/* for debugging, if done. */
	void 	print(bool debug_flag = false);
	
	/* for rendering into opengl around the centre itself. */
	void 	render(bool debuf_flag = false);
	void 	render_geometry();
	void 	render_physics(bool dflag = false);
	void 	handleCollision(SpaceObject* other);
	std::vector<pair<btVector3 , btVector3> > cameras; //TODO : Make it private.
	OBJECT_TYPE getType();
	void 	setType(OBJECT_TYPE _type);

	int 	getHealth();
	void 	setHealth(int h);
	void 	getTrans(float* mat);
	Weapon* 	getActiveWeapon();
	void 	setActiveWeapon(int w);

	btRigidBody* getRigidBody();
	void 	drawBox(btVector3&);

	//functions to get the state and stuff.
	void 	initCommunications(State*&, Message*&);
	void 	makeMessage(State*& , Message*&); //generates default message, with health, weapons, positions and everything else. etc.
	void 	setState(State&);
	void 	getState(State&);
	void 	setRenderModel(ObjLoader* _myobj);
	/* actions that the spaceobject can do .*/
	void fire_laser();
	void hit_by_laser();

	/* physics things that we must implement using quaternions and the sort. */
	void accelerate();
	void decelerate();
	void strafe_left();
	void strafe_right();
	void ascend();
	void descend();
	void pitch_up();
	void pitch_down();
	void yaw_left();
	void yaw_right();
	void roll_left();
	void roll_right();
	void toggle_weapon();

	void rotate(double pitch, double yaw);
	void setPosition(btVector3 vec);
	void setStatic(); //sets a bodies' mass to 0 IF it is of a certain type.
private:
	/* misc data */
	OBJECT_TYPE obj_type;
	std::string objpath;
	std::string phypath;
	int health;
	bool wasHit;
	btScalar maxVelocity;
	btScalar scalingAcceleration;
	btScalar scalingOmega;
	btScalar maxOmega;
	btScalar linearDamping;
	btScalar mouseScalePitch;
	btScalar mouseScaleYaw;
	btScalar angularDamping;
	std::vector<Weapon*> weapons;
	int activeWeapon;
	/*physics*/
	btScalar mass;
	std::vector<btTransform> childTransform;
	std::vector<btCollisionShape*> children;
	btCompoundShape* shape;
	btDefaultMotionState* dms; //default motion state.
	btVector3 moment_inertia;
	btRigidBody* body;
	BulletWorld* world;
	/*render*/
	ObjLoader* m_Obj;
};

#endif