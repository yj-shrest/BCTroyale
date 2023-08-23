#include "SDL.hpp"

SDL::SDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

SDL::~SDL() {
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
SDL_Window* SDL::createWindow(const char* title, int x, int y, int width, int height, Uint32 flags) {
    return SDL_CreateWindow(title, x, y, width, height, flags);
}

SDL_Renderer* SDL::createRenderer(SDL_Window* window, int index, Uint32 flags) {
    return SDL_CreateRenderer(window, index, flags);
}

SDL::Texture* SDL::loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        // Handle error
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL::SoundChunk* SDL::loadSound(const char* filePath) {
    SDL::SoundChunk* sound = Mix_LoadWAV(filePath);
    if (!sound) {
        // Handle error
    }
    return sound;
}

SDL::Music* SDL::loadMusic(const char* filePath) {
    SDL::Music* music = Mix_LoadMUS(filePath);
    if (!music) {
        // Handle error
    }
    return music;
}

bool SDL::pollEvent(SDL_Event& event) {
    return SDL_PollEvent(&event);
}

bool SDL::isMusicPlaying() const {
    return Mix_PlayingMusic() != 0;
}

int SDL::isChannelPlaying(int channel) const {
    return Mix_Playing(channel);
}

int SDL::playSoundChannel(SDL::SoundChunk* chunk, int channel, int loops) {
    return Mix_PlayChannel(channel, chunk, loops);
}

void SDL::playMusic(SDL::Music* music, int loops) {
    Mix_PlayMusic(music, loops);
}

void SDL::haltMusic() {
    Mix_HaltMusic();
}

void SDL::haltSoundChannel(int channel) {
    Mix_HaltChannel(channel);
}

void SDL::delay(unsigned int milliseconds) {
    SDL_Delay(milliseconds);
}

void SDL::getMouseState(int* mouseX, int* mouseY) {
    SDL_GetMouseState(mouseX, mouseY);
}

void SDL::hideCursor() const {
    SDL_ShowCursor(SDL_DISABLE);
}

Uint32 SDL::getTicks() const {
    return SDL_GetTicks();
}

void SDL::showCursor() const {
    SDL_ShowCursor(SDL_ENABLE);
}

int SDL::playSoundChunk(SDL::SoundChunk* &chunk, int channel, int loops) {
    return Mix_PlayChannel(channel, chunk, loops);
}
void SDL::destroyTexture(SDL_Texture* &texture)
{
    SDL_DestroyTexture(texture);
}
void SDL::renderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) {
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void SDL::renderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, double angle, const SDL_Point* center, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, angle, center, flip);
}

void SDL::renderClear(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
}

void SDL::destroyWindow(SDL_Window* window) {
    SDL_DestroyWindow(window);
}

void SDL::renderPresent(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}

SDL_Texture* SDL::loadTexture(SDL_Renderer* renderer, const char* path) {
    return IMG_LoadTexture(renderer, path);
}

TTF_Font* SDL::openFont(const char* file, int size) {
    return TTF_OpenFont(file, size);
}

SDL_Surface* SDL::renderTextSolid(TTF_Font* font, const char* text, SDL_Color color) {
    return TTF_RenderText_Solid(font, text, color);
}

SDL_Texture* SDL::createTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

// Other member function implementations...
