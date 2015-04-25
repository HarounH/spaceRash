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
	map.setPosition(0.0, wnd.getSize().y-100); //-100 because radius is 50. duh?

	ep.setRadius(5);
	ep.setFillColor(sf::Color::Green);

	health.setFillColor(sf::Color::Red);
	health.setSize(sf::Vector2f(wnd.getSize().x*6.0/10.0,2.0f));
	health.setPosition(20.0/100.0*wnd.getSize().x , wnd.getSize().y/2 + 160);
	healthBarSize = wnd.getSize().x;

	ammobar.setFillColor(sf::Color::Blue);
	ammoBarSize = wnd.getSize().x * 60.0/100.0;
	ammobar.setSize(sf::Vector2f(wnd.getSize().x*6.0/10.0,5.0f));
	ammobar.setPosition(20.0/100.0*wnd.getSize().x , wnd.getSize().y/2 + 170);
	

}

void HUD::resize(sf::RenderWindow& wnd, sf::Event& event) {
	//hna.setPosition(sf::Vector2f(wnd.getSize().x-100 , wnd.getSize().y-75 ));
	cout << "setting to=" << event.size.width/2 << "," << event.size.height/2 << "\n";
	//crosshair.setPosition());
	map.setPosition(0.99*event.size.width ,0.05*event.size.height );
	health.setPosition(-event.size.width , event.size.height/2 +160);
	healthBarSize = event.size.width;
	ammoBarSize = healthBarSize * 6.0/10.0;

}

void HUD::draw(SpaceObject* refer , sf::RenderWindow& wnd) {
	wnd.pushGLStates();
	wnd.draw(crosshair);
	
	float offset_health =((0.2)+float((1000.0-refer->getHealth()))/1000.0*0.3)*healthBarSize;
	
	float offset_ammo = ((0.2) + float((5000 - refer->getActiveWeapon()->ammo))/5000.0*0.3)*healthBarSize;
	health.setPosition(sf::Vector2f(offset_health,health.getPosition().y));
	health.setSize(sf::Vector2f((float)refer->getHealth()/1000.0*ammoBarSize,2.0f));
	

	ammobar.setPosition(sf::Vector2f(offset_ammo,ammobar.getPosition().y));
	
	ammobar.setSize(sf::Vector2f(float(refer->getActiveWeapon()->ammo)/5000.0*ammoBarSize,2.0f));
	
	if (refer->getHealth() > 500) {
		health.setFillColor(sf::Color::Green);
	} 
	else if (refer->getHealth() <= 500 && refer->getHealth()>=250) {
		health.setFillColor(sf::Color::Yellow);
	}
	else{
		health.setFillColor(sf::Color::Red);
	}
	if (refer->getActiveWeapon()->ammo<600)
		ammobar.setFillColor(sf::Color::Cyan);
	else
		ammobar.setFillColor(sf::Color::Blue);


	btVector3 u = quatRotate(refer->getRigidBody()->getOrientation() , btVector3(0,0,-1)); //direction of my front-side.
	btVector3 uprime(u.getX(), 0 , u.getZ());
	btVector3 v = btVector3(900,0,-900) - refer->getRigidBody()->getCenterOfMassPosition();
		v.setY(0);
	btScalar d = btAngle(uprime,v);
	btScalar z1 = uprime.getZ();
	float mX,mY;
	int r;
	if(v.length2()>1000000.0)
		r = 45;
	else
		r = 45*(v.length2())/1000000.0;
	btVector3 cross = btCross(uprime,v);
	if(cross.getY()<0){
		//-------------------SAME SIDE--------------------//
		if(d<(3.14159/2.0)){
			mX = r*sin(d);
			mY = -r*cos(d);
		}
		else{
			d = (3.14159 - d);
			mX = r*sin(d);
			mY = r*cos(d);
		}

	}
	else{
		//--------------OPPOSIDE SIDE--------------//
		if(d<(3.14159/2.0)){
			mX = -r*(sin(d));
			mY = -r*cos(d);
		}
		else{
			d = 3.14159-d;
			mX = -r*(sin(d));
			mY = r*cos(d);
		}
	}
	
	btVector3 pos =  quatRotate(refer->getRigidBody()->getOrientation() , btVector3(900,0,-900) - refer->getRigidBody()->getCenterOfMassPosition());
	ep.setPosition( map.getPosition().x + 45 + mX , map.getPosition().y +45 + mY);
	wnd.draw(ammobar);
	wnd.draw(health);

	wnd.draw(map);
	wnd.draw(ep);
	wnd.popGLStates();
}

#endif