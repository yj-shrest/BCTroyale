#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"
#include<vector>
class mob: public entity
{
    private:
    int hp;
    public:
    mob (float px, float py,float pw, float ph, SDL_Texture* t):entity(px,py,pw,ph,t){}
};