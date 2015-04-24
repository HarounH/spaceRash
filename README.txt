%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Authors: Akshay Kumar Gupta	Barun Patra	Haroun Habeeb      J. Shikhar Murty
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
INTRODUCTION:
Skyline Wars is a fully 3D racing and first person shooter game. Each player owns a ship and the objective is to reach the end while trying to shoot the other players down.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
COMPILATION AND EXECUTION:
Compiling the Project:
	"make" builds the project
Starting the Game:
	"make execute" starts the game
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
REQUIREMENTS:
Libraries:
	SFML
	boost
	bullet-physics
	SFGUI
GCC Version: c++11 support required.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Welcome Screen:
	On running the game, the user is shown a screen in which he can set all the controls for the game according to his/her preferences. He can also select his ship on this screen out of these ships: TIE Fighter, X-Wing Fighter, UFO. On clicking the Start/Join button, the user is taken to the Start/Join screen.
Start/Join Screen:
	In the start/join screen, the player can either choose to start a game by specifying the number of players and the number of AIs, or join an existing game by providing the IP and port of the player who started that game.
The Game:
	The world is a skyline with tall buildings, the positions of which form the route to the goal. There is a main route to the goal, and there are also shortcuts which are more dangerous but which shorten the route to the goal. Try to shoot everybody down and get to the finish line!