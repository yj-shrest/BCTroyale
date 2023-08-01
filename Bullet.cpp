#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"

#include<vector>
#include<cmath>
class Bullet : public entity
{   
    int mousex,mousey;
    int increment;
    float theta;
    public:
    Bullet(int  px, int py,int  pw, int ph, SDL_Texture*t,int mx,int my):entity(px,py,pw,ph,t)
{
    mousex = mx;
    mousey = my;
    increment = 10;
    theta = atan2(py-my,mx-px);
}
    void update()
    {
        getframe().x +=increment*cos(theta);
        getframe().y -= increment * sin(theta);
    }
    position getmouse()
    {
        return position(mousex,mousey);
    }
    float gettheta()
    {
        return theta;
    }
};