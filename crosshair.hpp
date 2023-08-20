#pragma once
#include "entity.hpp" // Include the appropriate header file

class Crosshair : public entity {
public:
    Crosshair(int px, int py, int pw, int ph, SDL::Texture* t);
    void update(int x, int y);
};
