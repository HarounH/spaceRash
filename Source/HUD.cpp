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

	map.setRadius(50.0f);
	map.setFillColor(sf::Color(0,0,0,100));
	map.setPosition(100, wnd.getSize().y-75);

	ep.setRadius(5);
	ep.setFillColor(sf::Color::Green);

	health.setFillColor(sf::Color::Red);
	health.setSize(sf::Vector2f(20.0f,2.0f));
	health.setPosition(wnd.getSize().x/2 - 25 , wnd.getSize().y/2 + 160);


}

void HUD::resize(sf::RenderWindow& wnd, sf::Event& event) {
	//hna.setPosition(sf::Vector2f(wnd.getSize().x-100 , wnd.getSize().y-75 ));
	cout << "setting to=" << event.size.width/2 << "," << event.size.height/2 << "\n";
	//crosshair.setPosition());
	map.setPosition(0.99*event.size.width ,0.05*event.size.height );
	health.setPosition(event.size.width/2 , event.size.height/2);

}

void HUD::draw(SpaceObject* refer , sf::RenderWindow& wnd) {
	wnd.pushGLStates();
	wnd.draw(crosshair);
	health.setSize(sf::Vector2f((float)refer->getHealth()/10.0f,2.0f));

	if (refer->getHealth() > 50) {
		health.setFillColor(sf::Color::Green);
	} else if (refer->getHealth() < 50 ) {
		health.setFillColor(sf::Color::Red);
	}

	btVector3 pos =  quatRotate(refer->getRigidBody()->getOrientation() , btVector3(900,0,-900) - refer->getRigidBody()->getCenterOfMassPosition());
	ep.setPosition( map.getPosition().x +((pos.getX())/100), map.getPosition().y + ((pos.getZ())/100));

	wnd.draw(health);
	wnd.draw(map);
	wnd.draw(ep);
	wnd.popGLStates();
}

#endif