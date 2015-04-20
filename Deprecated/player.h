#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
/* GLM! */
#include <glm/glm.hpp>
/* Boost includes. no special linkers. */
#include <boost/config.hpp>
#include <boost/bimap.hpp>

#include "spaceObject.h"
#include "networkManager.h"

/**
This file is the header file for userSettings and also the player.
*/
using namespace std;

/* Auxillary things for keyboard mapping. */

class Player {
public:
	Player() {}
	~Player() {}


	/** Debugging functions -- The boolean is for toggle debug mode. */
	void dprint(bool debug_cuboid=false); //the d stands for Debug.
	void drender(bool debug_cuboid=false);

	/** glut-linking-event handlers. */
	void keyboardHandler(); //Takes in keyboard stuff.
	void mouseHandler(); //Takes in mouse position.
	void shootHandle(); //Takes in clicked point?
	void shotHandle(GameEvent); //I got shot, handle it.
	void updateGameState();
			
private:
	/* Load this upon creaiton. */
	UserSettings settings;
	NetworkManager manager;
	std::vector< GameEvent > todolist; //List of all messages received etc.
	SpaceObject fighter; //his ship.
	WorldState world;
};
#endif