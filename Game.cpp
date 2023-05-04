#include "Game.hpp"

Game::Game() :
    m_window("Zombie Killer", window_width, window_height),
    m_forSpaceship(spaceship_x, spaceship_y, 200.0f, 20.0f, 100),
    m_player(character_x, character_y, character_height, character_width)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    m_backgroundTexture = IMG_LoadTexture(m_window.renderer, "data/Images/background5.jpg");
    m_basementTexture = IMG_LoadTexture(m_window.renderer, "data/Images/Spaceship.png");
    m_characterFaceTexture = IMG_LoadTexture(m_window.renderer, "data/Images/Character'sFace.jpg");
    m_spaceshipSymbolTexture = IMG_LoadTexture(m_window.renderer, "data/Images/SpaceshipSymbol.jpg");

    m_font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 28);
    m_scoreRect.x = 855;
    m_scoreRect.y = 65;
    m_highScoreRect.x = 855;
    m_highScoreRect.y = 25;
}

Game::~Game()
{
    SDL_DestroyTexture(m_backgroundTexture);
    SDL_DestroyTexture(m_basementTexture);
    SDL_DestroyTexture(m_characterFaceTexture);
    SDL_DestroyTexture(m_spaceshipSymbolTexture);
    SDL_FreeSurface(m_scoreTexture);
    SDL_FreeSurface(m_highScoreTexture);
    TTF_CloseFont(m_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run()
{
    while (m_gameRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_QUIT:
                m_gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (m_player.status == -1 || m_player.status == 4) break;
                if (m_event.button.button == SDL_BUTTON_LEFT) m_player.status = 5;
                else m_player.status = 2;
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeElapsed = currentTime - m_lastUpdateTime;

    if (timeElapsed >= 100) {
        m_lastUpdateTime = currentTime;
    }
    else {
        return;
    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    m_player.updateCharacterPosition(currentKeyStates);
    m_player.update();
    if (!m_player.toTheLeft) {
        m_player.frame[2].x = m_player.x-20;
        m_player.frame[5].x = m_player.x-20;
    }
    else {
        m_player.frame[2].x = m_player.x-45;
        m_player.frame[5].x = m_player.x-45;
    }
    if (currentTime - m_lastTimeDecerease > 5000) {
        m_timeDecreaseGenerating *= 0.9;
        m_lastTimeDecerease = currentTime;
    }
    if (currentTime - m_timeGenerateZombie > std::max(5000 * m_timeDecreaseGenerating, (float)2000) && m_zombies.size() < 1) {
        int r = rand();
        //cout<<r<<endl;
        if (r < 5000) {
            Zombie z;
            z.randomGenerating(m_window.renderer);
            m_zombies.push_back(z);
            m_timeGenerateZombie = currentTime;
        }
    }
    while (m_boss.zombies.size()) {
        Zombie z;
        z.summon(m_window.renderer, m_boss.zombies.front().first, m_boss.zombies.front().second);
        m_zombies.push_back(z);
        m_boss.zombies.pop();
    }
    m_player.attackBoss(m_boss);
    m_boss.listToDo(m_player);
    if (m_boss.flip) {
        m_boss.frame[m_boss.status].x = m_boss.x+200;
    }
    else {
        m_boss.frame[m_boss.status].x = m_boss.x;
    }
}

void Game::render()
{
    SDL_RenderCopy(m_window.renderer, m_backgroundTexture, NULL, NULL); //Render background

    SDL_Rect basementRect = {0, 20, 300, 700}; // Render tau vu tru nguoc
    SDL_RenderCopyEx(m_window.renderer, m_basementTexture, NULL, &basementRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    SDL_Rect characterFace = {35, 15, 40, 40};
    SDL_RenderCopy(m_window.renderer, m_characterFaceTexture, NULL, &characterFace);
    SDL_Rect spaceshipSymbol = {35, 75, 40, 40};
    SDL_RenderCopy(m_window.renderer, m_spaceshipSymbolTexture, NULL, &spaceshipSymbol);

    if (m_boss.status != 7 && m_boss.status != -1) {
        m_window.render(m_boss);
    }
    else if (m_boss.status == 7) {
        m_window.renderBossSkills(m_boss);
    }

    bool renderPlayer = false;
    std::sort(m_zombies.begin(), m_zombies.end(), [&](Zombie x, Zombie y) {
        return x.trueY < y.trueY;
    });
    for (auto &z: m_zombies) {
        if (z.status == -1) continue;
        if (!renderPlayer && z.trueY >= m_player.trueY && m_player.status >= 0) {
            m_window.render(m_player);
            renderPlayer = true;
        }
        m_window.render(z);
        z.update();
    }
    if (!renderPlayer && m_player.status > -1) {
        m_window.render(m_player);
    }

    for (auto &z: m_zombies) {
        z.walk();
    }

    std::string scoreText = "SCORE: " + std::to_string(m_player.score);
    std::string highScoreText = "HIGH SCORE: " + std::to_string(m_player.highScore);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(m_font, scoreText.c_str(), m_textColor);
    SDL_Surface* highScoreSurface = TTF_RenderText_Solid(m_font, highScoreText.c_str(), m_textColor);
    m_scoreTexture = SDL_CreateTextureFromSurface(m_window.renderer, scoreSurface);
    m_highScoreTexture = SDL_CreateTextureFromSurface(m_window.renderer, highScoreSurface);
    SDL_QueryTexture(m_scoreTexture, NULL, NULL, &m_scoreRect.w, &m_scoreRect.h);
    SDL_QueryTexture(m_highScoreTexture, NULL, NULL, &m_highScoreRect.w, &m_highScoreRect.h);
    SDL_RenderCopy(m_window.renderer, m_scoreTexture, NULL, &m_scoreRect);
    SDL_RenderCopy(m_window.renderer, m_highScoreTexture, NULL, &m_highScoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(highScoreSurface);

    m_window.display();
}
