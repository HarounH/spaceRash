#ifndef skybox_cpp
#define skybox_cpp
#include "skybox.hpp"
#include <iostream>
SkyBox::SkyBox(const std::string &path){
	imgPath = path;
}

SkyBox::~SkyBox(){
	delete texture;
	delete box;
}
void SkyBox::setImage(){
	box = new sf::Image;
	if(!box->loadFromFile(imgPath)){
		std::cout<<"ERROR: IMAGE DID NOT LOAD \n";
		return;
	}
	texture = new sf::Texture;
	if(!texture->loadFromImage(*box)){
		std::cout<<"ERROR: TEXTURE CANNOT BE LOADED \n";
		return;
	}
}
void SkyBox::renderBox(float size){
	
    bool btex=glIsEnabled(GL_TEXTURE_2D);     
    bool blight=glIsEnabled(GL_LIGHTING);
    bool bdepth=glIsEnabled(GL_DEPTH_TEST);


    glDisable(GL_LIGHTING); 		//turn off lighting, when making the skybox
	//glDisable(GL_DEPTH_TEST);       //turn off depth texting
    glEnable(GL_TEXTURE_2D);        //and turn on texturing

    sf::Texture::bind(texture);

	glBegin(GL_QUADS);      //and draw a face
                //back face
                glTexCoord2f(0.75,0.34);      //use the correct texture coordinate
                glVertex3f(size/2,size/2,size/2);       //and a vertex
                glTexCoord2f(0.75,0.65);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(1.0,0.65);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(1.0,0.34);      //and repeat it... 
                glVertex3f(-size/2,size/2,size/2);
        glEnd();
        glBegin(GL_QUADS);     
                //left face
                 glTexCoord2f(0.25,0.34);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0,0.34);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0,0.65);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(0.25,0.65);
                glVertex3f(-size/2,-size/2,-size/2);
               
        glEnd();
        

        glBegin(GL_QUADS);     
                //front face
                glTexCoord2f(0.5,0.34);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(0.25,0.34);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0.25,0.65);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0.5,0.65);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        

        glBegin(GL_QUADS);     
                //right face
                glTexCoord2f(0.75,0.34);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0.50,0.34);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(0.5,0.65);
                glVertex3f(size/2,-size/2,-size/2);
                glTexCoord2f(0.75,0.65);
                glVertex3f(size/2,-size/2,size/2);
                
        glEnd();
        

        glBegin(GL_QUADS);                      //top face
                glTexCoord2f(0.5,0);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0.25,0);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0.25,0.34);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0.5,0.34);
                glVertex3f(size/2,size/2,-size/2);
        glEnd();
        
;               
        glBegin(GL_QUADS);     
                //bottom face
                glTexCoord2f(0.5,1);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(0.5,0.65);
                glVertex3f(size/2,-size/2,-size/2);
                glTexCoord2f(0.25,0.65);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0.25,1);
                glVertex3f(-size/2,-size/2,size/2);
        glEnd();
        glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
        glEnable(GL_DEPTH_TEST);
        sf::Texture::bind(NULL);

        //restoring gl context :)
        if ( btex ) {
            glEnable(GL_TEXTURE_2D);
        } else {
            glDisable(GL_TEXTURE_2D);
        }

        if( blight ) {
            glEnable(GL_LIGHTING);
        } else {
            glDisable(GL_LIGHTING);
        }

        if ( bdepth ) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
}
#endif