#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"

class Weapon : public entity
{
    public:
    Weapon(float px, float py,float pw, float ph, SDL_Texture* t):entity(px,py,pw,ph,t)
    {

    }
    void update()
    {

    }
    position getcentrepos()
    {
        int x, y;
        x = getframe().x +getframe().w/2;
        y = getframe().y +getframe().h/2;
        return position(x,y);
    }
};