#pragma once
#include "SDL.hpp"  // Include the SDL wrapper class
class Player;
class entity {
private:
    SDL::Texture* texture;
    const float moveSpeed = 5.0f;
    SDL::Rect currentframe;

public:
    bool isFlying = false;
    bool isMovingSideways = false;
    int movementDirection = 0;
    
    // Constructors
    entity();
    entity(float px, float py, float pw, float ph);
    entity(float px, float py, float pw, float ph, SDL::Texture* t);

    // Methods for entity class
    void setval(float px, float py);
    SDL::Rect& getframe();
    int getspeed();
    SDL::Texture* getTxt();
    void updateHealth(Player &p);
    void updatenitro(Player &p);
};
