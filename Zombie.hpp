#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "Entity.hpp"
#include "Character.hpp"
#include "BloodBar.hpp"

using namespace std;

class Character;

class Zombie: public Entity {
public:
    int health;
    bool newAttack = 0;
    Zombie();
    void information (SDL_Renderer* renderer);
    void randomGenerating (SDL_Renderer* renderer);
    void summon (SDL_Renderer* renderer, float summonX, float summonY);
    void update() override;
    void walk();
    void takeDamage (double damage);
    void behavior (BloodBar &spaceShip);
    void attack (Character &player, BloodBar &spaceShip);
};
