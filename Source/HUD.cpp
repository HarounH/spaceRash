#ifndef HUD_CPP
#define HUD_CPP

#include "HUD.hpp"

//initialize this just before the main loop.
void HUD::init(Player* _usrptr, sf::RenderWindow& wnd) {
	usrptr = _usrptr;
	if (!font.loadFromFile(FONT_FILE)) {
		cout << "error loading font\n";
	} 
	hna.setFont(font);
    hna.setColor(sf::Color::Red);
    hna.setStyle(sf::Text::Bold | sf::Text::Underlined);

	if (!crosshairimg.loadFromFile(CROSSHAIRIMG_FILE)) {
		cout << "error loading crosshair-img\n";
	}
	if (!crosshairtex.loadFromImage(crosshairimg)) {
		cout << "error loading crosshair-tex\n";
	}
	crosshair.setTexture(crosshairtex);
	//TODO: See what colors i get frm usersettings.
	crosshair.setColor(sf::Color(usrptr->getSettings()->HUDCross_r , usrptr->getSettings()->HUDCross_g , usrptr->getSettings()->HUDCross_b , 128));
	crosshair.setScale(sf::Vector2f(0.2,0.2));

	hna.setPosition(sf::Vector2f(wnd.getSize().x-100 , wnd.getSize().y-75 ));
	crosshair.setPosition(sf::Vector2f( wnd.getSize().x/2 - 25 , wnd.getSize().y/2 - 20));

}

void HUD::resize(sf::RenderWindow& wnd) {
	hna.setPosition(sf::Vector2f(wnd.getSize().x-100 , wnd.getSize().y-75 ));
	crosshair.setPosition(sf::Vector2f( wnd.getSize().x/2 , wnd.getSize().y/2 ));
}

void HUD::draw(SpaceObject* refer , sf::RenderWindow& wnd) {
	wnd.pushGLStates();
	hna.setString(L"Hi!\n");
	wnd.draw(hna);
	wnd.draw(crosshair);
	wnd.popGLStates();
}
#endif