#include<iostream>
#include<SDL2/SDL.h>
#include <vector>
#include<string>
#include <thread>
#include <jsoncons/json.hpp>

using jsoncons::json;
using namespace std;
#include "position.cpp"
#include "Entity.cpp"
#include "player.cpp"
#include "camera.cpp"
#include "mob.cpp"
#include "Bullet.cpp"
#include "crosshair.cpp"
#include "windowrenderer.cpp"
#include "client.cpp"
#include "server.cpp"

const int width = 1100, height = 700;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(int argc, char *argv[])
{
    Camera camera(width, height);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    //DL_Window *window = SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_ALLOW_HIGHDPI);
    renderwindow window("Minimiltia",width,height);
    SDL_Event windowevent;


    SDL_Texture *background = window.loadTexture("assets/background.png");
    SDL_Texture *rectplatform1 = window.loadTexture("assets/rectplatform1.png");
    SDL_Texture *rectplatform2 = window.loadTexture("assets/rectplatform2.png");
    SDL_Texture *sqplatform = window.loadTexture("assets/sqplatform.png");
    SDL_Texture *healthBarRectTexture = window.loadTexture("assets/healthbarrect.png");
    SDL_Texture *healthBarTexture = window.loadTexture("assets/healthbar.png");
    SDL_Texture *nitroBarTexture = window.loadTexture("assets/nitrobar.png");
    SDL_Texture *gamelogoTexture = window.loadTexture("assets/gamelogo.png");
    SDL_Texture *namemenuTexture = window.loadTexture("assets/namemenu.png");
    SDL_Texture *heartTexture = window.loadTexture("assets/heart.png");
    SDL_Texture *gameoverTexture = window.loadTexture("assets/gameover.png");
    SDL_Texture *modesTexture = window.loadTexture("assets/modes.png");
    SDL_Texture *hostjoinTexture = window.loadTexture("assets/hostjoin.png");
    SDL_Texture *joinbuttonTexture = window.loadTexture("assets/joinbutton.png");
    SDL_Texture *lobbyTexture = window.loadTexture("assets/lobby.png");
    SDL_Texture *mobTexture = window.loadTexture("assets/mob.png");
    SDL_Texture *bulletTexture = window.loadTexture ("assets/bullet.png");
    SDL_Texture *crosshairTexture = window.loadTexture ("assets/crosshair.png");

    entity bg(0,0,3000,1500,background);
    entity bg2(-3000,0,3000,1500,background);
    entity bg3(3000,0,3000,1500,background);
    entity healthbarrect(9,9,202,22,healthBarRectTexture);
    entity nitrobarrect(9,39,202,22,healthBarRectTexture);
    entity healthbar(10,10,200,20,healthBarTexture);
    entity nitrobar(10,40,200,20,nitroBarTexture);
    entity gamelogo(0,0,1100,700,gamelogoTexture);
    entity namemenu(0,0,1100,700,namemenuTexture);
    entity lives(200,9,40,40,heartTexture);
    entity gameOverScreen(0,0,1100,700,gameoverTexture);
    entity modesScreen(0,0,1100,700,modesTexture);
    entity hostjoinScreen(0,0,1100,700,hostjoinTexture);
    entity lobbyScreen(0,0,1100,700,lobbyTexture);
    entity joinbutton(300,300,500,120,joinbuttonTexture);
    Crosshair crosshair(0,0,9,9,crosshairTexture);



    vector <mob> mobs;
    mobs.push_back(mob(1150,680,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
    // mobs.push_back(mob(1600,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
    // mobs.push_back(mob(2350,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));

    vector <entity> platforms; 
    platforms.push_back(entity(100,1000,500,500,sqplatform));
    platforms.push_back(entity(600,1200,230,300,rectplatform2));
    platforms.push_back(entity(970,800,400,200,rectplatform1));
    platforms.push_back(entity(1850,800,400,200,rectplatform1));
    platforms.push_back(entity(1400,1200,500,300,rectplatform1));
    platforms.push_back(entity(2500,1000,500,500,sqplatform));
    platforms.push_back(entity(2270,1200,230,300,rectplatform2));
    Player soloPlayer;
    Player *player = &soloPlayer;
    vector <Player> players;
    vector <Bullet> mybullets;
    vector <Bullet> Enemybullets;
    const int gvalue= 10;
    bool init= false;

    int mousedirection= 1;
    int mouseX, mouseY;
    int clickx,clicky;
    bool leftclick= false;
    bool lefthold = false;
    string textInput = "Type here...";
    bool typing = true;
    int screen = 1;
    bool hitenter = false;
    bool foundgame = false;
    int i =0;
    int j =1;
    int myId;
    bool once= true; 
    bool loop = false;
    Uint32 bulletstart1,bulletstart2;
    bool gamestarted;
    Client c(window);
    Server s(window);
    int number =0;
    while (true)
    { 
        
        frameStart = SDL_GetTicks();
        if (SDL_PollEvent(&windowevent))
        {
            if(SDL_QUIT == windowevent.type)
            {
                break;
            }
            if (windowevent.type == SDL_KEYDOWN)
            {
               if (windowevent.key.keysym.sym == SDLK_LEFT ||windowevent.key.keysym.sym == SDLK_a) {
            (*player).moveSideways(-1);
            }
            else if (windowevent.key.keysym.sym == SDLK_RIGHT || windowevent.key.keysym.sym == SDLK_d ) {
            (*player).moveSideways(1);
            }
            else if (windowevent.key.keysym.sym == SDLK_UP || windowevent.key.keysym.sym == SDLK_w ) {
            (*player).jump();
            }
            else if(windowevent.key.keysym.sym == SDLK_RETURN && (*player).getlives()==0){
                hitenter = true;
            }   

            if (typing) {
                    
                    if (windowevent.key.keysym.sym == SDLK_RETURN) {
                        typing = false; // Finish typing on pressing Enter
                        screen += 1;
                    }
                    else if (windowevent.key.keysym.sym == SDLK_BACKSPACE && textInput.length() > 0) {
                        textInput.pop_back(); // Delete the last character on pressing Backspace
                    }
                }
            }
            else if (windowevent.type == SDL_TEXTINPUT && typing) {
                if(i ==0)
                {
                    textInput = "";
                    i=1;
                }
                textInput += windowevent.text.text; // Append the entered character to the text input
            }
            else if (windowevent.type == SDL_MOUSEBUTTONDOWN) {
            if (windowevent.button.button == SDL_BUTTON_LEFT) {
            int clickx = windowevent.button.x; // X coordinate of the mouse
            int clicky = windowevent.button.y; // Y coordinate of the mouse
            leftclick = true;
            lefthold = true;
            }
            } 
            else if (windowevent.type == SDL_MOUSEBUTTONUP) {
            if (windowevent.button.button == SDL_BUTTON_LEFT) {
            lefthold = false;
            }
            } 
            }
            if (windowevent.type == SDL_KEYUP) {
                if (windowevent.key.keysym.sym == SDLK_LEFT || windowevent.key.keysym.sym == SDLK_RIGHT ||windowevent.key.keysym.sym == SDLK_a ||windowevent.key.keysym.sym == SDLK_d ) {
            (*player).stopMovingSideways();
                }
                if (windowevent.key.keysym.sym == SDLK_UP ||windowevent.key.keysym.sym == SDLK_w )
                {
                    (*player).stopFlying();
                }
        }

        
        window.clear();
        
        if(init)
        {
        window.render(bg,position(0,0)); 
        window.render(gamelogo,position(0,0));
        window.display();
        SDL_Delay(1000);
        init = false;
        }

        if(screen ==1)
        {
            window.render(bg,position(0,0));
            window.render(namemenu,position(0,0));
            window.inputname(textInput);
            window.display();
        }
        else if(screen ==2)
        {   
            if(leftclick)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX>300 && mouseX<800)
                {
                    if(mouseY>270 && mouseY<400)
                    {
                        screen = 3;
                    }
                    if(mouseY>440 && mouseY<560)
                    {
                        screen = 4;
                    }
                }
            }
            window.render(bg,position(0,0));
            window.render(modesScreen,position(0,0));
            window.display();

        }
        else if((*player).getlives()==0)
        {
            if(hitenter)
            {
                (*player).refill();
                hitenter = false;
            }
            window.render(bg,position(0,0));
            window.render(gameOverScreen,position(0,0));
            window.display();
        }
        else if(screen ==3)
        {   
            camera.update(position((*player).getframe().x,(*player).getframe().y));
            SDL_ShowCursor(SDL_DISABLE);
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;

            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(platforms,camera.getPosition()); 
            window.render(mobs, camera.getPosition());
            window.renderplayer(*player,camera.getPosition(),mousedirection,lefthold);
            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));
            window.renderlives((*player),lives);

            window.rendername(textInput);

            if(lefthold)
            {
                if(SDL_GetTicks() -  bulletstart1 >100)
                {

               mybullets.push_back(Bullet(575,420,16,4,bulletTexture,mouseX,mouseY,camera.getPosition()));
               bulletstart1 = SDL_GetTicks();
                }
            }
            window.render(mybullets,camera.getPosition());
            // if(lefthold)
            // {
            // window.render(weaponfire,(*player),mousedirection);
            // }
            // else window.render(weapon,(*player),mousedirection);

            window.render(crosshair,position(0,0));
            std::vector<Bullet> newBullets;
            std::vector<mob> newMobs;


            for (Bullet& b : mybullets) {
                b.update();
                if (!b.hit(platforms) && b.isinrange() &&!b.hit(mobs)) {
                    newBullets.push_back(b);
                }   
            }
            for (mob& m : mobs) {
                if (m.hit(mybullets)) {
                    m.update();
                }  
                 if (!(m.gethp()<0)) {
                    newMobs.push_back(m);
                }  
            }

            // Replace the bullets vector with the new vector
            mybullets = std::move(newBullets);
            mobs = std::move(newMobs);
            
            
            //Mobs firing bullet part:
            float dx = (*player).getpos().x- 1150;
            float dy = (*player).getpos().y- 680;
            float distance  = std::sqrt(dx * dx + dy * dy);
            if(distance<400)
            {

            if(SDL_GetTicks() - bulletstart2>200)
            {
            Enemybullets.push_back(Bullet(1150,680,16,4,bulletTexture,(*player).getpos()));
            bulletstart2 = SDL_GetTicks();
            }
            }
            for (Bullet& b : Enemybullets) 
            {
                b.update();   
            }
            window.render(Enemybullets,camera.getPosition());


            crosshair.update(mouseX,mouseY);
            (*player).update(platforms);
            
            healthbar.updateHealth((*player));
            nitrobar.updatenitro((*player));
            window.display();
        }
        else if(screen ==4)
        {
            if(leftclick)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX>300 && mouseX<800)
                {
                    if(mouseY>200 && mouseY<310)
                    {
                        screen = 5;//host 
                        myId =0;
                    }
                    if(mouseY>360 && mouseY<480)
                    {
                        screen = 6;//join
                        
                    }
                }
            }
            window.render(bg,position(0,0));
            window.render(hostjoinScreen,position(0,0));
            window.display();
        }
        else if(screen ==5)
        {   
            //host lobby
            if(once)
            {
                s.initialize();
                once = false;
            }
            if(players.size()==0) {
                players.push_back(Player(textInput,0));
            }
            json dataIn;
            bool foundInData = false;
            
            window.clear();
            window.render(bg,position(0,0));
            window.render(lobbyScreen,position(0,0));
            SDL_Delay(16);
                        
            s.broadcastingThread(players);
            
            dataIn = s.incomingThread();
            foundInData = dataIn["found"].as_bool();
    
            if(foundInData)
            {   
                cout<<"Player added";
                players.push_back(Player(dataIn["name"].as<std::string>(),j));
                j++;
            }
            int var = 0;
            for(Player &p: players)
            {
            window.rendertext(to_string(p.getid())+". "+p.getname(),position(90,200+var*40));
            var+=1;
            }
            if(leftclick)
            {
                screen = 8;// start game
                once = true;
            }
            window.display();
        }
        else if(screen ==6)
        {
            //searching game
            if(once)
            {
                c.initialize();
                once = false;
            }
            
            window.clear();
            window.render(bg,position(0,0));
            SDL_Delay(16);
                
            foundgame = c.scanningThread();
         if(foundgame)
        {
            window.render(joinbutton,position(0,0));
            if(leftclick)   
            {      
            c.initialize();
            c.sendconfirmation(textInput);
            screen = 7;    
            once = true;
            }
        }
        window.display();
        }
        else if(screen ==7)
        {
            //client lobby
            window.clear();
            window.render(bg,position(0,0));
            window.render(lobbyScreen,position(0,0));
            vector<Player> tempplayers;
            tempplayers = c.receivingThread(gamestarted);
            if(tempplayers.size()!=0) 
            {   
                players.clear();
                for(Player &p : tempplayers)
                players.push_back(p);
            }
            int var = 0;
            for(Player &p: players)
            {
                if(textInput == p.getname()) 
                {
                    myId = p.getid();
                    player = &players[myId];
                }
                window.rendertext(to_string(p.getid())+". "+p.getname(),position(90,200+var*40));
                var+=1;
            }
            if(gamestarted)
            {
                screen = 9; // client game
            }
            window.display();

        }
        else if(screen == 8)
        {   //server Game


            window.clear();
            if(once)
            {
            s.broadcastingStart(players,true);
            for(Player &p: players)
            {
                p.setvalues();
                s.sendInitialData(p);
                player = &players[myId];
            }
            once = false;
            }
            json receivedData = s.receiveData();
            if(receivedData["found"].as_bool())
            {
                int id = receivedData["id"].as<int>();
                int x = receivedData["x"].as<int>();
                int y = receivedData["y"].as<int>();
                int dir = receivedData["dir"].as<int>();
                bool isfiring = receivedData["isfiring"].as_bool();
                float theta = receivedData["theta"].as<float>();
                player[id].updatePosition(x,y,dir);
                if(isfiring)
                {
                    if(SDL_GetTicks() -  bulletstart1 >100)
                {
                    //cout<<theta<<endl;
                    position pos = position (players[id].getframe().x - width/2, players[id].getframe().y - height/2);
                    mybullets.push_back(Bullet(575,420,16,4,bulletTexture,theta,pos));
                    bulletstart1 = SDL_GetTicks();
                }
                }
            }
            SDL_ShowCursor(SDL_DISABLE);
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;

            if(lefthold)
            {
                if(SDL_GetTicks() -  bulletstart1 >100)
                {
                position pos = position (players[myId].getframe().x - width/2, players[myId].getframe().y - height/2);
               mybullets.push_back(Bullet(575,420,16,4,bulletTexture,mouseX,mouseY,pos));
               bulletstart1 = SDL_GetTicks();
                }
            }

            std::vector<Bullet> newBullets;

            for (Bullet& b : mybullets) {
                b.update();
                if (!b.hit(platforms) && b.isinrange()) {
                    newBullets.push_back(b);
                }   
            }
            mybullets = std::move(newBullets);
            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(mybullets,camera.getPosition());
            window.render(platforms,camera.getPosition()); 
            window.render(crosshair,position(0,0));
            for(Player &p : players)
            {
            window.renderplayer(p,camera.getPosition(),p.dir,lefthold);
            }
            // cout<<players[0].getframe().x<<endl;
            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));

            window.rendername(textInput);
            window.display();
            for(Player &p: players)
            {
            p.update(platforms);
            }
            crosshair.update(mouseX,mouseY);
            camera.update(position(players[myId].getframe().x,players[myId].getframe().y));
            if(players[myId].isFlying || players[myId].isMovingSideways || lefthold)
            {
            s.sendData(players[myId],mousedirection,lefthold,lefthold?Bullet::mouseangle(players[myId],mouseX,mouseY):0);
            }
            
        }
        else if(screen == 9)
        { 
            //client game
            window.clear();
            SDL_ShowCursor(SDL_DISABLE);
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;
            if(number!=players.size())
            {

            json dataIn = c.receiveInitialData();
            
            if(dataIn["found"].as_bool())
            {
                int id = dataIn["id"].as<int>();
                int x = dataIn["x"].as<int>();
                int y = dataIn["y"].as<int>();
                players[id].setvalues(x,y);
                number++;
                cout<<number;
            }
            }
                
            else
            {
            json receivedData = c.receiveData();
            if(receivedData["found"].as_bool())
            {
                int id = receivedData["id"].as<int>();
                if(id!=myId)
                {
                int x = receivedData["x"].as<int>();
                int y = receivedData["y"].as<int>();
                int dir = receivedData["dir"].as<int>();
                bool isfiring = receivedData["isfiring"].as_bool();
                float theta = receivedData["theta"].as<float>();
                player[id].updatePosition(x,y,dir);
                if(isfiring)
                {
                    if(SDL_GetTicks() -  bulletstart1 >100)
                {
                    //cout<<theta<<endl;
                    position pos = position (players[id].getframe().x - width/2, players[id].getframe().y - height/2);
                    mybullets.push_back(Bullet(575,420,16,4,bulletTexture,theta,pos));
                    bulletstart1 = SDL_GetTicks();
                }
                }
                }
            }
            }
            
            if(lefthold)
            {
                if(SDL_GetTicks() -  bulletstart1 >100)
                {
                position pos = position (players[myId].getframe().x - width/2, players[myId].getframe().y - height/2);
               mybullets.push_back(Bullet(575,420,16,4,bulletTexture,mouseX,mouseY,pos));
               bulletstart1 = SDL_GetTicks();
                }
            }

            std::vector<Bullet> newBullets;

            for (Bullet& b : mybullets) {
                b.update();
                if (!b.hit(platforms) && b.isinrange()) {
                    newBullets.push_back(b);
                }   
            }
            mybullets = std::move(newBullets);

            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(platforms,camera.getPosition());
            for(Player &p : players)
            {
            window.renderplayer(p,camera.getPosition(),p.dir,lefthold);
            }
            window.render(mybullets,camera.getPosition());

            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));
            window.render(crosshair,position(0,0));
            window.rendername(textInput);
            window.display();
            crosshair.update(mouseX,mouseY);
            for(Player &p: players)
            {
            p.update(platforms);
            }
            camera.update(position(players[myId].getframe().x,players[myId].getframe().y));
            if(players[myId].isFlying || players[myId].isMovingSideways || lefthold)
            {
            c.sendData(players[myId],mousedirection,lefthold,lefthold?Bullet::mouseangle(players[myId],mouseX,mouseY):0);
            }

        }
        leftclick = false;


        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
        }
    }
    window.cleanup();
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
    return 0;
}
