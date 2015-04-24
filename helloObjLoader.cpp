#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
/*
linker:
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL -lGLU*/
using namespace std;
#include "Source/obj_Loader.cpp"

void lettherebelight() {
    float ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float lpos[] = {-100.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}
double size=2.0;      

int main(int argc, char** argv) {
    // create the window
    ObjLoader mObjLoader("UFO");
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    lettherebelight();
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    gluPerspective(90.0f,1.33,0.1f,3000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt( 0.0,0.0,5.0,
        0.0,0.0,0.0,
    0,1.0,0);
    
    glViewport(0, 0, 800, 600);
    glFlush();

    window.setVerticalSyncEnabled(true);
    
    // sf::Image* sourceImage = new sf::Image;
    
    // sf::Texture* mTexture = new sf::Texture;
    // sf::Texture* mTexture2;
    
    // load resources, initialize the OpenGL states, ...
    
    mObjLoader.LoadObjectFile("Resource/Render/tie.obj");
    mObjLoader.print(true);
    //     if(sourceImage->loadFromFile("tex3.png")) {
    //         cout << "succesfully read image of size="<< sourceImage->getSize().x << "," << sourceImage->getSize().y << "\n";
    //     }
    //     if (mTexture->loadFromImage(*sourceImage) ) {
    //         cout << "successfully read from image, size=" << mTexture->getSize().x << "," << mTexture->getSize().y << "\n";
    //     }
    // mObjLoader.loadTexture("tex3.jpg",mTexture2);
    
    cout << "#brk1\n";
    
    //glDepthMask(GL_TRUE);
    
    // mObjLoader.vertices.push_back(new coordinate(size/2,size/2,-size/2));
    // mObjLoader.vertices.push_back(new coordinate(-size/2,size/2,-size/2));
    // mObjLoader.vertices.push_back(new coordinate(-size/2,-size/2,-size/2));
    // mObjLoader.vertices.push_back(new coordinate(size/2,-size/2,-size/2));    
    // mObjLoader.textureCoordinates.push_back(new texcoord(0.5,0.34));
    // mObjLoader.textureCoordinates.push_back(new texcoord(0.25,0.34));
    // mObjLoader.textureCoordinates.push_back(new texcoord(0.25,0.65));
    // mObjLoader.textureCoordinates.push_back(new texcoord(0.5,0.65));
    // face mFace;
    // mObjLoader.faces[3]->vertices.resize(4);
    // mObjLoader.faces[3]->vertices[0]= 1;
    // mObjLoader.faces[3]->vertices[1]= 2;
    // mObjLoader.faces[3]->vertices[2]= 3;
    // mObjLoader.faces[3]->vertices[3]= 4;
    // mObjLoader.faces[3]->texcoord.resize(4);
    // mObjLoader.faces[3]->texcoord[0]= 1;
    // mObjLoader.faces[3]->texcoord[1]= 2;
    // mObjLoader.faces[3]->texcoord[2]= 3;
    // mObjLoader.faces[3]->texcoord[3]= 4;
    float diff[3] = {0.64,0.64,0.64};
    float amb[3] = {0.4,0.4,0.4};
    float spec[3] = {0.5,0.5,0.5};
    // mObjLoader.faces[3]->mat = new material(1.0,1.0,96.078431,diff,amb,spec,2,mTexture2);
    cout << "#brk2\n";

    //mObjLoader.print(true); //debugging print.
        // mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->print();
        // mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->print();
        // mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->print();
    //cout << (!(mObjLoader.faces[3]->mat->texture)) << "=nullity lalalala\n";    
    //loadTextureWorks.
        //loadObjFile works.
    //code to try and load a material.    
    bool running=true;
    while(running) {
        sf::Event event;
        while (window.pollEvent(event)){ 
            glGetError();
            if ( event.type==sf::Event::Closed ) {
                running=false;
            }else if ( event.type == sf::Event::KeyPressed ) {
                //a key was pressed.
                double x,y,z; x = y = z = 0;
                if (event.key.code == sf::Keyboard::W) {
                    x += 0.05;
                } else if ( event.key.code ==sf::Keyboard::S) {
                    x -= 0.05;
                }
                glTranslated(x,y,z);
            } else if ( event.type == sf::Event::MouseMoved ) {
                double x,y,z; x = y = z = 0;
                std::cout << "mouseMove=(" << event.mouseMove.x << "," << event.mouseMove.y << ")\n";
                if ( event.mouseMove.x < 50 ) {
                    x -= 0.05;
                } else if ( event.mouseMove.x > 750) {
                    x += 0.05;
                }
                if (event.mouseMove.y < 50 ) {
                    y += 0.05;
                } else if (event.mouseMove.y > 550 ) {
                    y -= 0.05;
                }
                glTranslated(x,y,z);
            }
        }
        glGetError();
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glGetError();
        // glEnable(GL_LIGHTING);
        glPushMatrix();
        // glLoadIdentity();
        glScalef(3.0,3.0,3.0);
        glRotatef(140.0,0.5,1.0,0);
        mObjLoader.render();
        glPopMatrix();
        // glMaterialfv(GL_FRONT,GL_DIFFUSE,mObjLoader.faces[3]->mat->diff);
        // glMaterialfv(GL_FRONT,GL_AMBIENT,mObjLoader.faces[3]->mat->amb);
        // glMaterialfv(GL_FRONT,GL_SPECULAR,mObjLoader.faces[3]->mat->spec);
        
        // glEnable(GL_TEXTURE_2D);
        // //sf::Texture::bind(mTexture2);
        // sf::Texture::bind(mObjLoader.faces[3]->mat->texture);
        // glGetError();
        // glBegin(GL_POLYGON);
        //     glNormal3f(mObjLoader.normals[mObjLoader.faces[3]->normals]->x , mObjLoader.normals[mObjLoader.faces[3]->normals]->y,mObjLoader.normals[mObjLoader.faces[3]->normals]->z);
        //     glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->v);
        //     glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->z);
        //     glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->v);
        //     glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->z);
        //     glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->v);
        //     glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->z);
          
        // glEnd();
        // // glGetError();
        // sf::Texture::bind(NULL);
        // glGetError();
        // glDisable(GL_TEXTURE_2D);
        
    //cout << "!NULL =" << !(mObjLoader.faces[3]->mat->texture);
    //sf::Texture::bind(mTexture);
        //glMaterialfv(GL_FRONT,GL_DIFFUSE,mObjLoader.faces[3]->mat->diff);
        //glMaterialfv(GL_FRONT,GL_AMBIENT,mObjLoader.faces[3]->mat->amb);
        //glMaterialfv(GL_FRONT,GL_SPECULAR,mObjLoader.faces[3]->mat->spec);
         
        
         //glBegin(GL_POLYGON);
         
                 // glTexCoord2f(0.5,0.34);
                 // glVertex3f(size/2,size/2,-size/2);
                 // glTexCoord2f(0.25,0.34);
                 // glVertex3f(-size/2,size/2,-size/2);
                 // glTexCoord2f(0.25,0.65);
                 // glVertex3f(-size/2,-size/2,-size/2);
                 // glTexCoord2f(0.5,0.65);
                 // glVertex3f(size/2,-size/2,-size/2);
         //glNormal3f(0.0,0.0,1.0);
                //cout<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->x<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->y<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->z<<"\n";
                //cout<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->u<<" "<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->v<<"\n\n";
                //glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[0]]->v);
        //         glTexCoord2f(1.0,1.0);
        //         glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[0]]->z);
                
        //         //cout<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->x<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->y<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->z<<"\n";
        //         //cout<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->u<<" "<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->v<<"\n\n";
        //         //glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[1]]->v);
        //         glTexCoord2f(0.5,1.0);
        //         glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[1]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->z);
                
        //         //cout<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->x<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->y<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->z<<"\n";
        //         //cout<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->u<<" "<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->v<<"\n\n";
        //         //glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[2]]->v);
        //         glTexCoord2f(0.5,0.5);
        //         glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[2]]->z);
                
        //         // cout<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->x<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->y<<" "<<mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->z<<"\n";
        //         // cout<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[3]]->u<<" "<<mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[3]]->v<<"\n\n";
        //         // glTexCoord2f(mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[3]]->u,mObjLoader.textureCoordinates[mObjLoader.faces[3]->texcoord[3]]->v);
        //         // glVertex3f(mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->x,mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->y,mObjLoader.vertices[mObjLoader.faces[3]->vertices[3]]->z);
        //  glEnd();
        // sf::Texture::bind(NULL); 
        window.display();  
}
    // run the main loop
    /*bool running = true;
    
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            } else if ( event.type == sf::Event::KeyPressed ) {
                //a key was pressed.
                double x,y,z; x = y = z = 0;
                if (event.key.code == sf::Keyboard::W) {
                    x += 0.05;
                } else if ( event.key.code ==sf::Keyboard::S) {
                    x -= 0.05;
                }
                glTranslated(x,y,z);
            } else if ( event.type == sf::Event::MouseMoved ) {
                double x,y,z; x = y = z = 0;
                //std::cout << "mouseMove=(" << event.mouseMove.x << "," << event.mouseMove.y << ")\n";
                if ( event.mouseMove.x < 50 ) {
                    x -= 0.05;
                } else if ( event.mouseMove.x > 750) {
                    x += 0.05;
                }
                if (event.mouseMove.y < 50 ) {
                    y += 0.05;
                } else if (event.mouseMove.y > 550 ) {
                    y -= 0.05;
                }
                //glTranslated(x,y,z);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glGetError();
        //glRotatef(45.0f,1.0,0.0,0.0);
        
        sf::Texture::bind(test.getTexture());
        //cout << test.getTexture()->getSize().x << "," << test.getTexture()->getSize().y << "= size\n";
        double size = 0.5;
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);      //and draw a face
                //back face
                
                glTexCoord2f(0.0,0.0);      //use the correct texture coordinate
                //glNormal3f(0.0,0.0,1.0);
                glVertex3f(size/2,-size/2,-1);       //and a vertex
                glTexCoord2f(0.0,1.0);
                //glNormal3f(0.0,0.0,1.0);
                glVertex3f(size/2,size/2,-1);
                glTexCoord2f(1.0,1.0);
                //glNormal3f(0.0,0.0,1.0);
                glVertex3f(-size/2,size/2,-1);
                glTexCoord2f(1.0,0.0);      //and repeat it... 
                //glNormal3f(0.0,0.0,1.0);
                glVertex3f(-size/2,-size/2,-1);
        glEnd();
       // test.render();
        sf::Texture::bind(NULL);
        // glBegin(GL_POLYGON);
        // glVertex2f(0.0,0.0);
        // glVertex2f(1.0,0.0);
        // glVertex2f(0.0,1.0);
        // glEnd();
        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    // release resources...

    return 0;*/
    glEnable(GL_TEXTURE_2D);
    sf::Texture::bind(NULL);
    glDisable(GL_TEXTURE_2D);
}