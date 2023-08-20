#include "mob.hpp"
    mob::mob (float px, float py,float pw, float ph, SDL::Texture* mobtext,SDL::Texture* hptxt,SDL::Texture* recttext ):entity(px,py,pw,ph,mobtext)
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
    SDL::Rect& mob::getsmallrect()
    {
        return rectframesmall;
    }
    SDL::Rect& mob::getbigrect()
    {
        return rectframebig;
    }
    SDL::Texture* mob::getrecttxt()
    {
        return hprecttexture;
    }
    SDL::Texture* mob::gethptxt()
    {
        return hptexture;
    }
    int mob::gethp()
    {
        return hp;
    }
    void mob::update()
    {
        hp-=2;
        rectframesmall.w = hp;
    }
   
    

   
