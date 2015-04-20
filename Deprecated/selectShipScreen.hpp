#ifndef SELECT_SHIP_SCREEN
#define SELECT_SHIP_SCREEN

#include "helpers.hpp"
#include "player.hpp"

class SelectShipScreen {
private:
	//Player that calls this window
	Player* usrptr;
	
	//All the buttons on this window
	sfg::Button::Ptr leftShift;
	sfg::Button::Ptr rightShift;
	sfg::Button::Ptr startJoin;

	sfg::Scale::Ptr XMouseSense;
	sfg::Scale::Ptr YMouseSense;
	sfg::Scale::Ptr ColourMeter;
	
	/* pain incoming. 
	map characters to sf::Keyboard::Key , very very painful :(
	->made to string functions, to make life less painful.
	*/
	std::vector< sfg::Label::Ptr > userSettingsLabels;
	std::vector<sfg::Entry::Ptr> userSettingsEntries;
	
	sfg::Button::Ptr resetSettings;
	sfg::Button::Ptr saveSettings;

	sfg::Label::Ptr playerName;
	sfg::Entry::Ptr enterName;
	sfg::Label::Ptr shipName;
	sfg::Label::Ptr redName;
	sfg::Label::Ptr greenName;
	sfg::Label::Ptr blueName;
	sfg::Label::Ptr xSenseName;
	sfg::Label::Ptr ySenseName;
	sfg::Label::Ptr crossName;
	//List of ships
	std::vector<SpaceObject*>* shipDisplayList;

	sfg::Box::Ptr scaleBox;
	sfg::Box::Ptr displayBox;
	sfg::Box::Ptr mapBox;
	sfg::Box::Ptr hugeBox;

	sfg::Frame::Ptr scaleBoxFrame;
	sfg::Frame::Ptr displayBoxFrame;
	sfg::Frame::Ptr mapBoxFrame;
	sfg::Frame::Ptr hugeBoxFrame;

	sfg::RadioButton::Ptr RedButton;
	sfg::RadioButton::Ptr GreenButton;
	sfg::RadioButton::Ptr BlueButton;
	sfg::RadioButton::RadioButtonGroup::Ptr rgbGroup;

	int currentShip;
	bool startjoin;

	sfg::SFGUI sfgui;
public:

	SelectShipScreen(Player* , vector<SpaceObject*>*&);

	~SelectShipScreen();

	void onRightShiftButtonClick();

	void onLeftShiftButtonClick();

	void onStartJoinButtonClick();

	void setupAlignment(std::vector<sfg::Alignment::Ptr>&);

	void setMouseSensitivity();

	void setUserSettings();

	void setCrosshairColor();

	void setUserName();

	void onResetSettingsButtonClick();

	void onSaveSettingsButtonClick();

	void Run();
};
#endif