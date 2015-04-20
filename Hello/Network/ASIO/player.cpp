#ifndef PLAYER_CPP
#define PLAYER_CPP
#include "players.hpp"

Player() {
	//Do things.
	init_bulletWorld();
}

~Player() {
	//Do things.
	delete bulletWorld;
}
void init_bulletWorld() {
	bulletWorld = new BulletWorld();
}

#endif