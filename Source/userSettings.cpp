#ifndef SETTINGS_CPP
#define SETTINGS_CPP

#include <fstream>
#include <SFML/Window.hpp> //don't need it again.
#include <boost/config.hpp>
#include <string>
#include <boost/bimap.hpp>
#include <btBulletDynamicsCommon.h>
#include <sys/stat.h>
#include "helpers.hpp"
inline bool doesFileExist(std::string fname) {
	struct stat buffer;
	return (stat( fname.c_str() , &buffer ) == 0 );
}

using namespace std;

//class user settings. 
/**
		File Format : 
		player name
		mouseX mouseY mouseZ
		KeyboardInput in one line, in that order <- written as keyboard key.
		DefaultFullScreen, DefaultScreenSizeX, DefaultScreenSizeY
		fov HUDCross_r HUDCross_g HUDCross_b
*/

//unbinds value bound to _key, and sets it.

void UserSettings::updateKeyMap(sf::Keyboard::Key _key , KeyboardInput _action) {
	
	//check if key is bound.
		//if bound, unbind.
	//bind it to action.
	KeyboardMapping::left_iterator keyiter = keyboardMapping.left.find(_key);
	if ( keyiter!= keyboardMapping.left.end() ) {
		keyboardMapping.left.replace_data( keyiter , _action );
	} else {
		keyboardMapping.insert(keymap_type(_key, _action));
	}
}

void UserSettings::updateKeyMapLeft(sf::Keyboard::Key _key , KeyboardInput _action) {
	KeyboardMapping::right_iterator keyiter = keyboardMapping.right.find(_action);
	if ( keyiter!= keyboardMapping.right.end() ) {
		keyboardMapping.right.replace_data( keyiter , _key );
	} else {
		keyboardMapping.insert(keymap_type(_key, _action));
	}
}

KeyboardInput UserSettings::getAction(sf::Keyboard::Key _key) {
	//returns the appropriate action for the given key.
	//see if key is bound. if bound, return action
	//if not bound, return NONE
	KeyboardInput ans = NONE;
	try {
		ans = keyboardMapping.left.at(_key);
	} catch( std::out_of_range& e ) {
	};
	return ans;
}
sf::Keyboard::Key UserSettings::getKey(KeyboardInput _action) {
	//return the appropriate key for the given action.
	//see if action is bound, if bound, return key
	//if not bound, return unknown=-1.
	sf::Keyboard::Key ans = sf::Keyboard::Unknown;
	try {
		ans = keyboardMapping.right.at(_action);
	} catch( std::out_of_range& e ) {
	};
	return ans;
}

void UserSettings::set_default() {
	name = "rookieWookie";
	mouseSensitivity.setX(1.0);
	mouseSensitivity.setY(1.0);
	mouseSensitivity.setZ(0.0);
	//TODO : INSERT DEFAULT VALUES.
	updateKeyMap(sf::Keyboard::W, ACCELERATE);
	updateKeyMap(sf::Keyboard::S, DECELERATE);
	updateKeyMap(sf::Keyboard::A, STRAFE_LEFT);
	updateKeyMap(sf::Keyboard::D, STRAFE_RIGHT);
	updateKeyMap(sf::Keyboard::Q, ASCEND);
	updateKeyMap(sf::Keyboard::E, DESCEND);
	updateKeyMap(sf::Keyboard::I, PITCH_UP);
	updateKeyMap(sf::Keyboard::K, PITCH_DOWN);
	updateKeyMap(sf::Keyboard::J, YAW_LEFT);
	updateKeyMap(sf::Keyboard::L, YAW_RIGHT);
	updateKeyMap(sf::Keyboard::U, ROLL_LEFT);
	updateKeyMap(sf::Keyboard::O, ROLL_RIGHT);
	updateKeyMap(sf::Keyboard::C, TOGGLE_CAM);
	updateKeyMap(sf::Keyboard::G, TOGGLE_WEAPON);
	updateKeyMap(sf::Keyboard::F, TOGGLE_FULLSCREEN);
	updateKeyMap(sf::Keyboard::Escape, ESCAPE);
	fov = 90.0f;
	HUDCross_r = 0.0;
	HUDCross_b = 0.0;
	HUDCross_g = 0.0;
	defaultScreenSizeX = 800;
	defaultScreenSizeY = 600;
}

