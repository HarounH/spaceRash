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
	//sf::Image leftsfImage;
	//leftsfImage.loadFromFile("");
	//shipName = sfg::Label::Create(shipDisplayList->getName()); // default ship name goes here
	// sfg::Image::Ptr leftsfgImage = sfg::Image::Create(leftsfImage);
	// leftShift->setImage(leftsfgImage);
	//sf::Image rightsfImage;
	//rightsfImage.loadFromFile("");
	// sfg::Image::Ptr rightsfgImage = sfg::Image::Create(rightsfImage);
	// rightShift->setImage(rightsfgImage);
	

	//commented by haroun. TODO - WIP
	/*startJoin = sfg::Button::Create();
	leftShift = sfg::Button::Create();
	rightShift = sfg::Button::Create();
	resetSettings = sfg::Button::Create();
	saveSettings = sfg::Button::Create();
	XMouseSense = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	YMouseSense = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	ColourMeter = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	playerName = sfg::Label::Create("n");

	rgbGroup = sfg::RadioButton::RadioButtonGroup::Create();
	RedButton = sfg::RadioButton::Create("", rgbGroup);
	GreenButton = sfg::RadioButton::Create("", rgbGroup);
	BlueButton = sfg::RadioButton::Create("", rgbGroup);

	enterName = sfg::Entry::Create();
	
	leftShift->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onLeftShiftButtonClick, this ) );
	rightShift->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onRightShiftButtonClick, this ) );
	startJoin->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &SelectShipScreen::onStartJoinButtonClick, this ) );
	resetSettings->GetSignal(sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectShipScreen::onResetSettingsButtonClick , this) );
	saveSettings->GetSignal(sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectShipScreen::onSaveSettingsButtonClick , this) );
	
	scaleBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	displayBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	mapBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	hugeBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

	scaleBoxFrame = sfg::Frame::Create();
	displayBoxFrame = sfg::Frame::Create();
	mapBoxFrame = sfg::Frame::Create();
	hugeBoxFrame = sfg::Frame::Create();

	userSettingsLabels.resize(16);
	userSettingsEntries.resize(16);
	for(int i = 0; i < 16; i++)
	{
		userSettingsLabels[i] = sfg::Label::Create();
		userSettingsEntries[i] = sfg::Entry::Create();
	}

	redName = sfg::Label::Create("r");
	blueName = sfg::Label::Create("g");
	greenName = sfg::Label::Create("b");
	crossName = sfg::Label::Create("cross");
	xSenseName = sfg::Label::Create("xsens");
	ySenseName = sfg::Label::Create("ysens");*/
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
	gluLookAt(-1.0,0,2,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);
	glFlush();
}

