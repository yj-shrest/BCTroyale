#pragma once
#include "position.hpp"

class Camera {
    position pos;
    int screenWidth;
    int screenHeight;
    
public:
    Camera(int width, int height);

    void update(const position& target);

    const position& getPosition() const;
};
