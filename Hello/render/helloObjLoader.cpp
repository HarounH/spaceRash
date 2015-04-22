#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
/*
linker:
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL -lGLU*/
using namespace std;
#include "../../Source/obj_Loader.cpp"

void lettherebelight() {
    float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
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


int main(int argc, char** argv) {
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...
    ObjLoader test("UFO"); //pass name.
    test.LoadObjectFile("untitled.obj");

    test.print(true);
    cout << "#brk1\n";
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,1.33,0.1f,3000.0f);
    
    gluLookAt( 50,0,50,
        0.0,0.0,0.0,
    0,1.0,0);
    lettherebelight();
    
    glViewport(0, 0, 800, 600);
    glFlush();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cout << "#brk2\n";
    // run the main loop
    bool running = true;
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
                glTranslated(x,y,z);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glGetError();
        glPushMatrix();
        glRotatef(45.0f,1.0,0.0,0.0);
        test.render();
        glPopMatrix();
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

    return 0;
}