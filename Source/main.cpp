using namespace std;

/*LIBS=
-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lboost_system -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -lGL
*/


#include "spaceObject.hpp"
#include "player.hpp"
#include "helpers.hpp"
#include "ObjManager.hpp"
#include "HUD.hpp"
#define TICKS 10

using namespace std;
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
int main(int argc, char** argv) {
    //-----------SETTING PATHS TO THE OBJECTS TO BE RENDERED-------//
    vector<string> filePaths(4);
    string img1 = "skyrise_tall.jpg";
    string img2 = "img1.jpg";
    filePaths[0] = OBJ_RSC_DIR+TIEF_FNAME+OBJ_EXTENSION;
    filePaths[1] = OBJ_RSC_DIR+XWING_FNAME+OBJ_EXTENSION;
    filePaths[2] = OBJ_RSC_DIR+ img1; //SKYRISE_TALL_FNAME+OBJ_EXTENSION;
    filePaths[3] = OBJ_RSC_DIR+ img2; //SKYRISE_FAT_FNAME+OBJ_EXTENSION;
    ObjManager* mObjManager;
    // cout << "#brk3\n";
    mObjManager = new ObjManager;
    mObjManager->LoadAllObjects(filePaths);
    //mObjManager->allObjects[0]->print(true);

    //---------------LET THE GAMES BEGIN--------------------------//
    Player* usr = new Player(mObjManager);
    HUD mHud;
    // cout << "#brk1\n";
    // cout << "#brk2\n";
    
    // cout << "#brk3\n";
    std::vector<SpaceObject*>* displayList= new vector<SpaceObject*>(2) ;
    (*displayList)[0] = new SpaceObject(XWING);
    (*displayList)[1] = new SpaceObject(TIE);
    BulletWorld* tempWorld = new BulletWorld();
    (*displayList)[0]->init(tempWorld);
    (*displayList)[1]->init(tempWorld);

    //TODO: Set their centre of mass positions.
    btTransform t0(btQuaternion(0,1,0,0), btVector3(5,0,5));
    btTransform t1(btQuaternion(0,1,0,0), btVector3(-5,0,-5));
    (*displayList)[0]->getRigidBody()->setCenterOfMassTransform(t0);
    (*displayList)[1]->getRigidBody()->setCenterOfMassTransform(t1);
    tempWorld->dynamicsWorld->stepSimulation(1.0f);
    bool selectionDone=false;
    SelectShipScreen* selectShipScreen = new SelectShipScreen(usr , displayList);
    selectShipScreen->Run2(selectionDone,mObjManager);

    for(int i=0; i<2; ++i) {
        tempWorld->dynamicsWorld->removeRigidBody((*displayList)[i]->getRigidBody());
    }
    delete tempWorld;
    
    usr->init_fighter();

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
    
    //sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    sf::RenderWindow window(sf::VideoMode(usr->getSettings()->defaultScreenSizeX , usr->getSettings()->defaultScreenSizeY), "spaceRash" , sf::Style::Default, sf::ContextSettings(32));
    mHud.init(usr,window);
    usr->setup_game_screen( usr->getSettings()->defaultScreenSizeX , usr->getSettings()->defaultScreenSizeY );
    gContactAddedCallback=(Player::collisionCallback);
    // glEnable(GL_DEPTH_TEST);
    // glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);
    
    // lettherebelight();
    
    // glMatrixMode(GL_PROJECTION);
    
    // glLoadIdentity();
    // gluPerspective(90.0f,1.33,0.1f,3000.0f);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // gluLookAt( 0.0,0.0,6.0,
    //     0.0,0.0,0.0,
    // 0,1.0,0);
    
    // glViewport(0, 0, 800, 600);
    // glFlush();

    window.setVerticalSyncEnabled(true);
    bool running = true;
    usr->playMusic(true);
    //Player* usr2 = new Player();
    

    // SpaceObject* otr = new SpaceObject(TIE);
    // otr->init(usr->getBulletWorld());
    // otr->getRigidBody()->translate(btVector3(0,0,-10));
    // usr->add_object(otr);
    double dt1;
    double dt2;
    int ctr=0;
    while (running)
    {
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
        
        glGetError();
        // glEnable(GL_LIGHTING);
        
        /*glPushMatrix();
        // glLoadIdentity();
        glScalef(3.0,3.0,3.0);
        glRotatef(140.0,0.5,1.0,0);
        mObjManager->render(TIE);
        glPopMatrix();*/
       

        mHud.draw(usr->getFighter(), window);
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