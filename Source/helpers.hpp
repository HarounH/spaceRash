#ifndef HELPERS_H
#define HELPERS_H
/** c++ includes */
using namespace std;


#include <string.h> //because character arrays.
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
/** sfml includes */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
/** physics includes */
#include <btBulletDynamicsCommon.h>
/** sfgui includes */
#include <SFGUI/SFGUI.hpp>

#include <boost/config.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/support/lambda.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

/* math! */
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
#defines.
*/
const std::string debugPath = "Hello/render/";
const std::string RSC_DIR= "Resource/"; //shouldn't need this, ideally.
const std::string PHY_RSC_DIR =  "Resource/Physics/";
const std::string OBJ_RSC_DIR = "Resource/Render/";
const std::string MUSIC_RSC_DIR = "Resource/Music/";
const std::string SW_MUSIC = "SW";
const std::string HEALTH_FNAME  = "health";
const std::string AMMO_FNAME  = "ammo";
const std::string TIEF_FNAME  = "ties";
const std::string ASTEROID_FNAME  = "asteroid";
const std::string XWING_FNAME  = "xwing";
const std::string MF_FNAME  = "mf";
const std::string UFO_FNAME  = "ufo";
const std::string DEBRIS_FNAME  = "debris";
const std::string ENDPOINT_FNAME  = "endpoint";
const std::string SKYRISE_TALL_FNAME  = "skyrise_tall";
const std::string SKYRISE_FAT_FNAME  = "skyrise_fat";
const std::string OBJ_EXTENSION = ".obj";
const std::string PHY_EXTENSION = ".lhc";
const std::string MUSIC_EXTENSION = ".ogg";
const std::string WORLD_PHY_FNAME = "Resource/myWorld.avril";

/* This file contains parsers for user settings. */
const std::string SETTINGS_FILE = "thereisaspoon.tang";

class SpaceObject;
class Player;
class NetworkManager;
struct Weapon;
struct State;
struct Message;

/** Bullet Physics' World. */
struct BulletWorld {
    btBroadphaseInterface* broadphase;// = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration;// = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher;// = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver;// = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld;// = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    BulletWorld() {
    	broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0,0,0));
    }
    ~BulletWorld() {
		    delete dynamicsWorld;
		    delete solver;
		    delete collisionConfiguration;
		    delete dispatcher;
		    delete broadphase;
    }
};


enum KeyboardInput {
	NONE = -1 ,
	ACCELERATE, DECELERATE, STRAFE_LEFT, STRAFE_RIGHT, ASCEND, DESCEND, /* Translational Movement */
	PITCH_UP, PITCH_DOWN, YAW_LEFT, YAW_RIGHT, ROLL_LEFT, ROLL_RIGHT, /* Rotational Movement */
	TOGGLE_FULLSCREEN, TOGGLE_CAM, /* camera type things. */
	FIRE_WEAPON , TOGGLE_WEAPON, USE_ABILITY, /* weaponry */
	ESCAPE, /**/
	START_CHAT, ESCAPE_CHAT, SEND_CHAT

};

#include "keyToString.hpp"

typedef boost::bimap< sf::Keyboard::Key , KeyboardInput > KeyboardMapping;
typedef KeyboardMapping::value_type keymap_type;

enum WEAPON_TYPE {
	WEAK_LASER = 1,
	MEDIUM_LASER = 2,
	STRONG_LASER = 3,
	CANNON = 4,
	HEAT_MISSILE = 5,
	FORCE = 6
};

/** communication protocols. */
enum OBJECT_TYPE {
	ASTEROID = 0,
	HEALTH = 1,
	AMMO = 2,	
	XWING = 3,
	TIE = 4,
	MF = 5,
	ENDPOINT = 6,
	SKYRISE_TALL = 7,
	SKYRISE_FAT = 8,
	DEBRIS = 9,
	UFO = 10000
};


