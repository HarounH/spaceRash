#ifndef NETWORK_MANAGER
#define NETWORK_MANAGER
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include <ctime>


/* Include boost sockets, threads, mention library includes and so on.
*/

/** The header file for network manager. */

#include <tuple>
using namespace std;
typedef tuple< int,int,int,int > tIP4;
typedef int Time ; //discretized?
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
	//TODO: Aux data.
};

/*compile using : -lboost_system -lboost_thread might work.
use the following shorthand namespace? 
*/
namespace budp = boost::asio::ip::udp; //check this syntax. Also, udp is a specific thing, apparently.

class NetworkManager {
public:
	/** creationism */
	void init(PlayerInfo& pinfo); //Doesn't create the port.
	void nullify();
	/** Need a heap/queue of messages/things */
	/** */
	bool createNetwork(); //Creates a port and starts listening.
	bool connectToNetwork(tIP4 peerIP); //Create a port, listen on it and also send message to peerIP and so on.
	bool leaveNetwork(); //Close the active port.

	bool isAlive(int p_idx);
	bool killIdlers(); //Also broadcasts the message across.

	bool broadcastMessage(); //send message to all.
	bool sendMessage();		 
	
	bool getMessages(std::vector< GameEvent >& eventQueue); //All the events that need to be processed for the next render-loop iteration.
	
	/** Debugging functions -- The boolean is for toggle debug mode. */
	void dprint(bool debug_net=false); //the d stands for Debug.
	void drender(bool debug_net=false);

private:
	/** Need stuff here. */
	//vector of IPs of all players.
	PlayerInfo me;
	int myIdx;
	std::vector<PlayerInfo> network;
	//TODO: UDP Sockets etc
};
#endif