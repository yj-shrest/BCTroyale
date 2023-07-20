#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>
class Camera {
    position pos;
    int screenWidth;
    int screenHeight;
    
public:
    Camera(int width, int height) : screenWidth(width), screenHeight(height) {}

    void update(const position& target) {
        
        pos.x = target.x - screenWidth / 2;
        pos.y = target.y - screenHeight / 2;
    }

    const position& getPosition() const {
        return pos;
    }
};