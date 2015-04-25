#ifndef AI_cpp
#define AI_cpp

#include "AI.hpp"

btVector3 position(btRigidBody* body){
	return body->getCenterOfMassPosition(); 
}

double take_root(double val){
	return sqrt(val);
}

double sqr(double val){ return val*val; }

double AI_player::dist_travelled(){
	double dist = speed()*DT;
	return dist;
}

// calculates the distance  between 2 btVectors
double AI_player::dist(btVector3& a, btVector3& b){
	btVector3 c= a - b;
	return take_root((sqr(c.getX())) + (sqr(c.getY())) + (sqr(c.getZ())));
}


// calculates the distance between 2 spaceObjects
double AI_player::dist(SpaceObject* a, SpaceObject* b){
	btVector3 pos_a = position(a->getRigidBody());
	btVector3 pos_b = position(b->getRigidBody());
	if ( !(skyscraper(b) || skyscraper(a)) ) {
		return dist(pos_a, pos_b);
	} else {
		return -1;
	}
}


bool AI_player::gonnaCollideWith(SpaceObject* sky) {
	btCollisionShape* body = sky->getRigidBody()->getCollisionShape();
	for(int i=0; i< ( (btCompoundShape*) body)->getNumChildShapes(); ++i) {
		btCollisionShape* lol = ( (btCompoundShape*) body)->getChildShape(i);
		if ( ( (btBoxShape*) lol)->isInside( fighter->getRigidBody()->getCenterOfMassPosition() + DT*fighter->getRigidBody()->getLinearVelocity(), INSIDENESS_BODY_TOLERANCE )) {
			return true;
		}
	}
	return false;
}

bool AI_player::is_fighter_type(SpaceObject* obj){
	auto typ = obj->getType();
	return (typ == MF || typ == TIE || typ == XWING || typ == UFO);
}

bool AI_player::skyscraper(SpaceObject * obj){
	auto typ = obj->getType();
	return (typ == SKYRISE_TALL || typ == SKYRISE_FAT || typ == ENDPOINT);
}

// speed of my fighter
double AI_player::speed(){
	btVector3 velocity = fighter->getRigidBody()->getLinearVelocity();
	return length(velocity);
}


btVector3 position(SpaceObject* obj){
	return position(obj->getRigidBody());
}

// length of a btVector
double AI_player::length(btVector3& a){
	btVector3 zero(0.0,0.0,0.0);
	return dist(a, zero);
}

// takes in a vector of spaceobjects and populates consider_these with the closest opponent and the closest building,in that order
void AI_player::iterate_thru(boost::bimap< int, SpaceObject* >& others, pair<SpaceObject*, SpaceObject*>& consider_these, SpaceObject* hostFighter){
	double closest_building_dist = 1000000.0;
	double closest_opponent_dist = 1000000.0;
	double _dist;
	int i = 0;
	for(auto i = others.left.begin(); i != others.left.end(); ++i) {
		if(i->second == fighter) {
			continue;
		}
		if(dist(i->second, fighter) <= closest_opponent_dist)
		{

			if (is_fighter_type( (i->second) ))
			{
				i++;
				consider_these.first = (i->second);
				closest_opponent_dist = dist(i->second, fighter);
				cout << "hi\n";
			}
		}

		if(gonnaCollideWith(i->second))
		{
		 	if (skyscraper( (i->second) ) )
			{
				consider_these.second = (i->second);
			}
		}
	}


	if (hostFighter != nullptr && is_fighter_type( hostFighter ) )
	{
		i++;
		if(dist(hostFighter, fighter) <= closest_opponent_dist)
		{
			consider_these.first = (hostFighter);
			closest_opponent_dist = dist(hostFighter, fighter);
			cout << "hi\n";
		}
	}

	cout << "NUMBER OF FIGHTR SHIPS: "  << i << '\n';
}

