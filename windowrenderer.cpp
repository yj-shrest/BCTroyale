
#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<cmath>

class renderwindow
{
    private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    public:
    renderwindow(const char* t, int w, int h)
    {
        char* title = const_cast<char*>(t);
        window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
    }
    void cleanup()
    {
        SDL_DestroyWindow(window);
    }

    SDL_Texture* loadTexture(const char* filepath)
    {
        SDL_Texture *temp =NULL;
        char* fp = const_cast<char*> (filepath);
        temp = IMG_LoadTexture(renderer,fp);
        return temp;
    }
    void clear()
    {
        SDL_RenderClear(renderer);
    }
    void render(entity &ent,position camerapos, int direction =1)
    {
        SDL_Rect dst;
        dst.x=ent.getframe().x - camerapos.x;
        dst.y=ent.getframe().y - camerapos.y;
        dst.w= ent.getframe().w;
        dst.h = ent.getframe().h;
        if (direction ==1)
        {
        SDL_RenderCopy(renderer,ent.getTxt(),NULL,&dst);
        }
        else{
            SDL_RenderCopyEx(renderer,ent.getTxt(), NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    void render(std::vector<entity>& entities,position camerapos) {
    SDL_Rect dst;
    for (entity& e : entities) {
        dst.x = e.getframe().x - camerapos.x;
        dst.y = e.getframe().y - camerapos.y;
        dst.w = e.getframe().w;
        dst.h = e.getframe().h;
        SDL_RenderCopy(renderer, e.getTxt(), NULL, &dst);
    }
    }
    void render(Weapon &weapon,Player p,int dir) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect dst;
    dst.x = 560;
    dst.y = 410;
    dst.w = weapon.getframe().w;
    dst.h = weapon.getframe().h;
    double deltaX = mouseX - dst.x;
    double deltaY = mouseY - dst.y;
    double angleRadians = atan2(deltaY, deltaX);
    double angleDegrees = angleRadians * (180.0 / M_PI);
    SDL_Point center = { dst.w / 2, dst.h / 2 };
    if (dir ==-1)
    SDL_RenderCopyEx(renderer, weapon.getTxt(), NULL, &dst, angleDegrees, &center, SDL_FLIP_VERTICAL);
    else
    SDL_RenderCopyEx(renderer, weapon.getTxt(), NULL, &dst, angleDegrees, &center, SDL_FLIP_NONE);
    }

    void rendername(string name)
    {
        TTF_Font* font = TTF_OpenFont("assets/RichuMastRegular.ttf", 40);
        string textInput =name;
        SDL_Color textColor = { 27, 20, 100, 100 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect dst;
        dst.x = 580- textInput.length()*10;
        dst.y = 305;
        dst.w = textInput.length()*20;
        dst.h = 40;

        SDL_RenderCopy(renderer, textTexture, NULL, &dst);
    }

    void inputname(string text)
    {
        TTF_Font* font = TTF_OpenFont("assets/Jost.ttf", 60);
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        string textInput =text;
        SDL_Color textColor = { 27, 20, 100, 150 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect dst;
        dst.x = 575- textInput.length()*20;
        dst.y = 380;
        dst.w = textInput.length()*40;
        dst.h = 60;

        SDL_RenderCopy(renderer, textTexture, NULL, &dst);
    }

    void display()
    {
        SDL_RenderPresent(renderer);
    }
};
