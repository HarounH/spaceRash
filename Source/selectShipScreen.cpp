#ifndef SELECT_SHIP_SCREEN_CPP
#define SELECT_SHIP_SCREEN_CPP

#include "selectShipScreen.hpp"

/*
	The sfgui world is like a tree.
	Also, its essentially static in that it recomputes possibly changing things in every update call.
	so lets try to be intuitive in the declaration, where the order really shouldn't matter.
	bottom-to-top.
*/
SelectShipScreen::SelectShipScreen(Player*& _usrptr , vector<SpaceObject*>*& displayList) {
	usrptr = _usrptr;
	currentShip = 0;
	shipDisplayList = displayList;
	internalSelectionDone = false;
	cout << "pritning ship locations \n";
	for(int i=0; i<(*displayList).size(); ++i) {
		cout << "\t" << (*displayList)[i]->getRigidBody()->getCenterOfMassPosition().getX() << "," << (*displayList)[i]->getRigidBody()->getCenterOfMassPosition().getY() << "," << (*displayList)[i]->getRigidBody()->getCenterOfMassPosition().getZ() << "\n";
	}
}

SelectShipScreen::~SelectShipScreen() {

}

void SelectShipScreen::onRightShiftButtonClick() {
	currentShip++;
	if(currentShip == (int) shipDisplayList->size()) {
		currentShip = 0;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.0,0,0,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);
	glViewport(0,0,800,600);
	glFlush();
}

void SelectShipScreen::onLeftShiftButtonClick() {
	currentShip --;
	if(currentShip < 0) {
		currentShip = ((int) shipDisplayList->size()) - 1;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.0,0,0,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);
	glViewport(0,0,800,600);
	glFlush();
}

void SelectShipScreen::onStartJoinButtonClick() {
	//go to next window
	internalSelectionDone = true;
}

void SelectShipScreen::setMouseSensitivity() {
	usrptr->getSettings()->mouseSensitivity.setX(XMouseSense->GetValue());
	usrptr->getSettings()->mouseSensitivity.setY(YMouseSense->GetValue());	
}

void SelectShipScreen::setCrosshairColor() {
	if(RedButton->IsActive())
	{
		usrptr->getSettings()->HUDCross_r = ColourMeter->GetValue();
	}
	else if(GreenButton->IsActive())
	{
		usrptr->getSettings()->HUDCross_g = ColourMeter->GetValue();
	}
	else if(BlueButton->IsActive())
	{
		usrptr->getSettings()->HUDCross_b = ColourMeter->GetValue();
	}
}

void SelectShipScreen::setUserName() {
	usrptr->getSettings()->name = enterName->GetText();
}

void SelectShipScreen::onResetSettingsButtonClick() {
	XMouseSense->SetValue( usrptr->getSettings()->mouseSensitivity.getX());
	YMouseSense->SetValue( usrptr->getSettings()->mouseSensitivity.getY());

	for(int i=0; i<userSettingsLabels.size(); ++i) {
		//KeyboardInput(i)
		sf::Keyboard::Key key = usrptr->getSettings()->getKey( (KeyboardInput)i );
		std::string entryText = toString(key);
		userSettingsEntries[i]->SetText(entryText);
	}
}

void SelectShipScreen::onSaveSettingsButtonClick() {
	setUserName();
	setMouseSensitivity();
	setCrosshairColor();
	setUserSettings();
}

void SelectShipScreen::setUserSettings() {
	//ASSERT: userSettings.size() <= #(keyboard inputs)
	for(int i=0; i<userSettingsLabels.size(); ++i) {
		//KeyboardInput(i)
		std::string entryText = userSettingsEntries[i]->GetText();
		sf::Keyboard::Key key = keyFromString(entryText);
		usrptr->getSettings()->updateKeyMapLeft(key , (KeyboardInput)i );
	}
	usrptr->getSettings()->save_settings();
}

