#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <iostream>

#include "Zombie.hpp"

using namespace std;

Zombie::Zombie() : Entity(x, y, w, h) {

}

void Zombie::information (SDL_Renderer* renderer) {
    int r = rand();
    toTheLeft = 1;
    status = 5;
    w = 32*4;
    h = 32*3;
    attackZone = 5;
    attackDame = 10;
    setSizeOfFrame();
    switch (type) {
    case 0:
        speed = 10;
        health = 50;
        //attackZone = 15;
        for (int i = 1; i <= 11; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie1/appear/appear_"<< i << ".png";
            addAnimation(renderer, ss.str().c_str(), 5);
        }

        for (int i = 1; i <= 6; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie1/idle/idle_"<< i << ".png";
            addAnimation(renderer, ss.str().c_str(), 0);
        }

        for (int i = 1; i <= 10; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie1/walk/go_"<< i << ".png";
            addAnimation(renderer, ss.str().c_str(), 1);
        }

        for (int i = 1; i <= 8; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie1/die/die_"<< i << ".png";
            addAnimation(renderer, ss.str().c_str(), 4);
        }

        for (int i = 1; i <= 7; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie1/attack/hit_"<< i << ".png";
            addAnimation(renderer, ss.str().c_str(), 2);
        }

        frame[2].x -= 25;
        //z.sz[2].y -= 35;
        frame[2].w *= 1.6;
        frame[2].h *= 1;
        break;
    case 1:
        flip = 1;
        speed = 5;
        health = 100;
        //attackZone = 10;
        for (int i = 1; i <= 7; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Jump"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 5);
        }

        for (int i = 1; i <= 4; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Idle"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 0);
        }

        for (int i = 1; i <= 6; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Walk"<< i << ".png";
            addAnimation (renderer, ss.str().c_str(), 1);
        }

        for (int i = 1; i <= 6; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Attack"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 2);
        }

        for (int i = 1; i <= 4; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Hurt"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 3);
        }

        for (int i = 1; i <= 8; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Dead"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 4);
        }

        for (int i = 4; i <= 10; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie2/PNG/Animation/Run"<< i <<".png";
            addAnimation (renderer, ss.str().c_str(), 6);
        }
        frame[1].delay = 100;
        frame[2].w *= 0.8;
        frame[6].w *= 1.1;
        frame[4].w *= 0.8;
        break;
    case 2:
        flip = 1;
        speed = 3;
        health = 100;
        //attackZone = 15;
        for (int i = 1; i <= 7; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Jump"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 5);
        }

        for (int i = 1; i <= 4; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Idle"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 0);
        }

        for (int i = 1; i <= 4; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Walk"<< i << ".png";
            addAnimation (renderer, ss.str().c_str(), 1);
        }

        for (int i = 1; i <= 6; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Attack"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 2);
        }

        for (int i = 1; i <= 5; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Hurt"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 3);
        }

        for (int i = 1; i <= 8; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Dead"<<i<<".png";
            addAnimation(renderer, ss.str().c_str(), 4);
        }

        for (int i = 4; i <= 10; i++) {
            stringstream ss;
            ss << "data/Images/Zombie/Zombie3/Animation/Run"<< i <<".png";
            addAnimation (renderer, ss.str().c_str(), 6);
        }
        frame[1].delay = 100;
        frame[2].w *= 0.8;
        frame[6].w *= 1.1;
        frame[4].w *= 0.8;
        break;
    }
}

void Zombie::summon (SDL_Renderer* renderer, float summonX, float summonY) {
    type = rand()%3;
    x = summonX;
    y = summonY;
    trueY = y;
    trueX = x;
    information (renderer);
}

void Zombie::randomGenerating (SDL_Renderer* renderer) {
    type = rand()%3;
    int r = rand();
    x = 1000;
    y = r%400+85;
    trueY = y;
    trueX = x;
    information (renderer);
}

void Zombie::update() {
    bool change(0);
    Uint32 current = SDL_GetTicks();
    if (current-frame[status].last_update_time >= frame[status].delay) {
        frame[status].current = (frame[status].current+1) % frame[status].texture.size();
        frame[status].last_update_time = current;
        change = 1;
    }
     //cout<<status<<' '<<state[status]<<' '<<texture[status].size()<<endl;
    if (!change) return;
    if (attackZone && frame[2].current == 0) {
        Uint32 current = SDL_GetTicks();
        if (current-lastAttack < attackSpeed) {
            readyToAttack = 0;
        }
        else {
            readyToAttack = 1;
        }
    }
    switch (status) {
    case 3:
        if (frame[3].current == 0) {
            status = 6;
            speed = speed*3;
        }
        break;
    case 4:
        if (frame[4].current == 0) {
            status = -1;
        }
        break;
    case 5:
        if (frame[5].current == 0) status = 0;
        break;
    case 0:
        if (frame[0].current == 0) {
            if (!attackZone) status = 1;
            else status = 2;
        }
        break;
    default:
        break;
    }
}

void Zombie::walk() {
    if (status == 1 || status == 6) {
        if (x >= 270+speed) {
            updateX(-speed);
        }
        else status = 2;
    }
}

void Zombie::takeDamage (double damage) {
    health -= damage;
    if (health <= 0) status = 4;
    else status = 3;
}

void Zombie::behavior (BloodBar &spaceShip) {
    if (status == 3 || status == -1 || status == 4) return;
    if (x < 270+speed) {
        status = 2;
        if (frame[2].current == 2) spaceShip.update (attackDame);
    }
    else if (status == 2) status = 1;
}

void Zombie::attack (Character &player, BloodBar &spaceShip) {
    if (!contact(player)) {
        behavior (spaceShip);
        return;
    }
    status = 2;
    if (frame[2].current == 2) player.injured (attackDame);
}