/** Message_type is the protocol within the network manager. */
enum MESSAGE_PROTOCOL { GENDATA=1 , //use these messages as an internal protocol.
					LASERDATA=2,
					COLLISIONDATA=4,
					CONFIRMDATA=8,
					CONNECTDATA=16,
					SETCONNECTDATA=32,
					DIEDATA=64,
					WINDATA=128
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

class UserSettings {
public:
	/* Sensitivity and stuff. */
	std::string name;
	btVector3 mouseSensitivity;	   //Along x,y,z.
	KeyboardMapping keyboardMapping;
	float fov;
	float HUDCross_r,HUDCross_g,HUDCross_b;
	int defaultScreenSizeX,defaultScreenSizeY;
	void set_default();
	void read_settings(); //Read from setting files.
	void save_settings(); //Save to setting files
	/* wrappers for the bimap. */
	void 				updateKeyMap(sf::Keyboard::Key _key , KeyboardInput _action);
	void				updateKeyMapLeft(sf::Keyboard::Key _key , KeyboardInput _action);
	KeyboardInput 		getAction(sf::Keyboard::Key _key); // -1 returns NONE.
	sf::Keyboard::Key 	getKey(KeyboardInput _action); //returns -1 if nothing is mapped.
};

struct State {
	int health;
	int ammo;
	std::vector<float> transform; //position, rotation.
	std::vector<float> linearVelocity, angularVelocity;
	OBJECT_TYPE objType;
	
	State();	
	~State();
	State(State& other);
	State& operator= (State& other);
	State(int h,int am, btTransform& t, btVector3& lv , btVector3& av, OBJECT_TYPE _t);
	void setData(int h,int am, btTransform& t, btVector3& lv , btVector3& av, OBJECT_TYPE& _t);
	void getData(int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t);
	
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & health;
		ar & transform;
		ar & linearVelocity;
		ar & angularVelocity;
		ar & objType;
	}
};

struct Message {
	int msgType;
	State ship; //general data - includes myShip details.
	//collision data, is essentially health and new transform.
	std::string hitPlayerName;	 //chat data.
	std::vector<float> laserFrom,laserTo; //laser data. LINE SEGMENT.
	int wpnType;
	/* Connection data */
	std::string newConnectorIP;
	unsigned short newConnectorPort;
	/*
		IDEA : Forward this message to everyone, and respond to the sender with my details.
	*/
	std::string playerName; //file name to load from.

	Message(int prot , 
		int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
		btVector3& _laserFrom , btVector3& _laserTo , int& _wpnType , 
		std::string ip = "" , unsigned short port = 0, std::string hitname = "" , std::string name = "");
	Message();
	Message(Message& other);
	Message& operator= (Message& other);
	void setData(int prot , 
		int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
		btVector3& _laserFrom , btVector3& _laserTo ,int& _wpnType,
		std::string ip = "" , unsigned short port = 0, std::string hitname = "" , std::string name = "");
	void setData(int prot, std::string ip = "", unsigned short port = 0);
	void setData(btVector3& _laserFrom, btVector3& _laserTo);
	void setData( int prot , State* state , Weapon* wpn );
	void getData(int prot , 
		int& h, int& am, btTransform& t, btVector3& velo, btVector3& avelo , OBJECT_TYPE& _t, //For state
		btVector3& _laserFrom , btVector3& _laserTo ,int& _wpnType,
		std::string& ip, unsigned short port, std::string& hitname, std::string& name);
	void getData(btVector3&, btVector3&);
	
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & msgType;
		ar & ship;
		ar & hitPlayerName;
		ar & laserFrom;
		ar & laserTo;
		ar & newConnectorIP;
		ar & newConnectorPort;
		ar & playerName;
	}
	void print(){
		cout<<newConnectorIP<<" "<<newConnectorPort<<"\n";
	}
};
struct Weapon {

	Weapon(WEAPON_TYPE t , btVector3 color);
	~Weapon();
	void fireProjectile(btVector3& from, btVector3& to);
	void drawProjectile(btVector3& from, btVector3& to);
	void update();
	WEAPON_TYPE type;
	float strength;
	float r,g,b;
	double regen_rate;
	int max_ammo,ammo;
	bool active;
	int time_left;
	SpaceObject* fighter;
	BulletWorld* world;
	btVector3 last_from, last_to;
	
};

#include <tuple>
/** networking typedefs */
typedef std::tuple< int,int,int,int > tIP4;
typedef int Time ; //discretized?


#endif