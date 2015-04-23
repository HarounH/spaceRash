using namespace std;

/*LIBS=
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lboost_system -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -lGL
*/


#include "spaceObject.hpp"
#include "player.hpp"
#include "helpers.hpp"
#include "ObjManager.hpp"
#define TICKS 10

using namespace std;
int main(int argc, char** argv) {
    //-----------SETTING PATHS TO THE OBJECTS TO BE RENDERED-------//
    vector<string> filePaths(4);
    filePaths[0] = OBJ_RSC_DIR+TIEF_FNAME+OBJ_EXTENSION;
    filePaths[1] = OBJ_RSC_DIR+XWING_FNAME+OBJ_EXTENSION;
    filePaths[2] = OBJ_RSC_DIR+SKYRISE_TALL_FNAME+OBJ_EXTENSION;
    filePaths[3] = OBJ_RSC_DIR+SKYRISE_FAT_FNAME+OBJ_EXTENSION;
    ObjManager* mObjManager;
    // cout << "#brk3\n";
    mObjManager = new ObjManager;
    mObjManager->LoadAllObjects(filePaths);

    //---------------LET THE GAMES BEGIN--------------------------//
    Player* usr = new Player(mObjManager);
    cout << "#brk1\n";
    usr->setFighterType(UFO);
    cout << "#brk2\n";
    usr->init_fighter();
    cout << "#brk3\n";
    std::vector<SpaceObject*>* displayList= new vector<SpaceObject*>(1) ;
    (*displayList)[0] = usr->getFighter();
    bool selectionDone=false;
    SelectShipScreen* selectShipScreen = new SelectShipScreen(usr , displayList);
    selectShipScreen->Run2(selectionDone,mObjManager);
    StartJoinScreen* startJoinScreen = new StartJoinScreen(usr);
    startJoinScreen->Run();
    

    unsigned short myport, connect_to_port;
    string myip, connect_to_ip;

    double dt = 0.03;
    {
        sf::Window wnd(sf::VideoMode(150 , 150), "Select your ship!" , sf::Style::Titlebar | sf::Style::Close/*, sf::ContextSettings(32)*/);
        sfg::SFGUI sfgui;
        auto lonelyTable = sfg::Table::Create();
        auto waitLabel = sfg::Label::Create("Waiting...");

        lonelyTable->SetRowSpacings(5.f);
        lonelyTable->SetColumnSpacings(5.f);
        lonelyTable->Attach(waitLabel , sf::Rect<sf::Uint32>(0,0,1,1) , sfg::Table::EXPAND|sfg::Table::FILL ,sfg::Table::EXPAND|sfg::Table::FILL );

        auto sfgwnd = sfg::Window::Create();
        sfgwnd->Add(lonelyTable);
        sfg::Desktop desktop;
        desktop.Add(sfgwnd);
        bool internalRunning = true;
        sf::Event event;
        while(internalRunning) {
            while(wnd.pollEvent(event)) {
                desktop.HandleEvent(event);
                if ( event.type == sf::Event::Closed) {
                    internalRunning = false;
                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            desktop.Update(0.0f);
            sfgui.Display(wnd);
            wnd.display();
            if(usr->started())
            {
                usr->receiveMessage();
                if(usr->numberOfPlayers() == 1)
                {
                    string m = "go";
                    usr->sendMessage(m);
                    internalRunning = false;
                }
            }
            else
            {
                usr->receiveMessage();
                if(usr->beginGame())
                    internalRunning = false;
            }
            if(!internalRunning)
            {
                for(int i = 3; i >= 0; i--)
                {
                    std::string m = "Starting in ";
                    m += to_string(i);
                    waitLabel->SetText(m);
                    usleep(1000000);
                }
            }
        }
    }
    
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
    double dt1;
    double dt2;
    int ctr=0;
    while (running)
    {
        // handle events
        dt1 = clock();

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
        //---------------------------------------------//
        usr->update_state(dt);
        usr->render_state(dt);
        //usr->getFighter()->render(true);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
        if ( ctr%TICKS==0 ) {
            usr->setGeneralData();
            for(int i = 0; i < usr->getNetwork()->numberOfClients(); i++)
                usr->receiveMessage();
        } 
        ctr = (ctr+1)%TICKS ;
        
        dt1 = ((double)(clock() - dt1))/CLOCKS_PER_SEC;
        dt2 = dt1;
        int sleep = (15000) - (dt1 * 1000000);
        if(sleep > 0) {
            usleep((unsigned int) sleep);
        }
    }
    delete usr;
    delete mObjManager;
	return 1;
}