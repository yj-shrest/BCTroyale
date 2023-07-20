#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FONT_SIZE = 24;
const int TEXTBOX_WIDTH = 400;
const int TEXTBOX_HEIGHT = 50;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Text Input Box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/RichuMastRegular.ttf", FONT_SIZE);

    std::string textInput = "";
    bool typing = true;
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (typing) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        typing = false; // Finish typing on pressing Enter
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE && textInput.length() > 0) {
                        textInput.pop_back(); // Delete the last character on pressing Backspace
                    }
                }
                
            }
            else if (event.type == SDL_TEXTINPUT && typing) {
                textInput += event.text.text; // Append the entered character to the text input
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render the text input box
        SDL_Color textColor = { 0, 0, 0, 255 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, textInput.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        SDL_Rect textBoxRect = { (WINDOW_WIDTH - TEXTBOX_WIDTH) / 2, (WINDOW_HEIGHT - TEXTBOX_HEIGHT) / 2, TEXTBOX_WIDTH, TEXTBOX_HEIGHT };
        SDL_RenderDrawRect(renderer, &textBoxRect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textBoxRect);
        SDL_DestroyTexture(textTexture);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
