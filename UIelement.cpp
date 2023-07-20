#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


class UIElement {
protected:
    SDL_Rect rect;  // Position and size of the element
    SDL_Texture* texture;  // Texture for rendering the element

public:
    UIElement(int x, int y, int width, int height, SDL_Texture* texture);
    virtual ~UIElement();

    virtual void render(SDL_Renderer* renderer);
    virtual void update();
    virtual void handleEvent(SDL_Event& event);
};
UIElement::UIElement(int x, int y, int width, int height, SDL_Texture* texture) {
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    this->texture = texture;
}

UIElement::~UIElement() {
    SDL_DestroyTexture(texture);
}

void UIElement::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void UIElement::update() {
    // Update the UI element (e.g., animation, state change)
}

void UIElement::handleEvent(SDL_Event& event) {
    // Handle events related to the UI element (e.g., mouse click)
}
