#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "RenderWindow.hpp"
#include "Zombie.hpp"
#include "Character.hpp"
#include "Entity.hpp"
#include "Boss.hpp"
#include "BloodBar.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void handleEvents();
    void update();
    void render();

    RenderWindow m_window;

    Character m_player;
    BloodBar m_forSpaceship;
    float m_timeDecreaseGenerating = 1, m_lastTimeDecerease = 0;
    Boss m_boss;
    std::vector<Zombie> m_zombies;

    SDL_Texture* m_backgroundTexture;
    SDL_Texture* m_basementTexture;
    SDL_Texture* m_characterFaceTexture;
    SDL_Texture* m_spaceshipSymbolTexture;

    TTF_Font* m_font;
    SDL_Color m_textColor = {191, 64, 191, 255};
    SDL_Texture* m_scoreTexture = nullptr;
    SDL_Texture* m_highScoreTexture = nullptr;
    SDL_Rect m_scoreRect;
    SDL_Rect m_highScoreRect;

    Uint32 m_lastUpdateTime = 0;
    Uint32 m_timeGenerateZombie = 0;

    bool m_gameRunning = true;
    SDL_Event m_event;
};

#endif // GAME_HPP
