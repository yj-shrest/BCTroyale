#pragma once
#include "mob.hpp"
#include "entity.hpp"
#include <vector>
class Bullet;
class mob : public entity {
private:
    int hp;
    SDL::Texture* hptexture;
    SDL::Texture* hprecttexture;
    SDL::Rect rectframebig;
    SDL::Rect rectframesmall;

public:
    mob(float px, float py, float pw, float ph, SDL::Texture* mobtext, SDL::Texture* hptxt, SDL::Texture* recttext);

    SDL::Rect& getsmallrect();
    SDL::Rect& getbigrect();
    SDL::Texture* getrecttxt();
    SDL::Texture* gethptxt();
    int gethp();
    void update();
    bool hit(std::vector<Bullet>& bullets);
};
