#include<iostream>
#include<SDL2/SDL.h>
#include <vector>
#include<string>
using namespace std;
#include"position.cpp"
#include"Entity.cpp"
#include "player.cpp"
#include "weapon.cpp"
#include"camera.cpp"
#include"windowrenderer.cpp"
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
    SDL_Texture *playertexture = window.loadTexture("assets/char.png");
    SDL_Texture *weapontexture = window.loadTexture("assets/weapon.png");
    SDL_Texture *healthBarRectTexture = window.loadTexture("assets/healthbarrect.png");
    SDL_Texture *healthBarTexture = window.loadTexture("assets/healthbar.png");
    SDL_Texture *nitroBarTexture = window.loadTexture("assets/nitrobar.png");
    SDL_Texture *gamelogoTexture = window.loadTexture("assets/gamelogo.png");
    SDL_Texture *namemenuTexture = window.loadTexture("assets/namemenu.png");


    entity bg(0,0,3000,1500,background);
    entity bg2(-3000,0,3000,1500,background);
    entity bg3(3000,0,3000,1500,background);
    entity healthbarrect(9,9,202,22,healthBarRectTexture);
    entity nitrobarrect(9,39,202,22,healthBarRectTexture);
    entity healthbar(10,10,200,20,healthBarTexture);
    entity nitrobar(10,40,200,20,nitroBarTexture);
    entity gamelogo(0,0,1100,700,gamelogoTexture);
    entity namemenu(0,0,1100,700,namemenuTexture);

    vector <entity> platforms; 
    platforms.push_back(entity(100,1000,500,500,sqplatform));
    platforms.push_back(entity(600,1200,230,300,rectplatform2));
    platforms.push_back(entity(970,800,400,200,rectplatform1));
    platforms.push_back(entity(1850,800,400,200,rectplatform1));
    platforms.push_back(entity(1400,1200,500,300,rectplatform1));
    platforms.push_back(entity(2500,1000,500,500,sqplatform));
    platforms.push_back(entity(2270,1200,230,300,rectplatform2));
    Player player(2500,700,75,100,playertexture);
    Weapon weapon(2500,700,50,20,weapontexture);
    const int gvalue= 10;
    bool init= true;

    int mousedirection= 1;
    int mouseX, mouseY;
    
    string textInput = "Type here...";
    bool typing = true;
    bool inputname = false;
    int i =0;
    while (true)
    { 
        camera.update(position(player.getframe().x,player.getframe().y));
        frameStart = SDL_GetTicks();
        if (SDL_PollEvent(&windowevent))
        {
            if(SDL_QUIT == windowevent.type)
            {
                break;
            }
            if (windowevent.type == SDL_KEYDOWN)
            {
               if (windowevent.key.keysym.sym == SDLK_LEFT) {
            player.moveSideways(-1);
            }
            else if (windowevent.key.keysym.sym == SDLK_RIGHT) {
            player.moveSideways(1);
            }
            else if (windowevent.key.keysym.sym == SDLK_UP) {
            player.jump();
            }

            if (typing) {
                    
                    if (windowevent.key.keysym.sym == SDLK_RETURN) {
                        typing = false; // Finish typing on pressing Enter
                        inputname = true;
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
            }
            if (windowevent.type == SDL_KEYUP) {
                if (windowevent.key.keysym.sym == SDLK_LEFT || windowevent.key.keysym.sym == SDLK_RIGHT) {
            player.stopMovingSideways();
                }
                if (windowevent.key.keysym.sym == SDLK_UP)
                {
                    player.stopFlying();
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

        if(inputname == false)
        {
            window.render(bg,position(0,0));
            window.render(namemenu,position(0,0));
            window.inputname(textInput);
            window.display();
        }

        else
        {
        SDL_GetMouseState(&mouseX, &mouseY);
        if(mouseX<550) mousedirection = -1;
        if(mouseX>=550) mousedirection =1;


        window.clear();
        window.render(bg,camera.getPosition()); 
        window.render(bg2,camera.getPosition()); 
        window.render(bg3,camera.getPosition()); 
        window.render(platforms,camera.getPosition()); 
        window.render(player,camera.getPosition(),mousedirection);
        window.render(healthbarrect,position(0,0));
        window.render(nitrobarrect,position(0,0));
        window.render(healthbar,position(0,0));
        window.render(nitrobar,position(0,0));
        window.render(weapon,player,mousedirection);

        window.rendername(textInput);
        player.update(platforms);
        healthbar.updateHealth(player);
        nitrobar.updatenitro(player);
        window.display();
        }


        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
        }
    }
    window.cleanup();
    SDL_Quit();
    return 0;
}
