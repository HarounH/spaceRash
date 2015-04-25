/** MESSAGE_PROTOCOL is the protocol within the network manager. */
enum MESSAGE_PROTOCOL { GENDATA=0 , //use these messages as an internal protocol.
					LASERDATA=1,
					COLLISIONDATA=2,
					CHATDATA=3,
					CONNECTDATA=4,
					PINGDATA=5
};

/** enum PLAYER_PROTOCOL is the protocol between NetworkManager and Player */
enum PLAYER_PROTOCOL { //push these messages into the player's queue.
	GENDATA=0 , 
	LASERDATA=1,
	COLLISIONDATA=2,
	CHATDATA=3,
	CONNECTDATA=4,
	DROPDATA=5
};

/** PlayerInfo is used by the network for initializing player*/
struct PlayerInfo {
	std::string playerName;
	tIP4 ipAddress;
	Time lastMessageTime;
	OBJECT_TYPE objtype; //Communicated this to the player, maybe?
};

/**Physics hepler classes*/
class LineSeg {
public:
	Position start, end;
	Length length;
	LineSeg();
};

class Ray { 
public:
	Position start; 
	Direction direction;
	Ray();
};

class Line {
public:
	Position start; //Every line must pass through a point. 
	Direction direction; //Extends in both directions. 
	Line();
};

/**Different types of Space Objects*/
enum OBJECT_TYPE {
	ASTEROID = 0,
	
	HEALTH = 1,
	AMMO = 2,
	
	XWING = 3,
	TIE = 4,
	MF = 5
};

/**Player class helpers*/
struct GameEvent {
	PLAYER_PROTOCOL eventType;
};

struct WorldState {
	vector<PlayerInfo> playerInfo;
	vector<SpaceObject> objectsInSpace;
};

class UserSettings {
public:
	glm::vec3 mouseSensitivity;	   //Along x,y,z.
	KeyboardMapping keyboardMapping;
	UserSettings() {}
	void read_settings(); //Read from setting files.
	void save_settings(); //Save to setting files
};