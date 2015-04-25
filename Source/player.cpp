#ifndef PLAYER_CPP
#define PLAYER_CPP
#include "player.hpp"

/*--------TODO: DECIDE ON THE SKY BOX DIMENSIONS---------------*/
SpaceObject* Player::healthPackToRemove = NULL;

Player::Player(ObjManager* mObjManager) {
	//network = new NetworkManager();

	nextSpaceObjId = 0;
	skybox_size = 1024;
	init_bulletWorld();
	settings =  new UserSettings();
	settings->read_settings();
	//SKYBOX_IMG = "Resource/SkyBox/galaxy.png";
	SKYBOX_IMG = "Resource/SkyBox/stormyday.jpg";
	readWorld(WORLD_PHY_FNAME);
	skybox = new SkyBox(SKYBOX_IMG);
	skybox->setImage();
	camera_idx = 0;
	didStart = false;
	startGame = false;
	isDead = false;
	numPlayers = 0;
	numAIs = 0;
	nameAI = "";
	hasSetInitialPosition = false;
	allObjects = mObjManager;
	hasWon = false;
	endGame = false;
}

Player::~Player() {
	music->stop();
	delete music;
	delete network;
	delete skybox;
	allObjects = NULL;
	for ( spaceObjWeed::const_iterator obj_iterator = EveryOne.begin()
			; obj_iterator != EveryOne.end()
			; ++obj_iterator) {
			//--------------------------------
			bulletWorld->dynamicsWorld->removeRigidBody(obj_iterator->right->getRigidBody());
			delete obj_iterator->right;
		}
	delete bulletWorld; //TODO
}
void Player::init_bulletWorld() {
	bulletWorld = new BulletWorld();
}

void Player::init_fighter() {
	fighter = new SpaceObject(fighterType);
	cout << "##brk2\n";
	fighter->init(bulletWorld);
	cout << "##brk3\n";
	fighter->initCommunications(myState , myMessage);
	cout << "##brk4\n";
}



void Player::debug() {

}

void Player::playMusic(bool dflag){
	if(!dflag){
		return;
	}
	bool isSoundThere = false;
    std::string path = MUSIC_RSC_DIR+SW_MUSIC+MUSIC_EXTENSION;
	//sf::Music music;
    music = new sf::Music;
    // cout<<path.c_str()<<"\n";
    // cout<<isSoundThere<<"\n";
    if(music->openFromFile(path.c_str())){
        isSoundThere=true;
    }
    if(isSoundThere){
    // cout<<isSoundThere<<"\n";
    music->play();
    // cout<<isSoundThere<<"\n";
    }
    
}
void Player::update_state(double dt) {
	if(fighter->getHealth()<=0){
		isDead = true;
	}
	if ( healthPackToRemove==NULL ) {
		//pass
	} else {
		bulletWorld->dynamicsWorld->removeRigidBody(healthPackToRemove->getRigidBody());
		removeFromEveryone(healthPackToRemove);
		healthPackToRemove=NULL;
	}
}

