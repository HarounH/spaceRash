#ifndef SPACE_OBJECT_CPP
#define SPACE_OBJECT_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#include "cuboid.h"

/** This is the mother of all things. All ships, asteroids etc derive from this. */


class SpaceObject {
public:
	/** Each space object is a collection of Cuboids. Ideally, the Collection would be a vector<Cuboid> */	

	/** Creation/Loading */
	SpaceObject() {}
	~SpaceObject() {}
	void init(OBJECT_TYPE _objtype);

	/** get/sets */
	Position getPosition();
	Quat getQuatRot();
	Velocity getVelocity();
	Acceleration getAcceleration();
	void setPosition(Position& p);
	void setQuatRot(glm::vec3 _ea);
	void setQuatRot(Quat& _q);
	void setVelocity(Velocity& _v);
	void setAcceleration(Acceleration& _acc);

	/** rendering things. */
	bool loadOBJ();
	bool renderOBJ();

	/** Queries. */
	bool inside(Position& p);
	bool outside(Position& p);
	bool onsurface(Position& p);
	bool intersects(LineSeg& l);
	bool intersects(Ray& r);
	bool intersects(Line& l);
	bool intersects(Cuboid& cub);
	
	bool intersects(SpaceObject& spaceobj);
	/***/
	
	/** Updates */
	glm::vec3 translate(glm::vec3 displacement); //Returns the new position of the centre.
	glm::vec3 rotate(glm::vec3 rotation); 		 //Should it return the rotation matrix?
	glm::vec3 scale(glm::vec3 vec_scale); 		 //Scale along each directions.
	
	/** Debugging tools. */
	void dprint(bool debug_spaceobj=false);
	void drender(bool debug_spaceobj=false);
private:
	/** Rendering part of things.*/
	//The body is composed of vertices. we must read them into vectors so that we may draw them.
	std::vector<Position> object_vertices;
	std::vector<Direction> object_normals;
	std::vector< glm::vec4 > object_tVertices;
	std::vector<Face> object_faces;


	/** physics part of things. */
	std::vector<Cuboid> pieces; //Do we need a better data-structure? If we were using more complicated shapes, we'd use a AABBTree. 
	
	OBJFilepath objFile; /* Different space ships */
	OBJECT_TYPE objType;
	/** Physics and rendering stuff. */
	
	Mass mass;

	Position com;
	//translational
	Velocity v;
	Acceleration a;
	//rotational.
	Velocity rotv; //rotation velocity.
	Acceleration rota; //rotation acceleration.
	Quat quatRot;
	glm::mat4 matRotation, matTranslation, matScale;
};

#endif