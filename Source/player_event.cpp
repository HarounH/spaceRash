#ifndef PLAYER_EVENT_CPP
#define PLAYER_EVENT_CPP
#include "spaceObject.hpp"
#include "player.hpp"
inline double absolute(double x) {
	return (x*((x>=0)?(1):(-1)));
}
void Player::handle_event(sf::Event& event,sf::Window& window) {
	sf::Keyboard::Key key;
	bool collision, laser;
	rotatePressed = false;
	/*
		Follows the model of : keyboard, mouse.
	*/
	//Rotational
	double tx = sf::Mouse::getPosition(window).x;
    double ty = sf::Mouse::getPosition(window).y;
    //-----------------------------------MAX YAW AND PITCH ALLOWED OF 45 DEGREES. MIN PITCH AND YAW REQUIRED FOR MOVEMENT IS 2 DEGREES--//
    double pitch = (halfWindowSizeY-ty)*(3.0*settings->mouseSensitivity.getY()/halfWindowSizeY) ; //(absolute() > 0.2)?(halfWindowSizeY-ty)*(5.0*settings->mouseSensitivity.getY()/halfWindowSizeY) : 0.0 ;
    if ( !(absolute(pitch)>=0.9) ) {
    	pitch = 0.0;
    }
    double yaw  =  (halfWindowSizeX-tx)*(3.0*settings->mouseSensitivity.getX()/halfWindowSizeX); //(absolute() > 0.2)?(halfWindowSizeX-tx)*(5.0*settings->mouseSensitivity.getX()/halfWindowSizeX) : 0.0 ;
    if (!(absolute(yaw)>=0.9) ) {
    	yaw = 0.0;
    }

    // cout << "pyr=" << pitch << "," << yaw << "\n";
    if(pitch!=0.0 || yaw !=0.0){
    	fighter->rotate(pitch,yaw);
    }
    
	//Translational.
	if( ((key = settings->getKey( ACCELERATE )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->accelerate();
	}
	if( ((key = settings->getKey( DECELERATE )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->decelerate();
	}
	if( ((key = settings->getKey( STRAFE_LEFT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->strafe_left();
	}
	if( ((key = settings->getKey( STRAFE_RIGHT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->strafe_right();
	}
	if( ((key = settings->getKey( ASCEND )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->ascend();
	}
	if( ((key = settings->getKey( DESCEND )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		fighter->descend();
	}
	//rotational.
	if( ((key = settings->getKey( PITCH_UP )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;
		fighter->pitch_up();
	}
	if( ((key = settings->getKey( PITCH_DOWN )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;		
		fighter->pitch_down();
	}
	if( ((key = settings->getKey( YAW_LEFT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;
		fighter->yaw_left();
	}
	if( ((key = settings->getKey( YAW_RIGHT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;
		fighter->yaw_right();
	}
	if( ((key = settings->getKey( ROLL_LEFT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;
		fighter->roll_left();
	}
	if( ((key = settings->getKey( ROLL_RIGHT )) != sf::Keyboard::Unknown) && sf::Keyboard::isKeyPressed(key) ) {
		rotatePressed=true;		
		fighter->roll_right();
	}

	//End of continuous time keyboard handlers.
	//Begin toggles and shit.
	if ( event.type == sf::Event::KeyPressed ) {
		if ( event.key.code == settings->getKey(TOGGLE_FULLSCREEN) ) {
			//what? How. TODO
		} else if ( event.key.code == settings->getKey(TOGGLE_CAM) ) {
			toggle_camera( window.getSize().x , window.getSize().y );
		} else if ( event.key.code == settings->getKey(FIRE_WEAPON) ) {
			fire_laser();
		} else if ( event.key.code == settings->getKey(TOGGLE_WEAPON) ) {
			fighter->toggle_weapon();
		} else if ( event.key.code == settings->getKey(USE_ABILITY) ) {
			//TODO
		} else if ( event.key.code == settings->getKey(ESCAPE) ) {
			//TODO: Move this from the main to the plauer.
		} else if ( event.key.code == settings->getKey(START_CHAT) ) {
			//TODO
		} else if ( event.key.code == settings->getKey(ESCAPE_CHAT) ) {
			//TODO
		} else if ( event.key.code == settings->getKey(SEND_CHAT) ) {
			//TODO
		}
	}
	//WEAPONS
	if ( event.type == sf::Event::MouseButtonPressed ) {
        cout << "trying to shoot. \n";
        fire_laser();
    }
}

void Player::resetMouse(sf::Window& wnd) {
     if(rotatePressed){
     	sf::Vector2i temp(halfWindowSizeX,halfWindowSizeY);
	    sf::Mouse::setPosition(temp,wnd);
     }

}
void Player::fire_laser() {
	fighter->fire_laser();
}
#endif