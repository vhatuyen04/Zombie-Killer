#pragma once

#include <SDL.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer, int screen_width, int screen_height);
    ~Menu();
    void handle_events();
    void update();
    void render();

private:
    SDL_Renderer* renderer_;
    SDL_Texture* start;
    SDL_Texture* settings;
    SDL_Texture* quit;
    int screen_width_;
    int screen_height_;
    bool quit_;
    int selected_option_;
};
