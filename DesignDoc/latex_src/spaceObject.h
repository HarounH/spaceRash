class SpaceObject {
public:
	SpaceObject() {}
	void init(OBJECT_TYPE _objtype); //Creation Loading
	//Getters/Setters
	Position getPosition();
	Orientation getOrientation();
	Velocity getVelocity();
	Acceleration getAcceleration();
	void setPosition(Position& p);
	void setOrientaiton(Orientation& _o);
	void setVelocity(Velocity& _v);
	void setAcceleration(Acceleration& _acc);
	//Rendering functions
	void loadOBJ();
	void renderOBJ();
	//Queries
	bool inside(Position& p);
	bool outside(Position& p);
	bool onsurface(Position& p);
	bool intersects(LineSeg& l);
	bool intersects(Ray& r);
	bool intersects(Line& l);
	bool intersects(Cuboid& cub);
	bool intersects(SpaceObject& spaceobj);
	//Movement
	glm::vec3 translate(glm::vec3 displacement); //Translate object
	glm::vec3 rotate(glm::vec3 rotation); //Rotate object
	glm::vec3 scale(glm::vec3 vec_scale); //Scale object
	// Debugging functions: The boolean is to toggle debug mode.
	void dprint(bool debug_spaceobj=false);
	void drender(bool debug_spaceobj=false);
private:
	std::vector<Cuboid> pieces;
	OBJFilepath objFile;
	OBJECT_TYPE objType;
	//Properties
	Mass mass;
	Position com;
	Orientation o;
	Velocity v;
	Acceleration a;
};