void SelectShipScreen::onLeftShiftButtonClick() {
	currentShip --;
	if(currentShip < 0) {
		currentShip = ((int) shipDisplayList->size()) - 1;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.0,0,2,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);
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

// void SelectShipScreen::setupAlignment(std::vector<sfg::Alignment::Ptr>& alignVector) {
	
	
// 	for(int i = 0; i < 54; i++)
// 		alignVector[i]->SetScale(sf::Vector2f(0.0f, 0.0f));

// 	alignVector[0]->SetAlignment(sf::Vector2f(0.8f, 0.1f));
// 	alignVector[1]->SetAlignment(sf::Vector2f(0.1f, 0.1f));
// 	alignVector[2]->SetAlignment(sf::Vector2f(0.8f, 0.15f));
// 	alignVector[3]->SetAlignment(sf::Vector2f(0.1f, 0.15f));
// 	alignVector[4]->SetAlignment(sf::Vector2f(0.5f, 0.25f));
// 	alignVector[5]->SetAlignment(sf::Vector2f(0.2f, 0.3f));
// 	alignVector[6]->SetAlignment(sf::Vector2f(0.8f, 0.4f));
// 	alignVector[7]->SetAlignment(sf::Vector2f(0.7f, 0.4f));
// 	alignVector[8]->SetAlignment(sf::Vector2f(0.5f, 0.4f));
// 	alignVector[9]->SetAlignment(sf::Vector2f(0.4f, 0.4f));
// 	alignVector[10]->SetAlignment(sf::Vector2f(0.2f, 0.4f));
// 	alignVector[11]->SetAlignment(sf::Vector2f(0.1f, 0.4f));
// 	alignVector[12]->SetAlignment(sf::Vector2f(0.25f, 0.8f));
// 	alignVector[13]->SetAlignment(sf::Vector2f(0.5f, 0.2f));
// 	alignVector[14]->SetAlignment(sf::Vector2f(0.5f, 0.5f));
// 	alignVector[15]->SetAlignment(sf::Vector2f(0.8f, 0.7f));
// 	alignVector[16]->SetAlignment(sf::Vector2f(0.2f, 0.7f));
// 	alignVector[17]->SetAlignment(sf::Vector2f(0.25f, 0.8f));
// 	alignVector[18]->SetAlignment(sf::Vector2f(0.25f, 0.85f));

// 	for(int i = 19; i < 51; i+=2)
// 	{
// 		alignVector[i]->SetAlignment(sf::Vector2f(0.7f, 0.1 + ((i-19)*0.02)));
// 		alignVector[i]->SetAlignment(sf::Vector2f(0.2f, 0.1 + ((i-19)*0.02)));
// 	}

// 	alignVector[51]->SetAlignment(sf::Vector2f(0.1f, 0.1f));
// 	alignVector[52]->SetAlignment(sf::Vector2f(0.33f, 0.1f));
// 	alignVector[53]->SetAlignment(sf::Vector2f(0.66f, 0.1f));

// 	cout << "#brk-donesetting\n";

// 	for (int i = 0; i < 13; ++i)
// 		scaleBox->Pack(alignVector[i], true, true);
// 	for(int i = 13; i < 18; ++i)
// 		displayBox->Pack(alignVector[i], true, true);
// 	for(int i = 18; i < 51; ++i)
// 		mapBox->Pack(alignVector[i], true, true);
// 	for(int i = 51; i<54; ++i)
// 		hugeBox->Pack(alignVector[i], true, true);

// 	cout << "#brk-donepacking\n";

// 	alignVector[0]->Add(xSenseName);
// 	cout << "#brk n1\n";
// 	alignVector[1]->Add(XMouseSense);
// 	cout << "#brk n2\n";
// 	alignVector[2]->Add(ySenseName);
// 	cout << "#brk n3\n";
// 	alignVector[3]->Add(YMouseSense);
// 	cout << "#brk n4\n";
// 	alignVector[4]->Add(crossName);
// 	cout << "#brk n5\n";
// 	alignVector[5]->Add(ColourMeter);
// 	cout << "#brk n6\n";
// 	alignVector[6]->Add(redName);
// 	cout << "#brk n7\n";
// 	alignVector[7]->Add(RedButton);
// 	cout << "#brk n8\n";
// 	alignVector[8]->Add(greenName);
// 	cout << "#brk n9\n";
// 	alignVector[9]->Add(GreenButton);
// 	cout << "#brk n10\n";
// 	alignVector[10]->Add(blueName);
// 	cout << "#brk n11\n";
// 	alignVector[11]->Add(BlueButton);
// 	cout << "#brk n12\n";
// 	alignVector[12]->Add(resetSettings);
// 	cout << "#brk n13\n";
// 	alignVector[13]->Add(playerName);
// 	cout << "#brk n14\n";
// 	alignVector[14]->Add(enterName);
// 	cout << "#brk n15\n";
// 	alignVector[15]->Add(leftShift);
// 	cout << "#brk n16\n";
// 	alignVector[16]->Add(rightShift);
// 	cout << "#brk n17\n";
// 	alignVector[17]->Add(startJoin);
// 	cout << "#brk n18\n";
// 	alignVector[18]->Add(saveSettings);
	
// 	for(int i = 0, j = 19; i < 16; ++i, j+=2)
// 	{
// 		cout << "#brk-iter" << i << "\n";
// 		alignVector[j]->Add(userSettingsLabels[i]);
// 		alignVector[j+1]->Add(userSettingsEntries[i]);
// 	}
// 	cout << "#brk-about to add boxes.\n";
// 	alignVector[51]->Add(scaleBox);
// 	cout << "#brk-done scalebox\n";
// 	alignVector[52]->Add(displayBox);
// 	cout << "#brk-done display box\n";
// 	alignVector[53]->Add(mapBox);
// 	cout << "#brk-doneadding\n";
// 	// scaleBoxFrame->Add(scaleBox);
// 	// displayBoxFrame->Add(displayBox);
// 	// mapBoxFrame->Add(mapBox);

// 	// hugeBox-


// }

// void SelectShipScreen::Run(sf::Window& windw /* not even used. */) {
// 	//prepare desktop.
// 	//align boxes.
// 	//add stuff here.
// 	sf::Window window(sf::VideoMode(usrptr->getSettings()->defaultScreenSizeX , usrptr->getSettings()->defaultScreenSizeY), "" , sf::Style::Default, sf::ContextSettings(32));
// 	sfg::SFGUI sfgui;
// 	auto sfgwindow = sfg::Window::Create();
	
// 	std::vector<sfg::Alignment::Ptr> alignVector(54);

// 	for(int i = 0; i < 54; i++)
// 	{
// 		alignVector[i] = (sfg::Alignment::Create());
// 	}
// 	cout << "#brk2.05\n";
// 	setupAlignment(alignVector);
// 	//add boxes and stuff to window
// 	cout << "#brk2.075\n";
// 	sfg::Desktop desktop;
// 	desktop.Add(sfgwindow);
// 	cout << "#brk-done adding window\n";
// 	sfgwindow->Add(hugeBox);
// 	cout << "#brk2.1\n";
// 	sf::Clock clock;

// 	sf::Event event;
// 	while( !startjoin ) {
// 		while( window.pollEvent(event) ) {
// 			desktop.HandleEvent(event);
// 			if ( event.type == sf::Event::Closed ) {
// 				startjoin = true;
// 			}
// 		}
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
// 		//render the selected ship.
// 		//(*shipDisplayList)[currentShip]->render(true);//TODO
		
// 		desktop.Update( clock.restart().asSeconds() );
// 		sfgui.Display(window);
// 		window.display();
		
// 		clock.restart();
// 	}
// }

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


void SelectShipScreen::Run2(bool& selectionDone) {
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
	//gluLookAt(-1.0,0,2, 0.0,0,0, 0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();


	sf::Event event;
	while(!internalSelectionDone) {
		while( wnd.pollEvent(event)) {
			desktop.HandleEvent(event);
			if ( event.type == sf::Event::Closed) {
				internalSelectionDone = selectionDone = true; //i hope its right assoc.
			}
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		(*shipDisplayList)[currentShip]->render(true);


		desktop.Update(0.0f);
		sfgui.Display(wnd);
		wnd.display();

		selectionDone = internalSelectionDone;
	}

}
#endif