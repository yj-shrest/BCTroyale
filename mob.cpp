#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.cpp"
#include<vector>
class Bullet;
class mob: public entity
{
    private:
    int hp;
    SDL_Texture *hptexture;
    SDL_Texture *hprecttexture;
    SDL_Rect rectframebig;
    SDL_Rect rectframesmall;
    public:
    mob (float px, float py,float pw, float ph, SDL_Texture* mobtext,SDL_Texture* hptxt,SDL_Texture* recttext ):entity(px,py,pw,ph,mobtext)
    {
        hp = 100;
        hptexture = hptxt;
        hprecttexture = recttext;
        rectframebig.x = px+10; 
        rectframebig.y = py-20; 
        rectframebig.w = 102; 
        rectframebig.h = 12; 

        rectframesmall.x = rectframebig.x +1;
        rectframesmall.y = rectframebig.y +1;
        rectframesmall.w = rectframebig.w -2;
        rectframesmall.h = rectframebig.h -2;
    }
    SDL_Rect& getsmallrect()
    {
        return rectframesmall;
    }
    SDL_Rect& getbigrect()
    {
        return rectframebig;
    }
    SDL_Texture* getrecttxt()
    {
        return hprecttexture;
    }
    SDL_Texture* gethptxt()
    {
        return hptexture;
    }
    int gethp()
    {
        return hp;
    }
    void update()
    {
        hp-=2;
        rectframesmall.w = hp;
    }
   
    bool hit(std::vector<Bullet>& bullets);
};


   
