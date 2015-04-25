#ifndef HUD_HPP
#define HUD_HPP

#include "helpers.hpp"
#include "player.hpp"
#include "spaceObject.hpp"

const std::string CROSSHAIRIMG_FILE = "Resource/crosshair.png";
const std::string FONT_FILE = "Resource/Starjedi.ttf";

struct HUD {
	Player* usrptr;
	sf::Font font;
	sf::Text hna;
	sf::Text deathText;
	sf::Text winText;
	sf::Image crosshairimg;
	sf::Texture crosshairtex;
	sf::Sprite crosshair;
	sf::CircleShape map;
	sf::CircleShape ep; //endpoint marker.
	sf::RectangleShape health;
	sf::RectangleShape ammobar;
	int ammoBarSize;
	int healthBarSize;
	void init(Player* _usr,sf::RenderWindow& wnd);
	void resize(sf::RenderWindow& wnd, sf::Event& event);
	void draw(SpaceObject* s, sf::RenderWindow& window);
};
#endif