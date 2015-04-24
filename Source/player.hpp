#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "helpers.hpp"
#include "spaceObject.hpp"
#include "networkManager.hpp"
#include "skybox.hpp"
#include "selectShipScreen.hpp"
#include "startJoinScreen.hpp"
#include "ObjManager.hpp"
typedef boost::bimap< int, SpaceObject* > spaceObjWeed;
typedef spaceObjWeed::value_type spaceObjWeedNormal;
typedef spaceObjWeed::left_value_type spaceObjWeedLeft; 
typedef spaceObjWeed::right_value_type spaceObjWeedRight;

typedef boost::bimap<int,int> NtoPType;
typedef NtoPType::value_type NtoPTypeNormal;
typedef NtoPType::left_value_type NtoPTypeLeft;
typedef NtoPType::right_value_type NtoPTypeRight;

typedef boost::bimap<string,int> NametoPType;
typedef NametoPType::value_type NametoPTypeNormal;
typedef NametoPType::left_value_type NametoPTypeLeft;
typedef NametoPType::right_value_type NametoPTypeRight;

class Player {
private:
	/* misc data. */
	bool didStart;
	bool hasSetInitialPosition;
	int numAIs;
	int numPlayers;
	bool startGame;

	bool rotatePressed;
	int nextSpaceObjId;
	OBJECT_TYPE fighterType;
	SpaceObject* fighter;
	ObjManager* allObjects;

	/* network integration */
	State* myState;
	NtoPType NtoP;  // for every network int,there must be a player int
	NametoPType NameToP;
	NetworkManager* network;
	Message* myMessage;
	std::vector<bool> confirmed;
	/* Rendering geometry */
	//sf::Window* wnd; //Window that things run on. <-- deprecated.
	/* Physics geometry. */
	BulletWorld* bulletWorld;
	sf::Music* music;
	boost::bimap< int, SpaceObject* > EveryOne;

	std::string SKYBOX_IMG;
	SkyBox* skybox;
	float skybox_size;
	double halfWindowSizeX;
	double halfWindowSizeY;

	UserSettings* settings;
	int camera_idx;
public:
	Player(ObjManager*);
	~Player();

	bool hasWon;
	bool endGame;

	bool started() { return didStart; }
	void started(bool _didStart) { didStart = _didStart; }
	bool beginGame() { return startGame; }

	int numberOfPlayers() { return numPlayers; }
	NetworkManager* getNetwork() { return network; } 

	SpaceObject* which_spaceObject(int network_int);
	SpaceObject* which_spaceObject(string playerName);
	string which_player_name(SpaceObject* obj);

	bool addtoNtoP(int network_int, int player_int);
	bool addtoNametoP(string playerName, int player_int);
	
	void init_bulletWorld();
	void init_fighter();
	/* collision */
	static bool collisionCallback(btManifoldPoint& cp,
		const btCollisionObjectWrapper* obj1,int id1,int index1,
		const btCollisionObjectWrapper* obj2,int id2,int index2);


	void handle_event(sf::Event& event,sf::Window& window);

	void update_state(double dt);
	void render_state(double dt);
	void setup_game_screen(double,double);
	void loadSettings(); //includes HUD settings.
	void saveSettings();
	void playMusic(bool dflag = false);
	void handleEvent();
	/* game loop functions. */
	void game_loop(); 


	void select_ship_screen();
	void startjoin_screen();
	void setGameMode(std::string myip, unsigned short myport , bool startmode = true, std::string otherip = "", unsigned short otherport = 0, int _numPlayers = 0, int _numAIs = 0);
	void start_game();
	void connect_game();
	void waiting_screen();
	void race_begin();
	void race_end();
	void game_over();

	void startNetwork(string, unsigned short);
	void connectToNetwork(string, unsigned short, string, unsigned short);
	void setGeneralData();
	void sendMessage();
	void sendMessage(std::string);
	void sendMessageToClient(long long);
	void translateMessage(ClientMessage);
	void receiveMessage();
	void handleMessage(Message, int);
	void resetMouse(sf::Window&);
	//TODO : addSpaceObjectToWorld( cool-network-struct )
	bool addToEveryOne(int,SpaceObject*&); //------------PASS THE SPACE OBJ AFTER INSTANTIATING IT----------//
	bool add_object(SpaceObject*&); //------------PASS THE SPACE OBJ AFTER INSTANTIATING IT----------//
	void getNextValidPosition(btVector3&); //------The player who starts the game requires this function----//

	void fire_laser();
	void toggle_camera(double, double);
	/** gets and sets */
	UserSettings* 	getSettings();
	BulletWorld* 	getBulletWorld();
	SpaceObject* 	getFighter();
	void 			setFighterType(OBJECT_TYPE _t);
	OBJECT_TYPE 	getFighterType();
	SpaceObject*	getSpaceObject(int); 
	int 			getID(SpaceObject*);
	void 			readWorld(std::string wp);
	void getWindowSize(double & x, double & y);
	/** debuggers */
	void debug();

};
#endif