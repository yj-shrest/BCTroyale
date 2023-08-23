#pragma once

#include "entity.hpp"
#include "mob.hpp"
#include "player.hpp"  // Include Player class header
#include <vector>
#include <cmath>

class Bullet : public entity {
private:
    int frameposx, frameposy;
    int mousex, mousey;
    int increment;
    float theta;
    position initialpos;

public:
    bool remove;
    float range;

    Bullet(int px, int py, int pw, int ph, int mx, int my, position cpos);
    Bullet(int px, int py, int pw, int ph, float th, position cpos);
    Bullet(int px, int py, int pw, int ph, position cpos);

    void update();
    position getmouse();
    float gettheta();
    static float gettheta(int mouseX, int mouseY);
    bool hit(std::vector<entity>& platforms);
    bool hit(std::vector<mob>& mobs);
    bool hit(Player e);
    bool isinrange();
};
