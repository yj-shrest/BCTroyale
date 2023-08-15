#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>
class Player;
class mob;
class entity
{
    //position pos;
    SDL_Texture* texture;
    const float moveSpeed = 5.0f;
    SDL_Rect currentframe;
    public:
    bool isFlying = false;
    bool isMovingSideways = false;
    int movementDirection = 0;
        entity(float px, float py,float pw, float ph)
    {
        //pos.x = px;
        //pos.y = py;
        currentframe.x =px;
        currentframe.y = py;
        currentframe.w=pw;
        currentframe.h =ph ;
    }
    entity(float px, float py,float pw, float ph, SDL_Texture* t)
    {
        //pos.x = px;
        //pos.y = py;
        texture = t;
        currentframe.x =px;
        currentframe.y = py;
        currentframe.w=pw;
        currentframe.h =ph ;
    }
    
    SDL_Rect& getframe() 
    {
        return currentframe;
    }
     int getspeed()
     {
        return moveSpeed;
     }
    
    SDL_Texture* getTxt()
    {
        return texture;
    }
    void updateHealth(Player &p);
    void updatenitro(Player &p);

};