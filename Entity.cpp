#include"entity.hpp"
   
    entity::entity(){};

    entity::entity(float px, float py,float pw, float ph)
    {
        //pos.x = px;
        //pos.y = py;
        currentframe.x =px;
        currentframe.y = py;
        currentframe.w=pw;
        currentframe.h =ph ;
    }
    void entity::setval(float px, float py)
    {
        currentframe.x = px;
        currentframe.y = py;
        currentframe.w = 75;
        currentframe.h = 100;
    }
    entity::entity(float px, float py,float pw, float ph, SDL::Texture* t)
    {
        //pos.x = px;
        //pos.y = py;
        texture = t;
        currentframe.x =px;
        currentframe.y = py;
        currentframe.w=pw;
        currentframe.h =ph ;
    }
    int entity::getspeed()
    {
        return moveSpeed;
    }
    SDL::Rect& entity::getframe() 
    {
        return currentframe;
    }
    
    SDL::Texture* entity::getTxt()
    {
        return texture;
    }

