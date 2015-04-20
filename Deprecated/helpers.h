#ifndef HELPERS_H
#define HELPERS_H

#include <vector>

/**
library includes.
*/
#include <boost/config.hpp>
#include <boost/bimap.hpp>
#include <GL/glut.h> //do we want to use sdl?

/** Pedagogical. Why? we shall use the fourth dimension correctly. For a point, w=1, for a direction(read: velocity, acc) , w=0. */

/** math/physics typedefs */
typedef double Mass;
typedef glm::quat Quat; // QUATERNIONS!
typedef  glm::vec4 Dimension; //w=0
typedef  glm::vec4 Orientation; //w=0 //Unused
typedef  glm::vec4 Position; //w=1
typedef  glm::vec4 Direction; //w=0
typedef  glm::vec4 Velocity; //w=0
typedef  glm::vec4 Acceleration; //w=0


/** rendering typedefs */
typedef std::vector<int> Face; //this uses a vector of "ints" because thats how objects are loaded.  you dont pass a vertex for each face. you just pass the index of the vertex.

// //i want to print glm stuff.
// #include <glm/gtx/string_cast.hpp>
// template<typename genType>
// std::ostream& operator<<(std::ostream& out, const genType& g)
// {
//     return out << glm::to_string(g);
// }

#include <tuple>
/** networking typedefs */
typedef std::tuple< int,int,int,int > tIP4;
typedef int Time ; //discretized?

/** file typedef. readability. */
typedef std::string OBJFilepath;


/** Geometry */
/** A class for line segments */
enum AXIS { X=1, Y=2, Z=3 };

class LineSeg {
public:
	Position start,end;
};
/** A class for infinite rays. */
class Ray { 
public:
	Position start ; 
	Direction direction;
};
/** A class for complete lines. Should be absolutely useless. */
class Line {
public:
	Position start; //Every line must pass through a point. 
	Direction direction; //Extends in both directions. 
};

/** communication protocols. */
enum OBJECT_TYPE {
	ASTEROID = 0,
	
	HEALTH = 1,
	AMMO = 2,
	
	XWING = 3,
	TIE = 4,
	MF = 5
};

/** Message_type is the protocol within the network manager. */
enum MESSAGE_PROTOCOL { GENDATA=0 , //use these messages as an internal protocol.
					LASERDATA=1,
					COLLISIONDATA=2,
					CHATDATA=3,
					CONNECTDATA=4,
					PINGDATA=5
};

/** enum Event Type is the protocol between NetworkManager and Player */
enum PLAYER_PROTOCOL { //push these messages into the player's queue.
	GENDATA_P=0 , 
	LASERDATA_P=1,
	COLLISIONDATA_P=2,
	CHATDATA_P=3,
	CONNECTDATA_P=4,
	DROPDATA_P=5
};

/** Intra-player helper functions */

/** PlayerInfo is used by the network for initializing player*/
struct PlayerInfo {
	std::string playerName;
	tIP4 ipAddress;
	Time lastMessageTime;
	OBJECT_TYPE objtype; //Communicated this to the player, maybe?
	//TODO: Aux data.
};


/** game state. */
class SpaceObject; //forward declaration.
struct WorldState {
	//needs to contain a lot of stuff.
	vector<PlayerInfo> playerInfo;
	vector<SpaceObject> objectsInSpace;
};

/** event */
struct GameEvent {
	PLAYER_PROTOCOL eventType;
	//TODO: +Aux data.
};


/** event handlers */
enum KeyboardInput {};
typedef boost::bimap<int,KeyboardInput> KeyboardMapping;
typedef KeyboardMapping::value_type keymap_type;

//class user settings. 
class UserSettings {
public:
	/* Sensitivity and stuff. */
	glm::vec3 mouseSensitivity;	   //Along x,y,z.
	KeyboardMapping keyboardMapping;
	void read_settings(); //Read from setting files.
	void save_settings(); //Save to setting files
};

#endif