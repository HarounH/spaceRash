#ifndef PLAYER_WORLD_CPP
#define PLAYER_WORLD_CPP
#include "player.hpp"
#include "helpers.hpp"

/*
	World format:
	skybox_size SKYBOX_IMG maxheight
	Endpoint x,y,z
	SkyriseTall x,y,z
	SkyriseFat x,y,z
	Asteroid x,y,z
	Debris x,y,z
*/

//TODO: Add types to helpers.
void Player::readWorld(std::string worldfilepath /*=WORLD_PHY_FNAME*/) {
	std::fstream f(worldfilepath , ios::in);
	if ( !f.is_open() ) {
		std::cout << "i gotcha. invalid file bruh.\n";
	}

	string line1; getline(f,line1);
	std::istringstream lin1(line1);
	lin1 >> skybox_size >> SKYBOX_IMG >> maxHeightWithoutDamage;
	//Now, to do getlines until over.
	string line="";
	int nline=0;
	bool flag = true;
	while(getline(f,line)) {
		//read line into vector.
		std::vector<float> parts;
		std::istringstream s(line);
		float temp2;
		std::string line_type="";
		s >> line_type;
		while(!s.eof()){
			s>>temp2;
			parts.push_back(temp2);
		}
		flag = true;
		//ASSERT : Done reading vector.
		OBJECT_TYPE world_obj_type = UFO;
		if ( line_type == "Endpoint" ) {
			world_obj_type = ENDPOINT;
			goalPos = btVector3(parts[0],0,parts[2]); //set the goal position. 
		} else if ( line_type == "SkyriseTall" ) {
			world_obj_type = SKYRISE_TALL;
		} else if ( line_type == "SkyriseFat" ) {
			world_obj_type = SKYRISE_FAT;
		} else if ( line_type == "Asteroid") {
			world_obj_type = ASTEROID;
		} else if ( line_type == "Debris" ) {
			world_obj_type = DEBRIS;
		} else if (line_type == "AI") {
			flag = false;
		}
		if(flag) {
			SpaceObject* worldObject = new SpaceObject(world_obj_type);
			worldObject->init(bulletWorld);
			worldObject->setPosition( btVector3(parts[0] , parts[1] , parts[2]) );
			bulletWorld->dynamicsWorld->stepSimulation(1/60000.0);
			if (world_obj_type==DEBRIS || world_obj_type==ENDPOINT || world_obj_type==SKYRISE_FAT || world_obj_type==SKYRISE_TALL) {
				worldObject->setStatic();
			}
			add_object(worldObject); //pushes back a copy of the space object. i wonder if that matters.
		} else {
			//its an AI player, put him into a vector for akshay.
			valid_spawn.push_back(btVector3(parts[0],parts[1],parts[2]));
		}
		++nline;
	}
	f.close();
}
#endif