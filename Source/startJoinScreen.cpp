#ifndef START_JOIN_SCREEN_CPP
#define START_JOIN_SCREEN_CPP
#include "startJoinScreen.hpp"

StartJoinScreen::StartJoinScreen(Player*& _usr) {
	usrptr = _usr;
	internalRunning = true;
	
}

StartJoinScreen::~StartJoinScreen() {

}

void StartJoinScreen::onStartButtonClick() {
	std::string myip = myIPEntry->GetText();
	std::string str_myport = myPortEntry->GetText();
	std::string str_nplayers = nPlayersEntry->GetText();
	std::string str_naiplayers = nAIPlayersEntry->GetText();
	if(myip == "" || str_myport == "")
		return;
	unsigned short myport = (unsigned short) stoul(str_myport);
	int numPlayers = (int) stol(str_nplayers);
	int numAIs = (int) stol(str_naiplayers);
	usrptr->setGameMode(myip, myport, true, "", 0, numPlayers, numAIs);
	internalRunning = false;
}

void StartJoinScreen::onJoinButtonClick() {
	std::string myip = myIPEntry->GetText();
	std::string str_myport = myPortEntry->GetText();
	std::string otherip = otherIPEntry->GetText();
	std::string otherport_str = otherPortEntry->GetText() ;
	if(myip == "" || str_myport == "" || otherip == "" || otherport_str == "")
		return;
	unsigned short myport = (unsigned short) stoul(str_myport);
	unsigned short otherport = (unsigned short) stoul(otherport_str);
	usrptr->setGameMode(myip, myport, false, otherip, otherport);
	internalRunning  = false;
}

void StartJoinScreen::Run() {
	sf::Window wnd(sf::VideoMode(270 , 273), "Select your ship!" , sf::Style::Titlebar | sf::Style::Close/*, sf::ContextSettings(32)*/);
	sfg::SFGUI sfgui;

	//Now, to construct all the widgets.
	auto lonelyTable = sfg::Table::Create();

	myIPLabel	    =	sfg::Label::Create("Enter your IP:");
	myPortLabel 	=	sfg::Label::Create("Enter your port:");
	helpLabel 	    =	sfg::Label::Create("Start-Join Screen to setup multiplayer.");
	nPlayersLabel	=	sfg::Label::Create("How Many Players?");
	nAIPlayersLabel	=	sfg::Label::Create("How Many AI Players?");
	myIPEntry	    = 	sfg::Entry::Create();
	myPortEntry 	=	sfg::Entry::Create();
	otrIPLabel   	=	sfg::Label::Create("What's his ip?");
	otrPortLabel 	=	sfg::Label::Create("What's his port?");
	otherIPEntry 	=	sfg::Entry::Create();
	otherPortEntry 	=	sfg::Entry::Create();
	nPlayersEntry 	=	sfg::Entry::Create();
	nAIPlayersEntry	=	sfg::Entry::Create();
	startButton 	=	sfg::Button::Create("Host a round!");
	joinButton	    =	sfg::Button::Create("Join a round.");
	//Sorry for a lack of init functions.
	lonelyTable->SetRowSpacings(5.f);
	lonelyTable->SetColumnSpacings(5.f);
	lonelyTable->Attach(helpLabel , sf::Rect<sf::Uint32>(0,0,2,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(myIPLabel , sf::Rect<sf::Uint32>(0,1,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(myPortLabel , sf::Rect<sf::Uint32>(0,2,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(myIPEntry , sf::Rect<sf::Uint32>(1,1,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(myPortEntry , sf::Rect<sf::Uint32>(1,2,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(nPlayersLabel , sf::Rect<sf::Uint32>(0,3,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(nAIPlayersLabel , sf::Rect<sf::Uint32>(0,4,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(nPlayersEntry , sf::Rect<sf::Uint32>(1,3,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(nAIPlayersEntry , sf::Rect<sf::Uint32>(1,4,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(otrIPLabel , sf::Rect<sf::Uint32>(0,5,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(otrPortLabel , sf::Rect<sf::Uint32>(0,6,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(otherIPEntry , sf::Rect<sf::Uint32>(1,5,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(otherPortEntry , sf::Rect<sf::Uint32>(1,6,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(startButton , sf::Rect<sf::Uint32>(0,7,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );
	lonelyTable->Attach(joinButton , sf::Rect<sf::Uint32>(1,7,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );

	startButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &StartJoinScreen::onStartButtonClick, this ) );
	joinButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &StartJoinScreen::onJoinButtonClick, this ) );

	//ASSERT : Table is ready.
	auto sfgwnd = sfg::Window::Create();
	sfgwnd->SetTitle("Start Game/Join Game");
	sfgwnd->Add(lonelyTable);
	sfg::Desktop desktop;
	desktop.Add(sfgwnd);

	sf::Event event;
	while(internalRunning) {
		while(wnd.pollEvent(event)) {
			desktop.HandleEvent(event);
			if ( event.type == sf::Event::Closed) {
				internalRunning = false;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		desktop.Update(0.0f);
		sfgui.Display(wnd);
		wnd.display();
	}
}
#endif