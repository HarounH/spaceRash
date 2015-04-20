#include "selectShipScreen.hpp"

SelectShipScreen::SelectShipScreen(Player* _usrptr , vector<SpaceObject*>*& displayList) {
	usrptr = _usrptr;
	currentShip = 0;
	leftShift = sfg::Button::Create();
	rightShift = sfg::Button::Create();
	shipDisplayList = displayList;
	startjoin = false;
	//sf::Image leftsfImage;
	//leftsfImage.loadFromFile("");
	//shipName = sfg::Label::Create(shipDisplayList->getName()); // default ship name goes here
	// sfg::Image::Ptr leftsfgImage = sfg::Image::Create(leftsfImage);
	// leftShift->setImage(leftsfgImage);
	//sf::Image rightsfImage;
	//rightsfImage.loadFromFile("");
	// sfg::Image::Ptr rightsfgImage = sfg::Image::Create(rightsfImage);
	// rightShift->setImage(rightsfgImage);
	startJoin = sfg::Button::Create();
	resetSettings = sfg::Button::Create();
	saveSettings = sfg::Button::Create();
	XMouseSense = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	YMouseSense = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	ColourMeter = sfg::Scale::Create(0.f, 1.f, .01f, sfg::Scale::Orientation::HORIZONTAL);
	playerName = sfg::Label::Create("Your Name : ");

	rgbGroup = sfg::RadioButton::RadioButtonGroup::Create();
	RedButton = sfg::RadioButton::Create("Red", rgbGroup);
	GreenButton = sfg::RadioButton::Create("Blue", rgbGroup);
	BlueButton = sfg::RadioButton::Create("Green", rgbGroup);

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

	redName = sfg::Label::Create("Red");
	blueName = sfg::Label::Create("Green");
	greenName = sfg::Label::Create("Blue");
	crossName = sfg::Label::Create("Cross-hair Color");
	xSenseName = sfg::Label::Create("Mouse X");
	ySenseName = sfg::Label::Create("Mouse Y");
}

SelectShipScreen::~SelectShipScreen() {

}

void SelectShipScreen::onRightShiftButtonClick() {
	currentShip++;
	if(currentShip == (int) shipDisplayList->size()) {
		currentShip = 0;
	}

	gluLookAt(0,0,0,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);		
}

