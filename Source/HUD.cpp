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
	health.setSize(sf::Vector2f(wnd.getSize().x,2.0f));
	health.setPosition(0.0 , wnd.getSize().y/2 + 160);
	healthBarSize = wnd.getSize().x;

}

void HUD::resize(sf::RenderWindow& wnd, sf::Event& event) {
	//hna.setPosition(sf::Vector2f(wnd.getSize().x-100 , wnd.getSize().y-75 ));
	cout << "setting to=" << event.size.width/2 << "," << event.size.height/2 << "\n";
	//crosshair.setPosition());
	map.setPosition(0.99*event.size.width ,0.05*event.size.height );
	health.setPosition(-event.size.width , event.size.height/2 +160);
	healthBarSize = event.size.width;

}

void HUD::draw(SpaceObject* refer , sf::RenderWindow& wnd) {
	wnd.pushGLStates();
	wnd.draw(crosshair);
	//cout<<"SOMETHING FISHY HERE: "<<refer->getHealth()<<"\n";
	float offset = (1000-refer->getHealth())/1000.0;
	health.setPosition(sf::Vector2f(offset/2.0*healthBarSize,health.getPosition().y));
	//cout<<"Lost Health"<<offset/2.0*healthBarSize<<"\n";
	health.setSize(sf::Vector2f((float)refer->getHealth()/1000.0*healthBarSize,2.0f));
	//cout<<"Remaining Health"<<(float)refer->getHealth()/1000.0*healthBarSize;

	if (refer->getHealth() > 500) {
		health.setFillColor(sf::Color::Green);
	} 
	else if (refer->getHealth() <= 500 && refer->getHealth()>=100) {
		health.setFillColor(sf::Color::Yellow);
	}
	else{
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