// mutates state to turn away from this spaceObject by turning towards "delta_vector"
void AI_player::move_away(SpaceObject* obj){
	if (obj == NULL) return; // prevent segfaults.
	btVector3 i_point_at  = quatRotate(fighter->getRigidBody()->getOrientation(),btVector3(0,0,-1));
	btVector3 _x = position(fighter->getRigidBody());
	btVector3 _y = position(obj->getRigidBody());

	btVector3 delta_vector = _x - _y;
	btVector3 neg_delta_vector = -1*delta_vector;
	if (dot(i_point_at, neg_delta_vector) > 0) // move_away only if it has a velocity component towards the space object
		point_at_obj(neg_delta_vector);
}

void AI_player::point_at_obj(SpaceObject* obj){
	if (obj == NULL) return;
	btVector3 here = position(obj);
	point_at_obj(here);
}

void AI_player::point_at_obj(btVector3& a2) {
	btVector3 mpos = position(fighter);
	btVector3 v1 = btVector3(0,0,-1); //quatRotate(fighter->getRigidBody()->getOrientation(),btVector3(0,0,-1));
	btVector3 v2 = a2 - mpos;
	v1 = v1.normalize();
	v2 = v2.normalize();
	btVector3 half = 0.5*(v1+v2) ;
	half=half.normalize();

	btScalar w = btAngle(v1,v2);
	btVector3 a = btCross(v1,v2);
	a = a.normalize();
	// btVector3 a = btCross(v1,v2);
	
	//btScalar w = dot(v1,v2) + take_root(v1.length2() * v2.length2());

	btQuaternion orient(a,w);
	orient = orient.normalize();
	
	btTransform mynewtransform(orient, mpos);
	(fighter->getRigidBody())->setWorldTransform(mynewtransform);
	fighter->getRigidBody()->setAngularVelocity(btVector3(0,0,0));
	
	//world->dynamicsWorld->stepSimulation(0.0001f);
	cout << fighter->getRigidBody()->getAngularVelocity().getX() << "," << fighter->getRigidBody()->getAngularVelocity().getY() << "\n";
	//cout << deltap.getX() << " " << deltap.getY() << " " << deltap.getZ() << " : deltap " << '\n';
	// btQuaternion orient;
	// btVector3 _x(1,0,0), _y(0,1,0), _z(0,0,1);

	// if(deltap.length()==0) return;

	// btScalar x = (180/3.14)*acos((dot( deltap , _x)/(deltap.length())));
	// btScalar y = (180/3.14)*acos((dot( deltap , _y)/(deltap.length())));
	// btScalar z = (180/3.14)*acos((dot( deltap , _z)/(deltap.length())));

	// orient.setEulerZYX(x,y,z);
	
	//TODO: Mabe, i'll need a stepSimulation here.
	//position(obj) - position(fighter) = K*quatRotate(orient, btVector3(0,0,-1));
}

void AI_player::orient_in_direction(SpaceObject* obj){
	btVector3 vect = position(obj->getRigidBody());
	orient_in_direction(vect);
}


// rotates a little towards posVector
void AI_player::orient_in_direction(btVector3& posVector){
	btVector3 i_point_at  = quatRotate(fighter->getRigidBody()->getOrientation(),btVector3(0,0,-1));
	btVector3 _cross =  btCross(i_point_at, posVector);
	double tolerance = 0.001;
	
	fighter->rotate(tolerance*_cross.getX(),tolerance* _cross.getY());
}

// dot product between 2 btVectors
double AI_player::dot(btVector3& a, btVector3& b){
	return ((a.getX()*b.getX()) + (a.getY()*b.getY()) + (a.getZ()*b.getZ()) );
}

