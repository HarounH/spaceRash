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
			regen_rate = 0.0005;
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
	time_left = 10;
	switch (type) {
		case WEAK_LASER   : {
			
				drawProjectile(from,to);
				ammo -= 500; 
				if(ammo<0) ammo=0;
				break;
		}
		case MEDIUM_LASER : {
				drawProjectile(from,to);
				ammo -= 500; 
				if(ammo<0) ammo=0;
				break;
			
		}
		case STRONG_LASER : {
				if(ammo<600)
					break;
				drawProjectile(from,to);
				ammo -= 500; 
				if(ammo<0) ammo=0;
				break;
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
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glColor4f(r,g,b, (float)time_left/10 );
	//polygon on the screen
	glBegin(GL_POLYGON);
	glVertex3f(last_from.getX()-0.05, last_from.getY() - 0.05, last_from.getZ());
	glVertex3f(last_from.getX() +0.05, last_from.getY() - 0.05, last_from.getZ());
	glVertex3f(last_from.getX()+0.05, last_from.getY() + 0.05, last_from.getZ());
	glVertex3f(last_from.getX()-0.05, last_from.getY() - 0.05, last_from.getZ());	
	glEnd();

	//4 polygons for each side to see the laser.
	glBegin(GL_POLYGON);
	glVertex3f(last_from.getX(), last_from.getY() - 0.05, last_from.getZ());
	glVertex3f(last_from.getX(), last_from.getY() + 0.05, last_from.getZ());
	glVertex3f(last_to.getX(), last_to.getY() + 0.05, last_to.getZ());
	glVertex3f(last_to.getX(), last_to.getY() - 0.05, last_to.getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(last_from.getX(), last_from.getY() , last_from.getZ() - 0.05);
	glVertex3f(last_from.getX(), last_from.getY() , last_from.getZ() + 0.05);
	glVertex3f(last_to.getX(), last_to.getY() , last_to.getZ() + 0.05);
	glVertex3f(last_to.getX(), last_to.getY() , last_to.getZ() - 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(last_from.getX(), last_from.getY() + 0.05, last_from.getZ());
	glVertex3f(last_from.getX(), last_from.getY() - 0.05, last_from.getZ());
	glVertex3f(last_to.getX(), last_to.getY() - 0.05, last_to.getZ());
	glVertex3f(last_to.getX(), last_to.getY() + 0.05, last_to.getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(last_from.getX(), last_from.getY() , last_from.getZ() + 0.05);
	glVertex3f(last_from.getX(), last_from.getY() , last_from.getZ() - 0.05);
	glVertex3f(last_to.getX(), last_to.getY() , last_to.getZ() - 0.05);
	glVertex3f(last_to.getX(), last_to.getY() , last_to.getZ() + 0.05);
	glEnd();

	glDisable(GL_BLEND);

	/*
	glLineWidth(strength);
	glBegin(GL_LINES);
		glVertex3f(last_from.getX(), last_from.getY(), last_from.getZ());
		glVertex3f(last_to.getX(), last_to.getY(), last_to.getZ());
	glEnd();*/

	glColor3f( currentColor[0] , currentColor[1] , currentColor[2] );

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

void Weapon::update() {
	ammo  = ammo + (regen_rate*max_ammo);
	if (ammo>max_ammo) { ammo = max_ammo ; }
	drawProjectile(last_from , last_to);
}
#endif