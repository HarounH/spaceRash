#ifndef SELECT_SHIP_SCREEN
#define SELECT_SHIP_SCREEN

#include "helpers.hpp"
#include "player.hpp"
/**
Explanation of flow:
It is constructed by passing a user-pointer and a display list of ships.
Theres a shit ton of buttons which are instantiated during the call of the procedure Run().

Their function binding can probably be set upon their creation.

A sf::Window is generated in Run, it is later closed.
A couple of sfg:;Windows are created, with style set to 0. Their position Needs to be correctly set.
Each of these windows contains something called a table. These tables can be modified aptly, just needs to be done.

Before adding kids to tables, set the spacing for the table. you can probably change this in the middle of the attachment too, H doesn't know.

Table's Attach function gives the Table-container children ( such as boxes, labels , etc. )
The syntax for Attach:
ptr_table->Attach( ptr_child , sf::Rect<sf::Uint32>(col# , row#, colSpan, rowSpan) , sfg::TableEXPAND|sfg::Table::FILL,sfg::TableEXPAND|sfg::Table::FILL ). 
	Note: The use of the enum above.

*/
class SelectShipScreen {
private:
	//Player that calls this window
	Player* usrptr;
	bool internalSelectionDone;
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

	sfg::Table::Ptr scaleTable; //contains scales.
	sfg::Table::Ptr mapTable;	//contains keyboard mappings.
	sfg::Table::Ptr btnTable;	//contains buttons.	
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

	sfg::SFGUI sfgui;
public:

	SelectShipScreen(Player*& , vector<SpaceObject*>*&);

	~SelectShipScreen();

	void onRightShiftButtonClick();

	void onLeftShiftButtonClick();

	void onStartJoinButtonClick();

	//void setupAlignment(std::vector<sfg::Alignment::Ptr>&);

	void setMouseSensitivity();

	void setUserSettings();

	void setCrosshairColor();

	void setUserName();

	void onResetSettingsButtonClick();

	void onSaveSettingsButtonClick();

	//void Run(sf::Window&);
	
	void init2(); // -H wip.
	void initScaleTable(); //-H wip, need to add event handlers and prettify.
	void initMapTable(); //-H wip. need to add event handlers, and test.
	void initButtonTable();
	void initHugeBox();
	void Run2(bool&,ObjManager*); // -H wip.
};
#endif