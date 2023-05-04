#include <iostream>
#include "BloodBar.hpp"
using namespace std;

BloodBar::BloodBar (float posX, float posY, float width, float height, int health) {
    x = posX;
    y = posY;
    w = width;
    h = height;
    maxHealth = health;
    currentHealth = maxHealth;
}

void BloodBar::render (SDL_Renderer* renderer) {
    SDL_Rect outline = {x, y, w, h};
    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &outline);

    SDL_Rect fill = {x + 1, y + 1, (int)(w * (currentHealth / (float)maxHealth)) - 2, h - 2};
    if (isCharacter) SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);
    else SDL_SetRenderDrawColor (renderer, 0, 0, 255, 255);
    if (currentHealth > 0) SDL_RenderFillRect(renderer, &fill);
  }

void BloodBar::update (int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
}
