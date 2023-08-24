#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class SDL {
public:
    using Texture = SDL_Texture;
    using SoundChunk = Mix_Chunk;
    using Music = Mix_Music;
    using Event = SDL_Event;
    using Rect = SDL_Rect;
    using Window = SDL_Window;
    using Font = TTF_Font;
    using Color = SDL_Color;
    using Surface = SDL_Surface;
    using Renderer = SDL_Renderer;
    using Point = SDL_Point;

    static constexpr int QUIT = SDL_QUIT;
    static constexpr int KEY_UP = SDL_KEYUP;
    static constexpr int KEY_DOWN = SDL_KEYDOWN;
    static constexpr int TEXT_INPUT = SDL_TEXTINPUT;  
    static constexpr int MOUSE_BUTTON_DOWN = SDL_MOUSEBUTTONDOWN;  
    static constexpr int MOUSE_BUTTON_UP = SDL_MOUSEBUTTONUP; 
    static constexpr int MOUSE_MOTION = SDL_MOUSEMOTION;
    // Define more custom events as needed

    // Custom constants for frequently used key values
    static constexpr int UP = SDLK_UP;
    static constexpr int DOWN = SDLK_DOWN;
    static constexpr int LEFT = SDLK_LEFT;
    static constexpr int RIGHT = SDLK_RIGHT;
    static constexpr int BACKSPACE = SDLK_BACKSPACE;
    static constexpr int a = SDLK_a;
    static constexpr int d = SDLK_d;
    static constexpr int w = SDLK_w;
    static constexpr int BUTTON_LEFT = SDL_BUTTON_LEFT;
    static constexpr int BUTTON_RIGHT = SDL_BUTTON_RIGHT;
    static constexpr int ENTER = SDLK_RETURN;

    static const int WindowPosUndefined = SDL_WINDOWPOS_UNDEFINED;
    static const int WindowAllowHighDPI = SDL_WINDOW_ALLOW_HIGHDPI;
    static const int RendererAccelerated = SDL_RENDERER_ACCELERATED;
    static const int RendererPresentVSync = SDL_RENDERER_PRESENTVSYNC;
    static const SDL_RendererFlip FlipHorizontal = SDL_FLIP_HORIZONTAL;
    static const SDL_RendererFlip FlipVertical = SDL_FLIP_VERTICAL;
    static const SDL_RendererFlip NoFlip = static_cast<SDL_RendererFlip>(0);


    SDL();
    ~SDL();

    SDL_Window* createWindow(const char* title, int x, int y, int width, int height, Uint32 flags);
    SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags);
    Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
    SoundChunk* loadSound(const char* filePath);
    Music* loadMusic(const char* filePath);
    bool pollEvent(Event& event);
    bool isMusicPlaying() const;
    int isChannelPlaying(int channel) const;
    int playSoundChannel(Mix_Chunk* chunk, int channel, int loops);
    void playMusic(Mix_Music* music, int loops);
    void haltMusic();
    void haltSoundChannel(int channel);
    void delay(unsigned int milliseconds);
    void getMouseState(int* mouseX, int* mouseY);
    void hideCursor() const;
    Uint32 getTicks() const;
    void showCursor() const;
    int playSoundChunk(Mix_Chunk* &chunk, int channel, int loops);
    void renderCopy(Renderer* renderer, Texture* texture, const Rect* srcRect, const Rect* dstRect);
    void renderCopyEx(Renderer* renderer, Texture* texture, const Rect* srcRect, const Rect* dstRect, double angle, const Point* center, SDL_RendererFlip flip);
    void renderClear(Renderer* renderer);
    void destroyWindow(Window* window);
    void renderPresent(Renderer* renderer);
    void destroyTexture(SDL_Texture* &texture);
    Texture* loadTexture(Renderer* renderer, const char* path);
    Font* openFont(const char* file, int size);
    Surface* renderTextSolid(Font* font, const char* text, Color color);
    Texture* createTextureFromSurface(Renderer* renderer, Surface* surface);
};
