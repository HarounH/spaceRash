class Cuboid { //acts as the bounding box for everything.
public:
	Cuboid() {}
	glm::vec3 translate(glm::vec3 displacement); //Translate cuboid
	glm::vec3 rotate(glm::vec3 rotation); //Rotate cuboid
	glm::vec3 scale(glm::vec3 vec_scale);  //Scale cuboid
	// Queries to the cuboid
	bool inside(Position& p);
	bool outside(Position& p);
	bool onsurface(Position& p);
	bool intersects(LineSeg& l);
	bool intersects(Ray& r);
	bool intersects(Line& l);
	bool intersects(Cuboid& cub);
	//Collision handlers
	std::pair<Position,Direction> solveCollision(LineSeg& l);
	std::pair<Position,Direction> solveCollision(Ray& r);
	std::pair<Position,Direction> solveCollision(Line& l);
	std::pair<Position,Direction> solveCollision(Cuboid& cub);
	// Debugging functions: The boolean is to toggle debug mode.
	void dprint(bool debug_cuboid=false);
	void drender(bool debug_cuboid=false);
	// Getters and setters.
	Position getCentre();
	Dimension getDimension();
	Orientation getOrientation();
	void setCentre(Position& _p);
	void setDimension();
	void setOrientation();	
private:
	Position centre;
	Dimension dimensions;
	Orientation orientation;
};