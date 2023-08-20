#pragma once
#include "entity.hpp"  
#include "position.hpp"
#include "Bullet.hpp"
#include<iostream>
#include <vector>
#include<random>
using namespace std;
class Player : public entity {
private:
    // Data members specific to Player class
    const int maxhealth=100; 
    float health;
    float nitro;
    int mouseX, mouseY;
    int weaponwidth, weaponheight;
    int lives;
    int id;
    float takingdamage= false;
    string name;

public:
    float theta;
    bool died;
    int dir;
    bool firing;
    bool flying;
    bool respawning;
    Uint32 lastAnimationUpdateTime = 0;

    Player(string n, int i);
    Player();

    // Methods for Player class
    void setvalues();
    void setvalues(int x, int y);
    string getname();
    int getid();
    int getrandomx();
    position getpos();
    position getweaponsize();
    int getlives();
    void refill();
    void movedown();
    void moveSideways(int direction);
    void stopMovingSideways();
    void jump();
    int gethealth();
    float getnitro();
    void stopFlying();
    bool hit(Bullet &b);
    void damage();
    void nodamage();
    bool isOnGround(std::vector<entity> &entities);
    std::string sidecollision(std::vector<entity> &entities);
    bool upcollide(std::vector<entity> &entities);
    void updatePosition(int x, int y, int d, float t, bool fi, bool fly, bool res, bool dead);
    void update(std::vector<entity> &entities);
};
