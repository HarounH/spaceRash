#ifndef AI_HPP
#define AI_HPP


#include <ctime>
#include <cmath>
#include "helpers.hpp"
#include "spaceObject.hpp"
#include "networkManager.hpp"


#define TOLERANCE 0.95
#define DT 0.001
#define INSIDENESS_BODY_TOLERANCE 0.1



class AI_player{

private:
	OBJECT_TYPE fighterType;
	SpaceObject* fighter;
	BulletWorld* world;
	Message* myMessage;
	string myName;

	// distance travelled in DT by my fighter
	double dist_travelled();

	// calculates the distance  between 2 btVectors
	double dist(btVector3& a, btVector3& b);


	// calculates the distance between 2 spaceObjects
	double dist(SpaceObject* a, SpaceObject* b);

	bool gonnaCollideWith(SpaceObject* sky);

	bool is_fighter_type(SpaceObject* obj);

	bool skyscraper(SpaceObject * obj);

	// speed of my fighter
	double speed();

	// length of a btVector
	double length(btVector3& a);
	
	// takes in a vector of spaceobjects and populates consider_these with the closest opponent and the closest building,in that order
	void iterate_thru(boost::bimap< int, SpaceObject* >& others, pair<SpaceObject*, SpaceObject*>& consider_these,  SpaceObject* hostFighter = nullptr);

	// mutates state to turn away from this spaceObject by turning towards "delta_vector"
	void move_away(SpaceObject* obj);

	void orient_in_direction(SpaceObject* obj);


	// rotates a little towards posVector
	void orient_in_direction(btVector3& posVector);

	// dot product between 2 btVectors
	double dot(btVector3& a, btVector3& b);

	// checks if AI is right in front of obj, given some tolerance. needs to be double checked
	bool right_in_front(SpaceObject* obj);

	// mutates state to move in the direction of the goal;
	// TODO
	void move_towards_goal();

	// randomly changes its weapon with a small probability
	void random_weapon_toggle();


	void point_at_obj(SpaceObject*);
	void  point_at_obj(btVector3&);
public:

	AI_player(SpaceObject*, BulletWorld*, btVector3&, string);



	// takes an action,given bimap EveryOne and the network manager nm
	void take_action(boost::bimap< int, SpaceObject* >& EveryOne, NetworkManager* nm, SpaceObject* hostFighter = nullptr);

};

#endif
