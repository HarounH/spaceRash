class NetworkManager {

public:
	void init(PlayerInfo& pinfo); //Create player
	void nullify();
	bool createNetwork(); //Creates a port and starts listening.
	bool connectToNetwork(tIP4 peerIP); //Create a port, listen on it and also send message to peerIP etc.
	bool leaveNetwork(); //Close the active port.
	bool isAlive(int p_idx);
	bool killIdlers(); //Also broadcasts the message across.
	bool broadcastMessage(); //send message to all.
	bool sendMessage();		 
	bool getMessages(std::vector< GameEvent >& eventQueue); //All the events that need to be processed for the next rendering iteration.
	/* Debugging functions: The boolean is to toggle debug mode */
	void dprint(bool debug_net=false);
	void drender(bool debug_net=false);

private:
	//vector of IPs of all players.
	PlayerInfo me;
	int myIdx;
	std::vector<PlayerInfo> network;
};