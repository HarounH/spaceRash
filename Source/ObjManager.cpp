#ifndef OBJ_MANAGER_CPP
#define OBJ_MANAGER_CPP
#include "ObjManager.hpp"
#include "helpers.hpp"
void ObjManager::LoadAllObjects(std::vector<std::string> & filePaths){
	if(filePaths.size()!=4){
		std::cout<<"Improperly used filepaths ";
		return;
	}
    std::vector<float> red(3,0); red[0]=1.0;
    std::vector<float> blue(3,0); blue[2]=1.0;
    std::vector<float> green(3,0); green[1]=1.0;
    colors.push_back(red);
    colors.push_back(blue);
    colors.push_back(green);
    
	allObjects.push_back(new ObjLoader("TIE.FIGHTER"));
	allObjects.push_back(new ObjLoader("X Wing"));
	//allObjects.push_back(new ObjLoader("SKYRISE TALL"));
	//allObjects.push_back(new ObjLoader("SKYRISE FAT"));
	allObjects[0]->LoadObjectFile(filePaths[0].c_str());
	allObjects[1]->LoadObjectFile(filePaths[1].c_str());
    sf::Image* tmp = new sf::Image;
    if(!tmp->loadFromFile(filePaths[2].c_str())){
        std::cout<<"Image nahi banawat hai. Fuggof \n";
        return;
    }
    mBuildingImages.push_back(tmp);
    if(!tmp->loadFromFile(filePaths[3].c_str())){
        std::cout<<"Aww. Ek toh ho gaya. Dusra tera kat gaya :P \n";
        return;
    }
    mBuildingImages.push_back(tmp);
    mBuildingTextures.push_back(new sf::Texture);
    mBuildingTextures.push_back(new sf::Texture);
    if(!mBuildingTextures[0]->loadFromImage(*mBuildingImages[0])){
        std::cout<<"AhlMohst ho gaya. Bas Texture Bind nahi hua \n";
    }
    mBuildingTextures[0]->setRepeated(true);
    if(!mBuildingTextures[1]->loadFromImage(*mBuildingImages[1])){
        std::cout<<"Bahut hi bura kata tumhra toh \n";
    }
    mBuildingTextures[1]->setRepeated(true);
	//allObjects[2]->LoadObjectFile(filePaths[2].c_str());
	//allObjects[3]->LoadObjectFile(filePaths[3].c_str());
}
void ObjManager::drawEndpoint(btVector3 dim) {
    btScalar x,y,z;
    x = dim.getX();
    y = dim.getY();
    z = dim.getZ();
    int c = 0;

    glDisable(GL_LIGHTING);

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);
    glColor3f(colors[c][0],colors[c][1],colors[c][2]);
    glBegin(GL_POLYGON);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);
    glEnd();
    
    //Front face
    glBegin(GL_POLYGON);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);
    glEnd();
    
    //Left face
    glBegin(GL_POLYGON);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glEnd();
    
    //Right face
    glBegin(GL_POLYGON);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);
    glEnd();
    
    //Top face
    glBegin(GL_POLYGON);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);
    glEnd();
    
    //Bottom face
    glBegin(GL_POLYGON);
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, -y, z);
    glVertex3f(-x, -y, z);
    glEnd();

    glColor3f( currentColor[0] , currentColor[1] , currentColor[2] );

    glEnable(GL_TEXTURE_2D);
}
void ObjManager::drawBox(btVector3 dim ,sf::Texture* tex, int c) {
	btScalar x,y,z;
	x = dim.getX();
	y = dim.getY();
	z = dim.getZ();
    glDisable(GL_LIGHTING);
    float currentColor[4];
    glEnable(GL_TEXTURE_2D);
    glGetFloatv(GL_CURRENT_COLOR,currentColor);
    sf::Texture::bind(tex);
    glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP,GL_TRUE);
    //glColor3f(colors[c][0],colors[c][1],colors[c][2]);

    //Back face
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1); glVertex3f(-x, -y, -z);
    glTexCoord2f(1,0); glVertex3f(-x, y, -z);
    glTexCoord2f(0,0); glVertex3f(x, y, -z);
    glTexCoord2f(0,1); glVertex3f(x, -y, -z);
    glEnd();
    
    //Front face
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1); glVertex3f(-x, -y, z);
    glTexCoord2f(1,0); glVertex3f(x, -y, z);
    glTexCoord2f(0,0); glVertex3f(x, y, z);
    glTexCoord2f(0,1); glVertex3f(-x, y, z);
    glEnd();
    
    //Left face
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1); glVertex3f(-x, -y, -z);
    glTexCoord2f(1,0); glVertex3f(-x, -y, z);
    glTexCoord2f(0,0); glVertex3f(-x, y, z);
    glTexCoord2f(0,1); glVertex3f(-x, y, -z);
    glEnd();
    
    //Right face
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1); glVertex3f(x, -y, -z);
    glTexCoord2f(1,0); glVertex3f(x, y, -z);
    glTexCoord2f(0,0); glVertex3f(x, y, z);
    glTexCoord2f(0,1); glVertex3f(x, -y, z);
    glEnd();
    
    //Top face
    glBegin(GL_POLYGON);
    /*glTexCoord2f(1,1); */glVertex3f(-x, y, -z);
    /*glTexCoord2f(1,0); */glVertex3f(-x, y, z);
    /*glTexCoord2f(0,0); */glVertex3f(x, y, z);
    /*glTexCoord2f(0,1); */glVertex3f(x, y, -z);
    glEnd();
    
    //Bottom face
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1); glVertex3f(-x, -y, -z);
    glTexCoord2f(1,0); glVertex3f(x, -y, -z);
    glTexCoord2f(0,0); glVertex3f(x, -y, z);
    glTexCoord2f(0,1); glVertex3f(-x, -y, z);
    glEnd();

    glColor3f( currentColor[0] , currentColor[1] , currentColor[2] );
    sf::Texture::bind(NULL);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void ObjManager::render(OBJECT_TYPE id){
	switch (id){
		case TIE: {
			allObjects[0]->render();
			break;
			}
		case XWING: allObjects[1]->render();
				break;
		case SKYRISE_TALL : {
			// allObjects[2]->render();
			drawBox(btVector3(20,800,20),mBuildingTextures[0] , 1);
			break;
		}
		case SKYRISE_FAT : {
			///allObjects[3]->render();
			drawBox(btVector3(40,650,40),mBuildingTextures[1] , 2);
			break;
		}
        case ENDPOINT : {
            //draw a cyclinder.
            drawEndpoint(btVector3(50,1000,50));
        }
		default: break;
	}

}

#endif