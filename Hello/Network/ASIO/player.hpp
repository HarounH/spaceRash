#ifndef PLAYER_H
#define PLAYER_H

#include "helpers.hpp"

class HUD{
//Elements to show on the screen.
};

class Player {
private:
	/* misc data. */
	OBJECT_TYPE fighterType;
	UserSettings settings;
	HUD hud;
	/* Rendering geometry */

	/* Physics geometry. */
	BulletWorld* bulletWorld;	
public:
	Player();
	~Player();

	void init_bulletWorld();
	

	void loadSettings(); //includes HUD settings.
	void saveSettings();


	void handleEvent();

	/* game loop functions. */
	void game_loop(); //Start here
	void select_ship_screen();
	void startjoin_screen();
		void start_game(); 
		void connect_game();
	void waiting_screen();
	void race_begin();
	void race_end();
	void game_over();
	
	

};
#endif