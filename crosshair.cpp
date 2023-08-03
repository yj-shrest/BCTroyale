#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"

class Crosshair : public entity{
    public:
    Crosshair(int  px, int py,int  pw, int ph, SDL_Texture*t):entity(px,py,pw,ph,t){}
    void update(int x, int y)
    {
        getframe().x = x;
        getframe().y = y;
    }
};