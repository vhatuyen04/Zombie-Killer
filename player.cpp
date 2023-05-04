#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;

const int character_height = 32*3, character_width = 32*4;

Entity player(0, 180, character_height, character_width);
const int window_height = 1200, window_width = 600;
RenderWindow window ("Zombie Shooter", window_height, window_width);

void valueCharacter (RenderWindow w) {
    player.status = 0;
    player.addAnimation(window.renderer, "data/Images/NightBorne1.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne2.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne3.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne4.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne5.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne6.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne7.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne8.png", 0);
    player.addAnimation(window.renderer, "data/Images/NightBorne9.png", 0);
    player.state[0] = 0;
}

