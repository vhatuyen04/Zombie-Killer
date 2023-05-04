#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>

class BloodBar {
public:
    float x, y, w, h;
    bool isCharacter = 0;
    int currentHealth, maxHealth;
    BloodBar (float posX, float posY, float width, float height, int health);
    void render (SDL_Renderer* renderer);
    void update (int damage);
};
