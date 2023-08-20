#include "crosshair.hpp"

Crosshair::Crosshair(int px, int py, int pw, int ph, SDL::Texture* t)
    : entity(px, py, pw, ph, t) {}

void Crosshair::update(int x, int y) {
    getframe().x = x;
    getframe().y = y;
}
