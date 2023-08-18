#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"

#include<vector>
#include<cmath>
class Bullet : public entity
{   
    int frameposx,frameposy;
    int mousex,mousey;
    int increment;
    float theta;
    position initialpos;
    public:
    bool remove;
    float range;
    Bullet(int  px, int py,int  pw, int ph, SDL_Texture*t,int mx,int my, position cpos):entity(px+cpos.x,py+cpos.y,pw,ph,t)
{   
    frameposx = px;
    frameposy = py;
    mousex = mx+cpos.x;
    mousey = my+cpos.y;
    increment = 20;
    theta = atan2(my-py,mx-px);
    initialpos = position(px,py);
    range = 400;
}
    Bullet(int  px, int py,int  pw, int ph, SDL_Texture*t, float th, position cpos):entity(px+cpos.x,py+cpos.y,pw,ph,t)
{   
    frameposx =px;
    frameposy = py;
    theta =th;
    increment = 20;
    initialpos = position(px,py);
    range = 400;
}
    Bullet(int  px, int py,int  pw, int ph, SDL_Texture*t,position cpos):entity(px,py,pw,ph,t)
    {
        initialpos = cpos;
        initialpos.y += 50;
        increment = 20;
        range = 400;
        theta = atan2(initialpos.y-py,initialpos.x-px);
    }
    void update()
    {   
        frameposx += increment*cos(theta);
        frameposy += increment*sin(theta);
        getframe().x +=increment*cos(theta);
        getframe().y += increment * sin(theta);
    }
    position getmouse()
    {
        return position(mousex,mousey);
    }
    float gettheta()
    {
        return theta;
    }
    static float gettheta(int mouseX, int mouseY)
    {
        return atan2(mouseY-420,mouseX-575);
    }
    bool hit(std::vector<entity>& platforms)
    {
        for (entity& e : platforms)
        {
            if(e.getframe().y<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+5<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-5) )
                {
                return true;
                }
            }
        }
        
        return false;
    }
    bool hit(std::vector<mob>& mobs)
    {
        for (mob& e : mobs)
        {
            if(e.getframe().y<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+5<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-5) )
                {
                return true;
                }
            }
        }
        
        return false;
    }
    bool hit(Player e)
    {
        if(!e.respawning)
        {

            if(e.getframe().y<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+5<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-5) )
                {
                return true;
                }
            }
        }
        
        return false;
    }
    bool isinrange()
    {
        float dx = frameposx - initialpos.x;
        float dy = frameposy - initialpos.y;
        float distance  = std::sqrt(dx * dx + dy * dy);
        if(distance < range) return true;
        else return false;
    }
    
    
};
bool mob::hit(std::vector<Bullet>& bullets)
    {
        for (Bullet& b : bullets)
        {
            if(b.getframe().y<getframe().y+getframe().h && b.getframe().y+b.getframe().h>getframe().y)
            {

                if ( b.getframe().x+5<getframe().x+getframe().w && getframe().x<(b.getframe().x+b.getframe().w-5) )
                {
                return true;
                }
            }
        }
        
        return false;
    }
bool Player::hit(Bullet &b)
    {
        
    if(b.getframe().y<getframe().y+getframe().h && b.getframe().y+b.getframe().h>getframe().y)
        {

            if ( b.getframe().x+5<getframe().x+getframe().w && getframe().x<(b.getframe().x+b.getframe().w-5) )
                {
                return true;
                }
        }
        
        return false;
    }