void UserSettings::read_settings() {
	if (!doesFileExist(SETTINGS_FILE)) {
		set_default();
		save_settings();
		return;
	}
	fstream f(SETTINGS_FILE, ios::in);
	float mx,my,mz;
	f >> name;
	f >> mx ; f>>my; f>>mz; mouseSensitivity.setX(mx); mouseSensitivity.setY(my);mouseSensitivity.setZ(mz); //mouse settings.
	
	//TODO: Insert these values into the bimap.
	
	int kacc , kdec ,kstrl , kstrr , kasc, kdsc 
		, kpthu , kpthd , kyl , kyr , krol , kror
		, ktfscrn, ktcam 
		, kfire ,ktwpn , kabi 
		, kesc 
		, kstartchat , kescapechat , ksndchat ;
	f >> kacc >> kdec >> kstrl >> kstrr >> kasc >> kdsc 
		>> kpthu >> kpthd >> kyl >> kyr >> krol >> kror
		>> ktfscrn >> ktcam 
		>> kfire >> ktwpn >> kabi 
		>> kesc 
		>> kstartchat >> kescapechat >> ksndchat ;
	updateKeyMap((sf::Keyboard::Key)kacc , ACCELERATE);
	updateKeyMap((sf::Keyboard::Key)kdec , DECELERATE);
	updateKeyMap((sf::Keyboard::Key)kstrl , STRAFE_LEFT);
	updateKeyMap((sf::Keyboard::Key)kstrr , STRAFE_RIGHT);
	updateKeyMap((sf::Keyboard::Key)kasc , ASCEND);
	updateKeyMap((sf::Keyboard::Key)kdsc , DESCEND);
	updateKeyMap((sf::Keyboard::Key)kpthu , PITCH_UP);
	updateKeyMap((sf::Keyboard::Key)kpthd , PITCH_DOWN);
	updateKeyMap((sf::Keyboard::Key)kyl , YAW_LEFT);
	updateKeyMap((sf::Keyboard::Key)kyr , YAW_RIGHT);
	updateKeyMap((sf::Keyboard::Key)krol , ROLL_LEFT);
	updateKeyMap((sf::Keyboard::Key)kror , ROLL_RIGHT);

	updateKeyMap((sf::Keyboard::Key)ktfscrn , TOGGLE_FULLSCREEN);
	updateKeyMap((sf::Keyboard::Key)ktcam , TOGGLE_CAM);

	updateKeyMap((sf::Keyboard::Key)kfire , FIRE_WEAPON);
	updateKeyMap((sf::Keyboard::Key)ktwpn , TOGGLE_WEAPON);
	updateKeyMap((sf::Keyboard::Key)kabi , USE_ABILITY);

	updateKeyMap((sf::Keyboard::Key)kesc , ESCAPE);

	updateKeyMap((sf::Keyboard::Key)kstartchat , START_CHAT);
	updateKeyMap((sf::Keyboard::Key)kescapechat , ESCAPE_CHAT);
	updateKeyMap((sf::Keyboard::Key)ksndchat , SEND_CHAT);

	f >> defaultScreenSizeX >> defaultScreenSizeY;
	f >> fov >> HUDCross_r >> HUDCross_b >> HUDCross_g;
	f.close();
}

void UserSettings::save_settings() {
	fstream f(SETTINGS_FILE, ios::out);
	f << name << "\n";
	f << mouseSensitivity.getX() << " " << mouseSensitivity.getY() << " " << mouseSensitivity.getZ() << "\n";
	//TODO : Read these values from the bimap.
	sf::Keyboard::Key kacc , kdec ,kstrl , kstrr , kasc, kdsc 
		, kpthu , kpthd , kyl , kyr , krol , kror
		, ktfscrn, ktcam 
		, kfire ,ktwpn , kabi 
		, kesc 
		, kstartchat , kescapechat , ksndchat ;

	kacc = getKey(ACCELERATE);
	kdec = getKey(DECELERATE);
	kstrl = getKey(STRAFE_LEFT);
	kstrr = getKey(STRAFE_RIGHT);
	kasc = getKey(ASCEND);
	kdsc = getKey(DESCEND);
	kpthu = getKey(PITCH_UP);
	kpthd = getKey(PITCH_DOWN);
	kyl = getKey(YAW_LEFT);
	kyr = getKey(YAW_RIGHT);
	krol = getKey(ROLL_LEFT);
	kror = getKey(ROLL_RIGHT);

	ktfscrn = getKey(TOGGLE_FULLSCREEN);
	ktcam = getKey(TOGGLE_CAM);

	kfire = getKey(FIRE_WEAPON);
	ktwpn = getKey(TOGGLE_WEAPON);
	kabi = getKey(USE_ABILITY);

	kesc = getKey(ESCAPE);

	kstartchat = getKey(START_CHAT);
	kescapechat = getKey(ESCAPE_CHAT);
	ksndchat = getKey(SEND_CHAT);
	f << " " <<  (int)kacc << " " <<  (int)kdec<< " " <<  (int)kstrl << " " << (int)kstrr << " " <<  (int)kasc<< " " <<  (int)kdsc 
		<< " " <<  (int)kpthu << " " <<  (int)kpthd << " " <<  (int)kyl << " " <<  (int)kyr<< " " << (int) krol << " " <<  (int)kror
		<< " " <<  (int)ktfscrn << " " <<  (int)ktcam 
		<< " " <<  (int)kfire<< " " <<  (int)ktwpn << " " <<  (int)kabi 
		<< " " <<  (int)kesc 
		<< " " << (int)kstartchat << " " <<  (int)kescapechat << " " <<  (int)ksndchat << "\n";
	f << defaultScreenSizeX << " " << defaultScreenSizeY << "\n";
	f << fov << " " << HUDCross_r << " " << HUDCross_g << " " << HUDCross_b << "\n";
	f.close();
}
#endif