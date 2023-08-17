#pragma once

//#include "Player.cpp"
class Player;
class position
{
    public:
    float x, y;
    position():x(0),y(0){}
    position(float px, float py)
    {
        x = px; y = py;
    }
};