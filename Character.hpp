#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "Entity.hpp"
#include "Zombie.hpp"
#include "BloodBar.hpp"
#include "Boss.hpp"

using namespace std;

class Zombie;
class Boss;

class Character: public Entity {
public:
    float healthBarX = 80, healthBarY = 25, healthBarW = 300, healthBarH = 20;
    Character(float p_x, float p_y, float p_w, float p_h)
        : Entity(p_x, p_y, p_w, p_h), health(80, 25, 300, 20, 100)
    {
    }
    using Entity::Entity;
    bool checkLeftClick = 1;
    double attackDameLeftClick, attackDameRightClick;
    int healthBarMax = 100;
    int score = 0, highScore = 0;
    void creating(SDL_Renderer* renderer);
    void update() override;
    void updateCharacterPosition(const Uint8* currentKeyStates);
    void attackZombie (Zombie &z);
    void attackBoss (Boss &boss);
    void injured (int damage);
    BloodBar health ;
};

