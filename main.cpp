#include<iostream>
#include <vector>
#include <string>
#include <jsoncons/json.hpp>
using jsoncons::json;
using namespace std;
#include "SDL.hpp"
#include "position.hpp"
#include "Bullet.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "mob.hpp"
#include "camera.hpp"
#include "crosshair.hpp"
#include "windowrenderer.hpp"
#include "client.hpp"
#include "server.hpp"

const int width = 1100, height = 700;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

int main(int argc, char *argv[])
{
    Camera camera(width, height);
    SDL sdl;
    renderwindow window("BCT ROYALE",width,height);
    SDL::Event windowevent;
    Uint32 frameStart;
    int frameTime;

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    int JetSoundChannel = -1;
    int BulletSoundChannel = -1;
    int WalkingSoundChannel = -1;

    SDL::Texture *background = window.loadTexture("assets/background.png");
    SDL::Texture *rectplatform1 = window.loadTexture("assets/rectplatform1.png");
    SDL::Texture *rectplatform2 = window.loadTexture("assets/rectplatform2.png");
    SDL::Texture *sqplatform = window.loadTexture("assets/sqplatform.png");
    SDL::Texture *healthBarRectTexture = window.loadTexture("assets/healthbarrect.png");
    SDL::Texture *healthBarTexture = window.loadTexture("assets/healthbar.png");
    SDL::Texture *nitroBarTexture = window.loadTexture("assets/nitrobar.png");
    SDL::Texture *gamelogoTexture = window.loadTexture("assets/gamelogo.png");
    SDL::Texture *namemenuTexture = window.loadTexture("assets/namemenu.png");
    SDL::Texture *heartTexture = window.loadTexture("assets/heart.png");
    SDL::Texture *gameoverTexture = window.loadTexture("assets/gameover.png");
    SDL::Texture *modesTexture = window.loadTexture("assets/modes.png");
    SDL::Texture *hostjoinTexture = window.loadTexture("assets/hostjoin.png");
    SDL::Texture *joinbuttonTexture = window.loadTexture("assets/joinbutton.png");
    SDL::Texture *lobbyTexture = window.loadTexture("assets/lobby.png");
    SDL::Texture *lobby2Texture = window.loadTexture("assets/lobby2.png");
    SDL::Texture *mobTexture = window.loadTexture("assets/mob.png");
    SDL::Texture *crosshairTexture = window.loadTexture ("assets/crosshair.png");

    SDL::SoundChunk *walkingSound = Mix_LoadWAV("assets/walking.wav");
    SDL::SoundChunk *bulletSound = Mix_LoadWAV("assets/bullet.mp3");
    SDL::SoundChunk *jetSound = Mix_LoadWAV("assets/jet.mp3");
    SDL::Music* introMusic = Mix_LoadMUS("assets/intromusic.mp3");
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
    entity lobbyScreen2(0,0,1100,700,lobby2Texture);
    entity lobbyScreen(0,0,1100,700,lobbyTexture);
    entity joinbutton(300,300,500,120,joinbuttonTexture);
    Crosshair crosshair(0,0,9,9,crosshairTexture);



    vector <mob> mobs;
    mobs.push_back(mob(1150,680,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
    mobs.push_back(mob(1600,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
    mobs.push_back(mob(2350,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));

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
    bool init= true;

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
    int score =0;
    int myId;
    bool once= true; 
    bool gettinghit = false;
    Uint32 bulletstart1,bulletstart2,respawnTime;
    int secondspassed=0;
    int playersalive;
    bool introMusicPlayed = false;
    bool gamestarted;
    Client c(window);
    Server s(window);
    int number =0;
    while (true)
    { 
        
        frameStart = sdl.getTicks();
        if (sdl.pollEvent(windowevent))
        {
            if(SDL::QUIT == windowevent.type)
            {
                break;
            }
            if (windowevent.type == SDL::KEY_DOWN)
            {
                if ((windowevent.key.keysym.sym == SDL::LEFT || windowevent.key.keysym.sym == SDL::RIGHT) && (*player).isOnGround(platforms))
                {
                    if ((WalkingSoundChannel == -1 || !sdl.isChannelPlaying(WalkingSoundChannel)))
                    {
                         WalkingSoundChannel = sdl.playSoundChannel(walkingSound,-1, -1);
                         
                    }
                }
            }

            if (windowevent.type == SDL::KEY_UP || !(*player).isOnGround(platforms))
            {
                if (windowevent.key.keysym.sym == SDL::LEFT || windowevent.key.keysym.sym == SDL::RIGHT)
                {
                    sdl.haltSoundChannel(WalkingSoundChannel);
                    WalkingSoundChannel = -1;
                }
            }
            if (windowevent.type == SDL::KEY_DOWN)
            {
               if (windowevent.key.keysym.sym == SDL::LEFT ||windowevent.key.keysym.sym == SDL::a) {
            (*player).moveSideways(-1);
            }
            else if (windowevent.key.keysym.sym == SDL::RIGHT || windowevent.key.keysym.sym == SDL::d ) {
            (*player).moveSideways(1);
            }
            else if (windowevent.key.keysym.sym == SDL::UP || windowevent.key.keysym.sym == SDL::w ) {
            (*player).jump();
            if (JetSoundChannel == -1 || !sdl.isChannelPlaying(JetSoundChannel))
                    {
                        JetSoundChannel = sdl.playSoundChannel(jetSound,-1, -1);
                    }
            }
            else if(windowevent.key.keysym.sym == SDL::ENTER && (*player).getlives()==0){
                hitenter = true;
            }   

            if (typing) {
                    
                    if (windowevent.key.keysym.sym == SDL::ENTER) {
                        typing = false; // Finish typing on pressing Enter
                        screen += 1;
                    }
                    else if (windowevent.key.keysym.sym == SDL::BACKSPACE && textInput.length() > 0) {
                        textInput.pop_back(); // Delete the last character on pressing Backspace
                    }
                }
            }
            else if (windowevent.type == SDL::TEXT_INPUT && typing) {
                if(i ==0)
                {
                    textInput = "";
                    i=1;
                }
                textInput += windowevent.text.text; // Append the entered character to the text input
            }
            else if (windowevent.type == SDL::MOUSE_BUTTON_DOWN) {
            if (windowevent.button.button == SDL::BUTTON_LEFT) {
            int clickx = windowevent.button.x; // X coordinate of the mouse
            int clicky = windowevent.button.y; // Y coordinate of the mouse
            leftclick = true;
            lefthold = true;
            }
            } 
            else if (windowevent.type == SDL::MOUSE_BUTTON_UP) {
            if (windowevent.button.button == SDL::BUTTON_LEFT) {
            lefthold = false;
            }
            } 
            }
            if (windowevent.type == SDL::KEY_UP) {
                if (windowevent.key.keysym.sym == SDL::LEFT || windowevent.key.keysym.sym == SDL::RIGHT ||windowevent.key.keysym.sym == SDL::a ||windowevent.key.keysym.sym == SDL::d ) {
            (*player).stopMovingSideways();
                }
                if (windowevent.key.keysym.sym == SDL::UP ||windowevent.key.keysym.sym == SDL::w )
                {
                    (*player).stopFlying();
                    sdl.haltSoundChannel(JetSoundChannel);
                    JetSoundChannel = -1;
                }
        }

        
        window.clear();
        if ((init || screen == 1 || screen == 2 || screen == 4 || 
             screen == 5 || screen == 6 || screen == 7 || screen ==10) && Mix_PlayingMusic() == 0) {
            sdl.playMusic(introMusic, 0);  // Play intro music once
            introMusicPlayed = true;
        }
        if (screen == 3 || screen == 8 || screen == 9) {
            sdl.haltMusic(); // Stop the intro music
        }
        if(init)
        {
        window.render(bg,position(0,0)); 
        window.render(gamelogo,position(0,0));
        window.display();
        sdl.delay(2000);
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
                sdl.getMouseState(&mouseX, &mouseY);
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
        else if(screen ==3)
        {   
        if((*player).getlives()==0)
        {
            if(hitenter)
            {
                (*player).refill();
                score = 0;
                hitenter = false;
                mobs.clear();
                mobs.push_back(mob(1150,680,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
                mobs.push_back(mob(1600,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
                mobs.push_back(mob(2350,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));

            }
            window.render(bg,position(0,0));
            window.render(gameOverScreen,position(0,0));
            window.rendertext("Score:"+to_string(score),position(450,100));
            window.display();
        }
        else{

            camera.update(position((*player).getframe().x,(*player).getframe().y));
            sdl.hideCursor();
            sdl.getMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;

            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(platforms,camera.getPosition()); 
            window.render(mobs, camera.getPosition());
            player->theta = Bullet::gettheta(mouseX,mouseY);
            window.renderplayer(*player,camera.getPosition(),mousedirection);
            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));
            window.renderlives((*player),lives);
            window.rendertext("Score:"+to_string(score),position(500,50));
            window.rendername(textInput);

            if(lefthold)
            {
                player->firing = true;
                if(sdl.getTicks() -  bulletstart1 >100)
                {

               mybullets.push_back(Bullet(575,420,16,4,mouseX,mouseY,camera.getPosition()));
               bulletstart1 = sdl.getTicks();
               sdl.playSoundChunk(bulletSound,-1, 0);
                }
            }
            else{
                player->firing= false;
            }
            window.render(mybullets,camera.getPosition());
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
                else{
                    score +=100;
                }
            }

            // Replace the bullets vector with the new vector
            mybullets = std::move(newBullets);
            mobs = std::move(newMobs);
            
            
            //Mobs firing bullet part:
            for(mob &m : mobs)
            {
            float dx = (*player).getpos().x- m.getframe().x;
            float dy = (*player).getpos().y- m.getframe().y-30;
            float distance  = std::sqrt(dx * dx + dy * dy);
                if(distance<430)
                {
                    gettinghit = true;
                    if(sdl.getTicks() - bulletstart2>100)
                    {
                        Enemybullets.push_back(Bullet(m.getframe().x,m.getframe().y+30,16,4,(*player).getpos()));
                        bulletstart2 = sdl.getTicks();
                         sdl.playSoundChannel(bulletSound,-1, 0);

                    }
                }
            }
            if(!gettinghit)
            {
                player->nodamage();
            }
            gettinghit = false;
            vector<Bullet> newEnemyBullets;
            for (Bullet& b : Enemybullets) {
                b.update();
                if (!b.hit(platforms) && b.isinrange()) {
                    newEnemyBullets.push_back(b);
                }   
            }
            Enemybullets = std::move(newEnemyBullets);
            newEnemyBullets.clear();
            window.render(Enemybullets,camera.getPosition());
            for(Bullet &b :Enemybullets)
            {
            if((*player).hit(b))
            {
                (*player).damage();
            }
            else
            {
                newEnemyBullets.push_back(b);
            }
            }
            if(mobs.size()==0)
            {
                mobs.push_back(mob(1150,680,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
                mobs.push_back(mob(1600,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
                mobs.push_back(mob(2350,1080,120,125,mobTexture,healthBarTexture,healthBarRectTexture));
            }
            Enemybullets = std::move(newEnemyBullets);
            crosshair.update(mouseX,mouseY);
            (*player).update(platforms);
            (*player).respawning = false;
            healthbar.updateHealth((*player));
            nitrobar.updatenitro((*player));
            window.display();
        }
        }
        else if(screen ==4)
        {
            if(leftclick)
            {
                sdl.getMouseState(&mouseX, &mouseY);
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
                sdl.getMouseState(&mouseX, &mouseY);
                if(mouseX>720 && mouseX<1020)
                {
                    if(mouseY>500 && mouseY<610)
                    {
                        screen = 8;// start game
                        once = true;
                    }

                }
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
            foundgame = c.scanningThread();
         if(foundgame)
        {
            window.render(joinbutton,position(0,0));
            if(leftclick)   
            {  
                sdl.getMouseState(&mouseX, &mouseY);
                if(mouseX>joinbutton.getframe().x && mouseX<joinbutton.getframe().x+500)
                {
                    if(mouseY>joinbutton.getframe().y && mouseY<joinbutton.getframe().y+120)
                    {
                        c.sendconfirmation(textInput);
                        screen = 7;    
                        once = true;
                    }

                }    
            }
        }
            window.display();
        }
        else if(screen ==7)
        {
            //client lobby
            window.clear();
            window.render(bg,position(0,0));
            window.render(lobbyScreen2,position(0,0));
            vector<Player> tempplayers;
            tempplayers = c.receivingThread(gamestarted);
            if(tempplayers.size()!=0) 
            {   
                players.clear();
                for(Player &p : tempplayers)
                players.push_back(p);
            }
            int var = 0;
            if(players.size()!=0)
            {

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
        
            if(players[myId].respawning &&!players[myId].died)
            {   
                
                if(sdl.getTicks()-respawnTime >1000)
                {
                    secondspassed+=1; 
                    respawnTime = sdl.getTicks();
                }
                
                window.render(bg,position(0,0));
                int remaintime = 6-secondspassed;
                string remaintimestr = to_string(remaintime); 
                window.rendertext("Respawning in",position(400,300));
                window.rendertext(remaintimestr,position(550,350));
                window.display();
                if(remaintime==0)
                {
                    players[myId].respawning = false;
                    secondspassed =0;
                    s.sendData(players[myId],mousedirection,lefthold,Bullet::gettheta(mouseX,mouseY));
                }
            }
            else if(playersalive ==1 && !players[myId].died)
            {
                window.clear();
                window.render(bg,position(0,0));
                window.rendertext("Victory",position(500,300));
                window.display();
                s.sendData(players[myId],mousedirection,true,0,true);
            }
            else{

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
                bool isflying = receivedData["flying"].as_bool();
                bool respawning = receivedData["respawning"].as_bool();
                bool died = receivedData["died"].as_bool();
                float theta = receivedData["theta"].as<float>();
                bool gameover = receivedData["gameover"].as_bool();
                if(gameover) screen =10;
                player[id].updatePosition(x,y,dir,theta,isfiring,isflying,respawning,died);
                if(isfiring && !players[id].respawning)
                {
                    if(sdl.getTicks() - bulletstart2>100)
                    {
                        position pos = position(players[id].getframe().x-width/2 , players[id].getframe().y-height/2);
                        Enemybullets.push_back(Bullet(575,420,16,4,theta,pos));
                        bulletstart2 = sdl.getTicks();
                        sdl.playSoundChunk(bulletSound,-1, 0);

                    }
                }
            }
            else
            {
                for(Player &p: players)
                {
                    if(p.getid() !=myId)
                    {
                        p.firing = false;
                        p.flying = false;
                    }
                }
            }
            sdl.hideCursor();
            sdl.getMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;

            if(lefthold && !players[myId].respawning)
            {
                if(sdl.getTicks() -  bulletstart1 >100)
                {
                position pos = position (players[myId].getframe().x - width/2, players[myId].getframe().y - height/2);
              
               mybullets.push_back(Bullet(575,420,16,4,mouseX,mouseY,pos));
               bulletstart1 = sdl.getTicks();
               sdl.playSoundChunk(bulletSound,-1, 0);

                }
            }
            std::vector<Bullet> newBullets;
            std::vector<Bullet> newEnemyBullets;

            for (Bullet& b : mybullets) {
                b.update();
                //cout<<b.hit(platforms)<<endl;
                if (!b.hit(platforms) && b.isinrange()) {
                    newBullets.push_back(b);
                }   
            }

            mybullets = std::move(newBullets);

            newBullets.clear();
            for (Bullet& b : Enemybullets) {
                b.update();
                if (!b.hit(platforms) && b.isinrange()) {
                    newEnemyBullets.push_back(b);
                }   
            }
            Enemybullets = std::move(newEnemyBullets);
            newEnemyBullets.clear();
            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(mybullets,camera.getPosition());
            window.render(Enemybullets,camera.getPosition());
            window.render(platforms,camera.getPosition()); 
            window.render(crosshair,position(0,0));
            players[myId].dir =mousedirection; 
            players[myId].theta =Bullet::gettheta(mouseX,mouseY); 
            players[myId].firing =lefthold; 
            for(Bullet &b :Enemybullets)
            {
            if(players[myId].hit(b) && !players[myId].respawning)
            {
                players[myId].damage();
            }
            else
            {
                newEnemyBullets.push_back(b);
            }
            }
            Enemybullets = std::move(newEnemyBullets);
            if(players.size()>1)
            {
            for(Bullet &b :mybullets)
            {
                for(Player &p : players)
                {
                    if(p.getid()!=myId)
                    {
                        if(!b.hit(p))
                        {
                            newBullets.push_back(b);
                        }
                    }
                }
            }
            mybullets = std::move(newBullets);
            }
            for(Player &p : players)
            {
            window.renderplayer(p,camera.getPosition(),p.dir);
            }
            // cout<<players[0].getframe().x<<endl;
            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));

            //window.rendername(textInput);
            window.renderlives(players[myId],lives);
            window.display();
            for(Player &p: players)
            {
                if(!p.respawning)
                {
                    p.update(platforms);
                }
            }
            crosshair.update(mouseX,mouseY);
            healthbar.updateHealth((players[myId]));
            nitrobar.updatenitro((players[myId]));
            camera.update(position(players[myId].getframe().x,players[myId].getframe().y));
            if(players[myId].isFlying || players[myId].isMovingSideways || lefthold || players[myId].respawning)
            {
            s.sendData(players[myId],mousedirection,lefthold,Bullet::gettheta(mouseX,mouseY));
           }
            playersalive =0;
            for(Player &p :players)
            {
                if (!p.died)
                {
                    playersalive +=1;
                }
            }
            }
            
        }
        else if(screen == 9)
        { 
            //client game
            window.clear();
            if(players[myId].respawning &&!players[myId].died)
            {   
                
                if(sdl.getTicks()-respawnTime >1000)
                {
                    secondspassed+=1; 
                    respawnTime = sdl.getTicks();
                }
                
                window.render(bg,position(0,0));
                int remaintime = 6-secondspassed;
                string remaintimestr = to_string(remaintime); 
                window.rendertext("Respawning in",position(400,300));
                window.rendertext(remaintimestr,position(550,350));
                window.display();
                if(remaintime==0)
                {
                    players[myId].respawning = false;
                    secondspassed =0;
                    c.sendData(players[myId],mousedirection,lefthold,Bullet::gettheta(mouseX,mouseY));
                }
            }
            else if(playersalive ==1 && !players[myId].died)
            {
                window.clear();
                window.render(bg,position(0,0));
                window.rendertext("Victory",position(500,300));
                window.display();
                c.sendData(players[myId],mousedirection,true,0,true);
            }
            else{

            sdl.hideCursor();
            sdl.getMouseState(&mouseX, &mouseY);
            if(mouseX<550) mousedirection = -1;
            if(mouseX>=550) mousedirection =1;
            while(number!=players.size())
            {

            json dataIn = c.receiveInitialData();
            
            if(dataIn["found"].as_bool())
            {
                int id = dataIn["id"].as<int>();
                int x = dataIn["x"].as<int>();
                int y = dataIn["y"].as<int>();
                players[id].setvalues(x,y);
                number++;
            }
            }
                
            
            json receivedData = c.receiveData();
            if(receivedData["found"].as_bool())
            {
                int id = receivedData["id"].as<int>();
                int x = receivedData["x"].as<int>();
                int y = receivedData["y"].as<int>();
                int dir = receivedData["dir"].as<int>();
                bool isfiring = receivedData["isfiring"].as_bool();
                bool isflying = receivedData["flying"].as_bool();
                bool respawning = receivedData["respawning"].as_bool();
                bool died = receivedData["died"].as_bool();
                bool gameover = receivedData["gameover"].as_bool();
                if(gameover) screen =10;
                float theta = receivedData["theta"].as<float>();
                if(id!=myId)
                {
                players[id].updatePosition(x,y,dir,theta,isfiring,isflying,respawning,died);
                if(isfiring && !players[id].respawning)
                {
                    if(sdl.getTicks() - bulletstart2>100)
                    {
                        position pos = position(players[id].getframe().x-width/2 , players[id].getframe().y-height/2);
                        Enemybullets.push_back(Bullet(575,420,16,4,theta,pos));
                        bulletstart2 = sdl.getTicks();
                        sdl.playSoundChunk(bulletSound,-1, 0);

                    }
                }
                }
            }
            else
            {
                for(Player &p: players)
                {
                    if(p.getid() !=myId)
                    {
                        p.firing = false;
                        p.flying = false;
                    }
                }
            }
            
            
            if(lefthold && !players[myId].respawning)
            {
                if(sdl.getTicks() -  bulletstart1 >100)
                {
                position pos = position (players[myId].getframe().x - width/2, players[myId].getframe().y - height/2);
               mybullets.push_back(Bullet(575,420,16,4,mouseX,mouseY,pos));
               bulletstart1 = sdl.getTicks();
               sdl.playSoundChunk( bulletSound,-1, 0);

                }
            }

            std::vector<Bullet> newBullets;
            std::vector<Bullet> newEnemyBullets;

            for (Bullet& b : mybullets) 
            {
                b.update();
                if (!b.hit(platforms) && b.isinrange() ) {
                    newBullets.push_back(b);
                }   
            }
            mybullets = std::move(newBullets);
            newBullets.clear();
            for (Bullet& b : Enemybullets) 
            {
                b.update();
                if (!b.hit(platforms) && b.isinrange() ) {
                    newEnemyBullets.push_back(b);
                }   
            }
            Enemybullets = std::move(newEnemyBullets);
            newEnemyBullets.clear();
            window.clear();
            window.render(bg,camera.getPosition()); 
            window.render(bg2,camera.getPosition()); 
            window.render(bg3,camera.getPosition()); 
            window.render(platforms,camera.getPosition());
            players[myId].dir =mousedirection; 
            players[myId].theta =Bullet::gettheta(mouseX,mouseY); 
            players[myId].firing =lefthold; 
            for(Bullet &b :Enemybullets)
            {
            if(players[myId].hit(b) && !players[myId].respawning)
            {
                players[myId].damage();
                //cout<<players[myId].gethealth()<<endl;
            }
            else
            {
                newEnemyBullets.push_back(b);
            }
            }
            Enemybullets = std::move(newEnemyBullets);
            for(Bullet &b :mybullets)
            {
                for(Player &p : players)
                {
                    if(p.getid() !=myId)
                    {
                        if(!b.hit(p))
                        {
                            newBullets.push_back(b);
                        }
                    }
                }
            }
            mybullets = std::move(newBullets);
            for(Player &p : players)
            {
            window.renderplayer(p,camera.getPosition(),p.dir);
            }
            window.render(mybullets,camera.getPosition());
            window.render(Enemybullets,camera.getPosition());

            window.render(healthbarrect,position(0,0));
            window.render(nitrobarrect,position(0,0));
            window.render(healthbar,position(0,0));
            window.render(nitrobar,position(0,0));
            window.render(crosshair,position(0,0));
            //window.rendername(textInput);
            window.renderlives(players[myId],lives);

            window.display();
            healthbar.updateHealth((players[myId]));
            nitrobar.updatenitro((players[myId]));
            crosshair.update(mouseX,mouseY);
            for(Player &p: players)
            {
                if(!p.respawning)
                {
                    p.update(platforms);
                }
            }
            camera.update(position(players[myId].getframe().x,players[myId].getframe().y));
            if(players[myId].isFlying || players[myId].isMovingSideways || lefthold || players[myId].respawning)
            {
            c.sendData(players[myId],mousedirection,lefthold,Bullet::gettheta(mouseX,mouseY));
            }
            playersalive =0;
            for(Player &p :players)
            {
                if (!p.died)
                {
                    playersalive +=1;
                }
            }
            }
        }
        else if(screen ==10)
        {
            window.render(bg,position(0,0));
            window.rendertext("Defeat",position(500,300));
            window.display();
        }
        leftclick = false;
        frameTime = sdl.getTicks() - frameStart;

        if (frameDelay > frameTime) {
        sdl.delay(frameDelay - frameTime);
        }
    }
    sdl.showCursor();

    sdl.destroyTexture(background);
    sdl.destroyTexture(rectplatform1);
    sdl.destroyTexture(rectplatform2);
    sdl.destroyTexture(sqplatform);
    sdl.destroyTexture(healthBarTexture);
    sdl.destroyTexture(nitroBarTexture);
    sdl.destroyTexture(gamelogoTexture);
    sdl.destroyTexture(namemenuTexture);
    sdl.destroyTexture(heartTexture);
    sdl.destroyTexture(gameoverTexture);
    sdl.destroyTexture(modesTexture);
    sdl.destroyTexture(hostjoinTexture);
    sdl.destroyTexture(joinbuttonTexture);
    sdl.destroyTexture(lobbyTexture);
    sdl.destroyTexture(mobTexture);
    sdl.destroyTexture(crosshairTexture);

    Mix_FreeChunk(jetSound);
    Mix_FreeChunk(bulletSound);
    Mix_FreeChunk(walkingSound);
    Mix_FreeMusic(introMusic);

    window.cleanup();
    return 0;
}