void SelectShipScreen::onLeftShiftButtonClick() {
	currentShip --;
	if(currentShip < 0) {
		currentShip = ((int) shipDisplayList->size()) - 1;
	}

	gluLookAt(0,0,0,
		(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getX(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getY(),(*shipDisplayList)[currentShip]->getRigidBody()->getCenterOfMassPosition().getZ(),
		0.0,1.0,0.0
		);	
}

void SelectShipScreen::onStartJoinButtonClick() {
	//go to next window
	startjoin = true;
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
		usrptr->getSettings()->updateKeyMap(key , (KeyboardInput)i );
	}
	usrptr->getSettings()->save_settings();
}

void SelectShipScreen::setupAlignment(std::vector<sfg::Alignment::Ptr>& alignVector) {
	for (int i = 0; i < 13; ++i)
		scaleBox->Pack(alignVector[i], true, false);
	for(int i = 13; i < 19; ++i)
		displayBox->Pack(alignVector[i], true, false);
	for(int i = 19; i < 51; ++i)
		displayBox->Pack(alignVector[i], true, false);
	for(int i = 51; i<54; ++i)
		hugeBox->Pack(alignVector[i], true, false);

	alignVector[0]->Add(xSenseName);
	alignVector[1]->Add(XMouseSense);
	alignVector[2]->Add(ySenseName);
	alignVector[3]->Add(YMouseSense);
	alignVector[4]->Add(crossName);
	alignVector[5]->Add(ColourMeter);
	alignVector[6]->Add(redName);
	alignVector[7]->Add(RedButton);
	alignVector[8]->Add(greenName);
	alignVector[9]->Add(GreenButton);
	alignVector[10]->Add(blueName);
	alignVector[11]->Add(BlueButton);
	alignVector[12]->Add(resetSettings);
	alignVector[13]->Add(playerName);
	alignVector[14]->Add(enterName);
	alignVector[15]->Add(leftShift);
	alignVector[16]->Add(rightShift);
	alignVector[17]->Add(startJoin);
	alignVector[18]->Add(saveSettings);
	
	for(int i = 0, j = 19; i < 16; ++i, j+=2)
	{
		alignVector[j]->Add(userSettingsLabels[i]);
		alignVector[j+1]->Add(userSettingsEntries[i]);
	}

	alignVector[51]->Add(scaleBox);
	alignVector[52]->Add(displayBox);
	alignVector[53]->Add(mapBox);
	
	for(int i = 0; i < 54; i++)
		alignVector[i]->SetScale(sf::Vector2f(0.0f, 0.0f));

	alignVector[0]->SetAlignment(sf::Vector2f(0.8f, 0.1f));
	alignVector[1]->SetAlignment(sf::Vector2f(0.1f, 0.1f));
	alignVector[2]->SetAlignment(sf::Vector2f(0.8f, 0.15f));
	alignVector[3]->SetAlignment(sf::Vector2f(0.1f, 0.15f));
	alignVector[4]->SetAlignment(sf::Vector2f(0.5f, 0.25f));
	alignVector[5]->SetAlignment(sf::Vector2f(0.2f, 0.3f));
	alignVector[6]->SetAlignment(sf::Vector2f(0.8f, 0.4f));
	alignVector[7]->SetAlignment(sf::Vector2f(0.7f, 0.4f));
	alignVector[8]->SetAlignment(sf::Vector2f(0.5f, 0.4f));
	alignVector[9]->SetAlignment(sf::Vector2f(0.4f, 0.4f));
	alignVector[10]->SetAlignment(sf::Vector2f(0.2f, 0.4f));
	alignVector[11]->SetAlignment(sf::Vector2f(0.1f, 0.4f));
	alignVector[12]->SetAlignment(sf::Vector2f(0.25f, 0.8f));
	alignVector[13]->SetAlignment(sf::Vector2f(0.5f, 0.1f));
	alignVector[14]->SetAlignment(sf::Vector2f(0.2f, 0.1f));
	alignVector[15]->SetAlignment(sf::Vector2f(0.8f, 0.7f));
	alignVector[16]->SetAlignment(sf::Vector2f(0.2f, 0.7f));
	alignVector[17]->SetAlignment(sf::Vector2f(0.25f, 0.8f));
	alignVector[18]->SetAlignment(sf::Vector2f(0.25f, 0.8f));

	for(int i = 19; i < 51; i+=2)
	{
		alignVector[i]->SetAlignment(sf::Vector2f(0.7f, 0.1 + ((i-19)*0.04)));
		alignVector[i]->SetAlignment(sf::Vector2f(0.2f, 0.1 + ((i-19)*0.04)));
	}

	alignVector[51]->SetAlignment(sf::Vector2f(0.0f, 0.0f));
	alignVector[52]->SetAlignment(sf::Vector2f(0.25f, 0.0f));
	alignVector[53]->SetAlignment(sf::Vector2f(0.75f, 0.0f));

	// scaleBoxFrame->Add(scaleBox);
	// displayBoxFrame->Add(displayBox);
	// mapBoxFrame->Add(mapBox);

	// hugeBox-


}

void SelectShipScreen::Run() {
	//prepare desktop.
	//align boxes.
	//add stuff here.
	sf::Window wnd( sf::VideoMode(usrptr->getSettings()->defaultScreenSizeX , usrptr->getSettings()->defaultScreenSizeY), "\tSelect Fighter!", sf::Style::Titlebar | sf::Style::Close );
	sfg::SFGUI sfgui;
	auto sfgwindow = sfg::Window::Create();
	
	std::vector<sfg::Alignment::Ptr> alignVector(54);

	for(int i = 0; i < 54; i++)
	{
		//auto tempPtr = sfg::Alignment::Create();
		alignVector[i] = (sfg::Alignment::Create());
		cout << "hi\n";
	}
	cout << "#brk2.05\n";
	setupAlignment(alignVector);
	//add boxes and stuff to window
	sfg::Desktop desktop;
	desktop.Add(sfgwindow);
	sfgwindow->Add(hugeBox);
	cout << "#brk2.1\n";
	sf::Clock clock;




	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (wnd.getPosition().x/(double)wnd.getPosition().y) , 0.01f, 10000.0f);
	gluLookAt(-1.0,0,2, 
		0.0,0,0, 
		0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();


	sf::Event event;
	while( !startjoin ) {
		while( wnd.pollEvent(event) ) {
			desktop.HandleEvent(event);
			if ( event.type == sf::Event::Closed ) {
				startjoin = true;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		//render the selected ship.
		//(*shipDisplayList)[currentShip]->render(true);//TODO
		desktop.Update( clock.restart().asSeconds() );

		sfgui.Display(wnd);
		wnd.display();
		clock.restart();
	}
}