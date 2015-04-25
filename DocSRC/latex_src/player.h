class UserSettings {
public:
	glm::vec3 mouseSensitivity;	   //Along x,y,z.
	KeyboardMapping keyboardMapping;
	UserSettings() {}
	void read_settings(); //Read from setting files.
	void save_settings(); //Save to setting files
};

class Player {
public:
	Player() {}
	// Debugging functions: The boolean is to toggle debug mode.
	void dprint(bool debug_cuboid=false);
	void drender(bool debug_cuboid=false);
	// glut-linking-event handlers.
	void keyboardHandler(); //Takes in keyboard input.
	void mouseHandler(); //Takes in mouse position.
	void shootHandle(); //Takes in clicked point.
	void shotHandle(GameEvent); //Handle getting shot.
	void updateGameState();
			
private:
	// Loaded upon creaiton.
	UserSettings settings;
	NetworkManager manager;
	std::vector< GameEvent > todolist; //List of all messages received etc.
	WorldState world;
	SpaceObject fighter;
};