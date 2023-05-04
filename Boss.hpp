#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <queue>

#include "Entity.hpp"
#include "Character.hpp"

using namespace std;

class Character;

class Boss : public Entity {
public:
    Boss();
    bool exist = 0;
    int health, minX = 270, minY = 45, maxX = 800, maxY = 300;
    Uint32 lastIdle = 0, lastWalk, lastCast;
    float speedX, speedY, targetX, targetY;
    struct hole {
        float x, y, w, h;
        int current = 0;
    };
    hole holeZombies[4];
    vector <hole> explosion;
    queue <pair <float, float> > zombies;
    bool spotToGo = 0, appear;
    float distance (float x1, float y1);
    void creating (SDL_Renderer* renderer);
    void walk ();
    void chasingCharacter (Character &player);
    void behavior (Character &player);
    void update (Character &player);
    void summonZombies ();
    void createExplosion ();
    void listToDo (Character &player);
    void injured (int damage);
};
