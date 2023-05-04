#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"
#include "Boss.hpp"

using namespace std;

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture (const char* p_filePath);
    SDL_Renderer* renderer;
    void clear();
    void display();
    void cleanUp();
    void render (Entity& p_entity);
    void renderBossSkills (Boss& boss);
private:
    SDL_Window* window;
};
