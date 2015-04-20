#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "helpers.hpp"
Weapon::Weapon(WEAPON_TYPE t , btVector3 color) {
	type = t;
	switch (t) {
		case WEAK_LASER   : {
			ammo = max_ammo = 10000; 
			strength = 10;
			break;
		}
		case MEDIUM_LASER : {
			ammo = max_ammo = 5000; 
			strength = 50;
			break;
		}
		case STRONG_LASER : {
			ammo = max_ammo = 1000; 
			strength = 100;
			break;
		}
		default : {
			break;
		}
	}
	r = color.getX();
	g = color.getY();
	b = color.getZ();
	time_left = 0;
}
Weapon::~Weapon() {

}
void Weapon::fireProjectile(btVector3& from, btVector3& to) {
	last_from = from;
	last_to  = to;
	time_left = 500;
	switch (type) {
		case WEAK_LASER   : {
			if (ammo > 100) {
				drawProjectile(from,to);
				ammo -= 100; 
				break;
			}
		}
		case MEDIUM_LASER : {
			if (ammo > 100) {
				drawProjectile(from,to);
				ammo -= 100; 
				break;
			}
		}
		case STRONG_LASER : {
			if (ammo > 100) {
				drawProjectile(from,to);
				ammo -= 100; 
				break;
			}
		}
		default : {
			break;
		}
	}
}

void Weapon::drawProjectile(btVector3& from, btVector3& to) {
	if ( time_left == 0 || (type == FORCE)) {
		return;
	} 
	time_left--;

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);

	glColor3f(r,g,b);
	
	glLineWidth(strength);
	glBegin(GL_LINES);
		glVertex3f(last_from.getX(), last_from.getY(), last_from.getZ());
		glVertex3f(last_to.getX(), last_to.getY(), last_to.getZ());
	glEnd();

	glColor3f( currentColor[0] , currentColor[1] , currentColor[2] );
}

void Weapon::update() {
	if (active) {
		ammo += (regen_rate*max_ammo);
		if (ammo>max_ammo) { ammo = max_ammo ; }
	}
	drawProjectile(last_from , last_to);
}
#endif