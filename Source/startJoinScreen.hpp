#ifndef START_JOIN_SCREEN
#define START_JOIN_SCREEN
#include "helpers.hpp"
#include "player.hpp"
class StartJoinScreen {
public:
	StartJoinScreen(Player*& _usrptr);
	~StartJoinScreen();

	void onStartButtonClick();
	void onJoinButtonClick();
	void Run();
private:
	Player* usrptr;
	bool internalRunning;
	sfg::Label::Ptr myIPLabel,myPortLabel,helpLabel, nPlayersLabel, nAIPlayersLabel, otrIPLabel, otrPortLabel;
	sfg::Entry::Ptr myIPEntry , myPortEntry, otherIPEntry, otherPortEntry, nPlayersEntry, nAIPlayersEntry;
	sfg::Button::Ptr startButton , joinButton;
};
#endif