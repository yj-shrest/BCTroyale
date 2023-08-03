#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"
#include<vector>
class Player: public entity
{   private:
    const int maxhealth=100; 
    int health;
    float nitro;
    SDL_Texture* texture2;
    SDL_Texture* flytexture;
    int mouseX, mouseY;
    int lives = 3;

    public:
    Uint32 lastAnimationUpdateTime = 0;
    Player(float px, float py,float pw, float ph, SDL_Texture* t,SDL_Texture* t2,SDL_Texture* t3):entity(px,py,pw,ph,t)
    {   
        health =100;
        nitro =100;
        texture2 = t2;
        flytexture = t3;
    }
    position getpos()
    {
        return position(getframe().x,getframe().y);
    }
    int getlives()
    {
        return lives;
    }
    void refill()
    {
        lives =3;
    }
    SDL_Texture* getTxt2()
    {
        return texture2;
    }
    SDL_Texture* getflytexture()
    {
        return flytexture;
    }

    void movedown()
    {
        getframe().y+=1;
    }
    void moveSideways(int direction) {
        movementDirection = direction;
        isMovingSideways = true;
    }
    
    void stopMovingSideways() {
        isMovingSideways = false;
    }

    void jump() {
       
        isFlying = true;

    }
    int gethealth()
    {
        return health;
    }
    float getnitro()
    {
        return nitro;
    }
    void stopFlying()
    {
        isFlying = false;
    }

    bool isOnGround(std::vector<entity>& entities)
    {
        for (entity& e : entities)
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
    std::string sidecollision(std::vector<entity>& entities)
    {
        for (entity& e : entities)
        {
            if(e.getframe().y+5<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w) )
                {
                    if(getframe().x<e.getframe().x )
                    {
                        return "leftside";
                    }
                    if(getframe().x+getframe().w >e.getframe().x+e.getframe().w)
                    {
                        return "rightside";
                    }
                }
            }
        }
        return "nth";
    }
    bool upcollide(std::vector<entity>& entities)
    {
        for (entity& e : entities)
        {
            if(e.getframe().y+5<getframe().y+getframe().h && e.getframe().y+e.getframe().h>getframe().y)
            {

                if ( e.getframe().x+30<getframe().x+getframe().w && getframe().x<(e.getframe().x+e.getframe().w-30) )
                {
                    if(-getframe().y<=e.getframe().y +e.getframe().h )
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void update(std::vector<entity>& entities) {
        
        

        if(upcollide(entities))
        {
            isFlying = false;
        }
        if(nitro<=0)
        {
            isFlying = false;
        }
        if(isFlying)
        {
            getframe().y -= getspeed();
            //nitro-=0.5f;
        }
        if(isOnGround(entities))
        {   if(nitro<100)
        {
            nitro += 0.5f;
        }
        
        }
        if(getframe().y>1500)
        {  
            getframe().y = 500;
            nitro = 100;
            lives -=1;
        }
        if(!isFlying && !isOnGround(entities))
        {
            getframe().y+= getspeed();
        }
        if(!isFlying && upcollide(entities))
        {
            getframe() .y += getspeed();
        }
        if (isMovingSideways)
        {
            if(movementDirection ==1 and (sidecollision(entities)!="leftside"))
            {
            getframe().x += movementDirection * getspeed();
            }
            if(movementDirection ==-1 and (sidecollision(entities)!="rightside"))
            {
            getframe().x += movementDirection * getspeed();
            }
        }

    }
};
void entity::updateHealth(Player &p)
{
    currentframe.w = p.gethealth()*2;
}
void entity::updatenitro(Player &p)
{
    currentframe.w = p.getnitro()*2;
}