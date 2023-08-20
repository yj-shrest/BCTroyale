#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include "entity.hpp" // Include the appropriate header for entity class
#include "player.hpp" // Include the appropriate header for Player class
#include "mob.hpp" // Include the appropriate header for mob class
#include "Bullet.hpp" // Include the appropriate header for Bullet class
#include "position.hpp"
class renderwindow {
private:
    SDL sdl;
    SDL_Renderer* renderer;
    SDL_Texture* playertexture;
    SDL_Texture* playerflyingtexture;
    SDL_Texture* playerwtexture;
    SDL_Texture* weapontexture;
    SDL_Texture* weaponfiretexture;
    SDL_Texture* healthBarRectTexture;
    SDL_Texture* healthBarTexture;

public:
    SDL_Window* window;

    renderwindow(const char* t, int w, int h);
    void cleanup();
    SDL_Texture* loadTexture(const char* filepath);
    void clear();
    void render(entity& ent, position camerapos, int direction = 1);
    void renderplayer(Player& p, position camerapos, int direction = 1);
    void render(std::vector<entity>& entities, position camerapos);
    void render(std::vector<mob>& entities, position camerapos);
    void render(std::vector<Bullet>& bull, position cpos);
    void renderlives(Player& p, entity& h);
    void rendername(std::string name);
    void inputname(std::string text);
    void rendertext(std::string text, position p);
    void display();
};