void Player::render_state(double dt) {
	bulletWorld->dynamicsWorld->stepSimulation(dt);
	float invmat[16];
	fighter->getTrans(invmat);
	//glm magic.
	glm::mat4 invmattemp = glm::inverse(glm::make_mat4(invmat));
	const float *pSource = (const float*)glm::value_ptr(invmattemp);
	for (int i = 0; i < 16; ++i) {
    	invmat[i] = pSource[i];
	}
	//CAMERA MAGIC FOLLOWS.
	
	glPushMatrix();
	glMultMatrixf(invmat);
		

		skybox->renderBox(skybox_size);
		fighter->render(false,allObjects);
		//render all spaceobjects.
		for ( spaceObjWeed::const_iterator obj_iterator = EveryOne.begin()
			; obj_iterator != EveryOne.end()
			; ++obj_iterator) {
			//--------------------------------
			obj_iterator->right->render(false,allObjects);
		}
	glPopMatrix();
}
void Player::setup_game_screen(double winX, double winY) {
	halfWindowSizeX = winX/2;
	halfWindowSizeY = winY/2;
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//lighting
    float ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float lpos[] = {0.0f, 10.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(settings->fov/2,winX/winY,0.1f,3000.0f);
	toggle_camera(winX, winY);
}

void Player::toggle_camera(double x, double y) {
	camera_idx = (camera_idx + 1)%fighter->cameras.size() ;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// gluLookAt(0,7.5,10, 0,0,0, 0,1.0,0);
	/*gluLookAt( 0.0,0.0,5.0,
        0.0,0.0,0.0,
    	0,1.0,0);*/

	gluLookAt( fighter->cameras[camera_idx].first.getX() , fighter->cameras[camera_idx].first.getY() , fighter->cameras[camera_idx].first.getZ() ,   
		fighter->cameras[camera_idx].second.getX() , fighter->cameras[camera_idx].second.getY() , fighter->cameras[camera_idx].second.getZ() ,   
		0,1.0,0);

	glViewport(0, 0, x, y);
    glFlush();

}


bool Player::add_object(SpaceObject*& OBJ){
	if( addToEveryOne(nextSpaceObjId, OBJ) )
	{
		nextSpaceObjId++;
		return true;
	}
	else
		return false;
}

void Player::removeFromEveryone(SpaceObject* obj) {
	auto it = EveryOne.right.find(obj);
	if (it != EveryOne.right.end()) {
		EveryOne.right.erase(it);
		bulletWorld->dynamicsWorld->removeRigidBody(obj->getRigidBody());
		delete obj;
	}
}

void Player::removeFromEveryone(long long deadClientId) {
	SpaceObject *obj = which_spaceObject(deadClientId);
	removeFromEveryone(obj);
}

SpaceObject* Player::which_spaceObject(int network_int){
	// if present,return
	auto cit = NtoP.left.find(network_int);
	if (cit != NtoP.left.end())
    {
    	int player_int = cit->second;
    	// return spaceobject corresponding to this player_int
    	return getSpaceObject(player_int);
    }
    
    return nullptr;
    /* Assert : no player corresponding to this network int means this spaceObject hasn't yet been added */
}

SpaceObject* Player::which_spaceObject(string playerName) {
	auto cit = NameToP.left.find(playerName);
	if (cit != NameToP.left.end())
    {
    	int player_int = cit->second;
    	// return spaceobject corresponding to this player_int
    	return getSpaceObject(player_int);
    }
    
    return nullptr;
}

string Player::which_player_name(SpaceObject* obj) {
	int pid = getID(obj);
	if(pid != -1)
	{
		auto cit = NameToP.right.find(pid);
		if (cit != NameToP.right.end())
	    {
	    	 return cit->second;
	    }
	}
    
    return "";
}

bool Player::addtoNtoP(int network_int, int player_int) {
	return NtoP.insert(NtoPTypeNormal(network_int,player_int)).second;
}

bool Player::addtoNametoP(string playerName, int player_int) {
	return NameToP.insert(NametoPTypeNormal(playerName,player_int)).second;
}

bool Player::addToEveryOne(int ID,SpaceObject*& OBJ){
	if(!OBJ){
		cout<<"NULL OBJECT PASSED \n";
		return false;
	}
	if((EveryOne.left.insert(spaceObjWeedLeft(ID,OBJ))).second==false){
		cout<<" ID ALREADY TAKEN \n";
		return false;
	}
	return true;
}



bool Player::collisionCallback(btManifoldPoint& cp,
	const btCollisionObjectWrapper* obj1,int id1,int index1,
	const btCollisionObjectWrapper* obj2,int id2,int index2) {

	#define obj1 obj1->getCollisionObject()
	#define obj2 obj2->getCollisionObject()
	((SpaceObject*)(obj1->getUserPointer()))->handleCollision(((SpaceObject*)(obj2->getUserPointer())));
	((SpaceObject*)(obj2->getUserPointer()))->handleCollision(((SpaceObject*)(obj1->getUserPointer())));
	SpaceObject* o1 = ((SpaceObject*)(obj1->getUserPointer()));
	SpaceObject* o2 = ((SpaceObject*)(obj2->getUserPointer()));
	#undef obj1

	#undef obj2

	if(o1->getType()==DEBRIS) {
		healthPackToRemove = o1;
	} else if(o2->getType()==DEBRIS) {
		healthPackToRemove = o2;
	}
	return false;
}

void Player::getNextValidPosition(btVector3& lv) {
	if(didStart)
	{
		int nextPlayer = (int) NtoP.size() + 1;
		lv.setX(0);
		lv.setZ(0);
		if(nextPlayer & 1)
			lv.setY(((nextPlayer + 1) / 2) * 10);
		else
			lv.setY((nextPlayer / 2) * -10);
	}
}

#endif