// checks if AI is right in front of obj, given some tolerance. needs to be double checked
bool AI_player::right_in_front(SpaceObject* obj){

	btVector3 _x = position(fighter->getRigidBody());

	btVector3 _y = position(obj->getRigidBody());

	btVector3 _z = _y - _x;   // Subtracting 2 btVectors
	btVector3 i_point_at  = quatRotate(fighter->getRigidBody()->getOrientation(),btVector3(0,0,-1));

	if ( dot(i_point_at,_z) > TOLERANCE* length(i_point_at)* length(_z) ) {
		return true;
	}


	return false;

}

// mutates state to move in the direction of the goal;
// TODO
void AI_player::move_towards_goal(){
	fighter->accelerate();
}

// randomly changes its weapon with a small probability
void AI_player::random_weapon_toggle(){
	int coin_toss = rand() % 5;

	if (!coin_toss)
		fighter->toggle_weapon();
}

AI_player::AI_player(SpaceObject* f, BulletWorld* w, btVector3& c, string _name): fighter(f), world(w) {
	// need a method to initialize state, fighter,

	myName = _name;
	unsigned int time_ui = (unsigned int) time(NULL);
	srand( time_ui );
	myMessage = new Message();
	myMessage->playerName = myName;
}



// takes an action,given bimap EveryOne and the network manager nm
void AI_player::take_action(boost::bimap< int, SpaceObject* >& EveryOne, NetworkManager* nm, SpaceObject* hostFighter) {
	double coin_toss = rand()%2;
	random_weapon_toggle();  // randomly toggle weapon


	pair<SpaceObject*, SpaceObject*> consider_these;
	consider_these.first = NULL;
	consider_these.second = NULL;
	cout << boolalpha << (hostFighter == NULL) << " : IF THIS IS true I'm fucked" << '\n';
	iterate_thru(EveryOne, consider_these, hostFighter);  // iterate thru the bimap and compute the closest building and the closest spaceship
	

	coin_toss = rand()%2;


	// if (consider_these.second != NULL && coin_toss)	// if AI is extremely close to the closest building
	// {	
		
	// 	// then move away from this building with probability 1/2
	// 	fighter->decelerate();
	// 	move_away(consider_these.second);
	// 	cout << "considered building\n";
	// }

	// else 
	// if (consider_these.first != NULL && coin_toss) // if AI is extremely close to the closest ship
	// {
	// 	cout << boolalpha << (consider_these.first == hostFighter) << " : should be true"  << '\n';
	// 	// then move away from this ship with probability 1/2
	// 	fighter->decelerate();
	// 	move_away(consider_these.first);
	// 	cout << "considered ship\n";
	// }

	
	
	if(consider_these.first != NULL )
	{
		cout << boolalpha << (consider_these.first == hostFighter) <<  " : should be true"  << '\n';
		bool front_of_ship = right_in_front(consider_these.first);	
		cout << "POINTING AT\n";
		cout << "Orientationb4:" << fighter->getRigidBody()->getOrientation().getX() << "," << fighter->getRigidBody()->getOrientation().getY()<< "," << fighter->getRigidBody()->getOrientation().getZ() << "," << fighter->getRigidBody()->getOrientation().getW()<<")\n";
		point_at_obj(consider_these.first);
		cout << "Orientationb4:" << fighter->getRigidBody()->getOrientation().getX() << "," << fighter->getRigidBody()->getOrientation().getY()<< "," << fighter->getRigidBody()->getOrientation().getZ() << "," << fighter->getRigidBody()->getOrientation().getW()<<")\n";
		if (front_of_ship) {
			fighter->fire_laser();
		}
		else if (coin_toss)
		{

		}
	}	
		// now move towards the goal
	move_towards_goal();
	

	// make a message out of this new state
	
	if (myMessage != NULL)
		{fighter->getState(myMessage->ship);}

	if (myMessage == NULL) cout << "fked" << '\n';
	myMessage->msgType = (int) GENDATA;
	// now serialize this message and send it to everyone

	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << (*myMessage);
	std::string message = archive_stream.str();
	nm->SendToAll(message);


}

#endif