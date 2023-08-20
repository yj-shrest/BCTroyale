#include "camera.hpp"

Camera::Camera(int width, int height) : screenWidth(width), screenHeight(height) {}

void Camera::update(const position& target) {
    pos.x = target.x - screenWidth / 2;
    pos.y = target.y - screenHeight / 2;
}

const position& Camera::getPosition() const {
    return pos;
}
