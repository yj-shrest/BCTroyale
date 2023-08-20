
#include "Bullet.hpp"

    Bullet::Bullet(int  px, int py,int  pw, int ph, SDL::Texture*t,int mx,int my, position cpos):entity(px+cpos.x,py+cpos.y,pw,ph,t)
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
   Bullet:: Bullet(int  px, int py,int  pw, int ph, SDL::Texture*t, float th, position cpos):entity(px+cpos.x,py+cpos.y,pw,ph,t)
{   
    frameposx =px;
    frameposy = py;
    theta =th;
    increment = 20;
    initialpos = position(px,py);
    range = 400;
}
    Bullet::Bullet(int  px, int py,int  pw, int ph, SDL::Texture*t,position cpos):entity(px,py,pw,ph,t)
    {
        frameposx = px;
        frameposy = py;
        initialpos = position(px,py);
        initialpos.y += 50;
        increment = 20;
        range = 400;
        theta = atan2(cpos.y-py+20,cpos.x-px);
    }
    void Bullet::update()
    {   
        frameposx += increment*cos(theta);
        frameposy += increment*sin(theta);
        getframe().x +=increment*cos(theta);
        getframe().y += increment * sin(theta);
    }
    position Bullet::getmouse()
    {
        return position(mousex,mousey);
    }
    float Bullet::gettheta()
    {
        return theta;
    }
    float Bullet::gettheta(int mouseX, int mouseY)
    {
        return atan2(mouseY-420,mouseX-575);
    }
    bool Bullet::hit(std::vector<entity>& platforms)
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
    bool Bullet::hit(std::vector<mob>& mobs)
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
    bool Bullet::hit(Player e)
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
    bool Bullet::isinrange()
    {
        float dx = frameposx - initialpos.x;
        float dy = frameposy - initialpos.y;
        float distance  = std::sqrt(dx * dx + dy * dy);
        if(distance < range) return true;
        else return false;
    }
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
    



