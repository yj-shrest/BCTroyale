#pragma once
#include "position.hpp"

class Camera {
    position pos;
    int screenWidth;
    int screenHeight;
    
public:
    Camera(const int &width,const int &height);

    void update(const position& target);

    const position& getPosition() const;
};