void SelectShipScreen::initHugeBox() {
	hugeBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL , 0.0f);
}

void SelectShipScreen::initButtonTable() {
	btnTable=sfg::Table::Create();
	btnTable->SetRowSpacings(5.f);
	btnTable->SetColumnSpacings(5.f);
	
	startJoin = sfg::Button::Create("Start-Join!");
	leftShift = sfg::Button::Create("<<");
	rightShift = sfg::Button::Create(">>");
	resetSettings = sfg::Button::Create("Reset Settings");
	saveSettings = sfg::Button::Create("Save Settings");
	playerName = sfg::Label::Create("Name : ");
	enterName = sfg::Entry::Create( usrptr->getSettings()->name);
	
	//playername-entryname
	//left button, right button, 
	//save settings, reset settings, 
	//start-join
	btnTable->Attach( playerName , sf::Rect<sf::Uint32>(0,0,1,1) ,  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	btnTable->Attach( enterName , sf::Rect<sf::Uint32>(1,0,1,1) ,  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);

	btnTable->Attach(leftShift, sf::Rect<sf::Uint32>(0,1,1,1),  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	btnTable->Attach(rightShift, sf::Rect<sf::Uint32>(1,1,1,1),  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	
	btnTable->Attach(resetSettings, sf::Rect<sf::Uint32>(0,2,1,1),  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	btnTable->Attach(saveSettings, sf::Rect<sf::Uint32>(1,2,1,1),  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	
	btnTable->Attach(startJoin , sf::Rect<sf::Uint32>(0,3,1,1) ,  sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);

	leftShift->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onLeftShiftButtonClick, this ) );
	rightShift->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onRightShiftButtonClick, this ) );
	startJoin->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onStartJoinButtonClick, this ) );
	resetSettings->GetSignal(sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectShipScreen::onResetSettingsButtonClick , this) );
	saveSettings->GetSignal(sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectShipScreen::onSaveSettingsButtonClick , this) );

}
void SelectShipScreen::initScaleTable() {
	scaleTable = sfg::Table::Create();
	scaleTable->SetRowSpacings(5.f);
	scaleTable->SetColumnSpacings(5.f);
	//initScaleBox();
	XMouseSense = sfg::Scale::Create(0.f, 1.f, .001f, sfg::Scale::Orientation::HORIZONTAL);
	XMouseSense->SetRequisition(sf::Vector2f(50.0f, 0.0f));
	YMouseSense = sfg::Scale::Create(0.f, 1.f, .001f, sfg::Scale::Orientation::HORIZONTAL);
	YMouseSense->SetRequisition(sf::Vector2f(100.0f, 0.0f));
	xSenseName = sfg::Label::Create("X Mouse Sensitivity");
	ySenseName = sfg::Label::Create("Y Mouse Sensitivity");
	
	redName = sfg::Label::Create("Red");
	blueName = sfg::Label::Create("Green");
	greenName = sfg::Label::Create("Blue");
	crossName = sfg::Label::Create("Cross-hair Colour");

	ColourMeter = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	ColourMeter->SetRequisition(sf::Vector2f(100.0f, 0.0f));
	
	rgbGroup = sfg::RadioButton::RadioButtonGroup::Create();
	RedButton = sfg::RadioButton::Create("Red", rgbGroup);
	GreenButton = sfg::RadioButton::Create("Green", rgbGroup);
	BlueButton = sfg::RadioButton::Create("Blue", rgbGroup);


	scaleTable->Attach(xSenseName , sf::Rect<sf::Uint32>(0,0,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(XMouseSense , sf::Rect<sf::Uint32>(1,0,1,1), sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(ySenseName , sf::Rect<sf::Uint32>(0,1,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(YMouseSense , sf::Rect<sf::Uint32>(1,1,1,1), sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	
	scaleTable->Attach(crossName , sf::Rect<sf::Uint32>(0,2,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(ColourMeter , sf::Rect<sf::Uint32>(1,2,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);

	scaleTable->Attach(RedButton , sf::Rect<sf::Uint32>(0,3,1,1) , sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(GreenButton , sf::Rect<sf::Uint32>(1,3,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	scaleTable->Attach(BlueButton , sf::Rect<sf::Uint32>(2,3,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
}

void SelectShipScreen::initMapTable() {
	for(int action = 0; action < 20; ++action) {
		KeyboardInput kaction = (KeyboardInput)action;
		sf::Keyboard::Key key = usrptr->getSettings()->getKey( kaction);
		userSettingsLabels.push_back( sfg::Label::Create(toString(kaction)) );
		userSettingsEntries.push_back( sfg::Entry::Create(toString(key)) );
		userSettingsEntries[action]->SetRequisition(sf::Vector2f(70.0f, 0.0f));
	}
	//ASSERT : Data vecs Populated.
	mapTable = sfg::Table::Create();
	mapTable->SetRowSpacings(5.f);
	mapTable->SetColumnSpacings(5.f);
	
	for(int i=0; i<20; ++i) {
		mapTable->Attach( userSettingsLabels[i] , sf::Rect<sf::Uint32>(0,i,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
		mapTable->Attach( userSettingsEntries[i] , sf::Rect<sf::Uint32>(1,i,1,1) , sfg::Table::EXPAND | sfg::Table::FILL , sfg::Table::EXPAND | sfg::Table::FILL);
	}
}

void SelectShipScreen::init2() {
	initScaleTable();
	initMapTable();
	initButtonTable();
	initHugeBox();
	//initDisplayBox();
	//Root Node = hugeBox

}


void SelectShipScreen::Run2(bool& selectionDone,ObjManager* mObjManager) {
	//ASSERT : Window already running.
	sf::Window wnd(sf::VideoMode(usrptr->getSettings()->defaultScreenSizeX , usrptr->getSettings()->defaultScreenSizeY), "Select your ship!" , sf::Style::Titlebar | sf::Style::Close/*, sf::ContextSettings(32)*/);
	sfg::SFGUI sfgui;


	init2();

	//prepare the highest level.
	auto scalewindow = sfg::Window::Create();
	scalewindow->SetTitle("Scales");
	scalewindow->SetPosition(sf::Vector2f(0.0f, 200.0f));
	auto mapwindow = sfg::Window::Create();
	mapwindow->SetTitle("Keyboard bindings\n");
	mapwindow->SetPosition(sf::Vector2f(600.0f,0.0f));
	auto btnwindow = sfg::Window::Create();
	btnwindow->SetPosition(sf::Vector2f(300.0f,400.0f));
	
	scalewindow->SetStyle(0);
	mapwindow->SetStyle(0);
	btnwindow->SetStyle(0);
	sfg::Desktop desktop;

	scalewindow->Add(scaleTable);
	mapwindow->Add(mapTable);
	btnwindow->Add(btnTable);

	desktop.Add(scalewindow);
	desktop.Add(mapwindow);
	desktop.Add(btnwindow);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (wnd.getPosition().x/(double)wnd.getPosition().y) , 0.01f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.0,0,0, 
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0);
	glViewport(0,0,800,600);
	glFlush();


	sf::Event event;
	while(!internalSelectionDone) {
		while( wnd.pollEvent(event)) {
			desktop.HandleEvent(event);
			if ( event.type == sf::Event::Closed) {
				internalSelectionDone = selectionDone = true; //i hope its right assoc.
			}
		}

		glEnable(GL_TEXTURE_2D);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		(*shipDisplayList)[currentShip]->render(true,mObjManager);
		glDisable(GL_TEXTURE_2D);

		desktop.Update(0.0f);
		sfgui.Display(wnd);
		wnd.display();

		selectionDone = internalSelectionDone;
	}
	usrptr->setFighterType(((*shipDisplayList)[currentShip]->getType()));

}
#endif