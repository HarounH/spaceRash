using namespace std;

/*LIBS=
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lboost_system -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -lGL
*/


#include "spaceObject.hpp"
#include "player.hpp"
#include "helpers.hpp"

using namespace std;
int main(int argc, char** argv) {
    Player* usr = new Player();
    usr->setFighterType(UFO);
    usr->init_fighter();
    
    std::vector<SpaceObject*>* displayList= new vector<SpaceObject*>(1) ;
    (*displayList)[0] = usr->getFighter();
    
    // cout << "#brk1\n";
    // bool selectionDone=false;
    // SelectShipScreen* selectShipScreen = new SelectShipScreen(usr , displayList);
    // cout << "#brk2\n";
    // selectShipScreen->Run2(selectionDone);
    // StartJoinScreen* startJoinScreen = new StartJoinScreen(usr);
    // startJoinScreen->Run();
    // cout << "#brk3\n";
    

    unsigned short myport, connect_to_port;
    string myip, connect_to_ip;

    double dt = 1.0;
    // if (argc==3) {
    //     //listener.
    //     myport = (unsigned short)atoi(argv[1]);
    //     myip = argv[2];
    //     usr->startNetwork(myip, myport);
    //     usr->started(true);
        
    // } else if ( argc == 5 ) {
    //     //connector.
    //     myport = (unsigned short)atoi(argv[1]);
    //     myip = argv[2];
    //     connect_to_ip = argv[3];
    //     connect_to_port = (unsigned short)atoi(argv[4]);
    //     usr->getFighter()->getRigidBody()->translate(btVector3(0,0,10));
    //     usr->connectToNetwork(connect_to_ip , connect_to_port , myip , myport);
    // } else {
    //     cout << "invalid connection type. EXIT\n";
    //     exit(1);
    // }
    
    sf::Window window(sf::VideoMode(usr->getSettings()->defaultScreenSizeX , usr->getSettings()->defaultScreenSizeY), "spaceRash" , sf::Style::Default, sf::ContextSettings(32));
    usr->setup_game_screen( usr->getSettings()->defaultScreenSizeX , usr->getSettings()->defaultScreenSizeY );
    gContactAddedCallback=(Player::collisionCallback);

    window.setVerticalSyncEnabled(true);
    bool running = true;
    usr->playMusic(true);
    //Player* usr2 = new Player();
    SpaceObject* otr;
    
    // otr = new SpaceObject(UFO);
    // otr->init(usr->getBulletWorld());
    // otr->getRigidBody()->translate(btVector3(0,0,-10));
    // usr->addToEveryOne(1,otr);

    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                usr->setup_game_screen( event.size.width , event.size.height );
                
            }
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                running = false;
            }
            usr->handle_event(event,window);
        }
        usr->resetMouse(window);
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        usr->update_state(dt);
        usr->render_state(dt);
        //---------------------------------------------//
        //usr->getFighter()->render(true);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
        //usr->receiveMessage();
    }
    delete usr;
	return 1;
}