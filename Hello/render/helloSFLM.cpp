#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
/*
linker:
-lsfml-graphics -lsfml-window -lsfml-system -lGL
*/
int main(int argc, char** argv) {
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...

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

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_POLYGON);
        glVertex2f(0.0,0.0);
        glVertex2f(1.0,0.0);
        glVertex2f(0.0,1.0);
        glEnd();
        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}