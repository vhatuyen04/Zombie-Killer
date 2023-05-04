#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <queue>
#include <algorithm>
#include <SDL_ttf.h>
#include <cmath>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Character.hpp"
#include "Zombie.hpp"
#include "BloodBar.hpp"
#include "Boss.hpp"

using namespace std;

RenderWindow window ("Zombie Killer", window_width, window_height);
Character player (character_x, character_y, character_height, character_width);
BloodBar forSpaceship (80, 85, 300, 20, 1000);
float timeDecreaseGenerating = 1, lastTimeDecerease = 0;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // handle initialization error
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout<<"IMG_init has failed. Error: "<<SDL_GetError()<<endl;
    }
    // Create a window
    //SDL_SetRenderDrawBlendMode(window.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(window.renderer);

    Boss boss;
    vector <Zombie> zombies;

    SDL_Surface* surface = IMG_Load("data/Images/background5.jpg");
    SDL_Surface* loseSurface = IMG_Load ("data/Images/Game Over!.png");
    if (surface == NULL) return 0;
    if (loseSurface == NULL) return 0;
    SDL_Texture* gameOver = SDL_CreateTextureFromSurface(window.renderer, loseSurface);
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(window.renderer, surface);
    SDL_Texture* basementTexture = IMG_LoadTexture(window.renderer, "data/Images/Spaceship.png");
    SDL_Texture* characterFaceTexture = IMG_LoadTexture (window.renderer, "data/Images/Character'sFace.jpg");
    SDL_Texture* spaceshipSymbolTexture = IMG_LoadTexture (window.renderer, "data/Images/SpaceshipSymbol.jpg");
    SDL_FreeSurface(surface);

    Uint32 last_update_time_  = 0, time_generate_zombie = 0;

    srand(time(NULL));

    if (TTF_Init() < 0) {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }
    TTF_Font* font = NULL;
    SDL_Color textColor = {191, 64, 191, 255};
    SDL_Texture* scoreTexture = NULL;
    SDL_Texture* highScoreTexture = NULL;
    SDL_Rect scoreRect;
    SDL_Rect highScoreRect;
    font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 28);
    scoreRect.x = 855;
    scoreRect.y = 65;
    highScoreRect.x = 855;
    highScoreRect.y = 25;

    SDL_Event e;

    bool Quit_Menu = false;
	bool gameRunning = false;
	//While application is running
    SDL_Texture* menuTexture = IMG_LoadTexture(window.renderer, "data/Images/1.png");

    SDL_Texture* start = IMG_LoadTexture(window.renderer, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Play col_Button.png");
    SDL_Texture* startChosen = IMG_LoadTexture(window.renderer, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Play col_Button - Copy.png");
    SDL_Texture* settings = IMG_LoadTexture(window.renderer, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Settings col_Button.png");
    SDL_Texture* quit = IMG_LoadTexture(window.renderer, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Quit col_Button.png");
    SDL_Texture* quitChosen = IMG_LoadTexture(window.renderer, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Quit col_Button - Copy.png");

    SDL_Rect dstStart = {500, 200, 200, 80};
    SDL_Rect dstQuit = {500, 400, 200, 80};
    int selected_option = 0;
    bool chooseStart = 1, chooseQuit = 0;
	while (!Quit_Menu)
	{
		SDL_Event event;
		//Handle events on queue
		while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    Quit_Menu = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            selected_option--;
                            if (selected_option < 0)
                            {
                                selected_option = 1;
                            }
                            break;
                        case SDLK_DOWN:
                            selected_option++;
                            if (selected_option > 1)
                            {
                                selected_option = 0;
                            }
                            break;
                        case SDLK_RETURN:
                                Quit_Menu = true;
                            switch (selected_option)
                            {
                                case 0:
                                    // Start game
                                    gameRunning = 1;
                                    break;
                                case 1:
                                    // Quit
                                    break;
                            }
                            break;
                    }
                    break;
            }
        }
		SDL_RenderCopy (window.renderer, menuTexture, NULL, NULL);
        if (selected_option) {
            SDL_RenderCopy (window.renderer, start, NULL, &dstStart);
            SDL_RenderCopy (window.renderer, quitChosen, NULL, &dstQuit);
        }
        else {
            SDL_RenderCopy (window.renderer, startChosen, NULL, &dstStart);
            SDL_RenderCopy (window.renderer, quit, NULL, &dstQuit);
        }
		/*SDL_Rect* playButton = &gPlayButton[0];
		PlayButton.Render(playButton, gRenderer, gPlayButtonTexture);
		SDL_Rect* TTButton = &gTutorialsButton[0];
		TutorialsButton.Render(TTButton, gRenderer, gTutorialsTexture);
		SDL_Rect* EXButton = &gExitButton[0];
		ExitButton.Render(EXButton, gRenderer, gExitButtonTexture);
		if (PlayButton.currentSprite == BUTTON_SELECTED) {
			SDL_Rect* currentClip_Play = &gPlayButton[1];
			PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);
		}
		else if (TutorialsButton.currentSprite == BUTTON_SELECTED_2) {
			SDL_Rect* currentClip_TT = &gTutorialsButton[1];
			TutorialsButton.Render(currentClip_TT, gRenderer, gTutorialsTexture);
		}
		else if (ExitButton.currentSprite == BUTTON_SELECTED_3) {
			SDL_Rect* EXButton = &gExitButton[1];
			ExitButton.Render(EXButton, gRenderer, gExitButtonTexture);
		}*/

		// Update screen
		SDL_RenderPresent(window.renderer);
	}
    if (selected_option == 1) {
        SDL_Quit();
        return 0;
    }
    player.creating (window.renderer);
    boss.creating (window.renderer);
    while (gameRunning) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 time_elapsed = current_time - last_update_time_;

        if (time_elapsed >= 100) {
            last_update_time_ = current_time;
        }
        else
            continue;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    gameRunning = false;
                    SDL_Quit();
                    return 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (player.status == -1 || player.status == 4) {
                        break;
                    }
                    if (e.button.button == SDL_BUTTON_LEFT) player.status = 5;
                    else player.status = 2;
                    break;
                default:
                    break;
            }

        }

        SDL_RenderCopy (window.renderer, backgroundTexture, NULL, NULL); //Render background

        SDL_Rect basementRect = {0, 20, 300, 700}; // Render tau vu tru nguoc
        SDL_RenderCopyEx (window.renderer, basementTexture, NULL, &basementRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_Rect characterFace = {35, 15, 40, 40};
        SDL_RenderCopy (window.renderer, characterFaceTexture, NULL, &characterFace);
        SDL_Rect spaceshipSymbol = {35, 75, 40, 40};
        SDL_RenderCopy (window.renderer, spaceshipSymbolTexture, NULL, &spaceshipSymbol);

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        player.updateCharacterPosition(currentKeyStates);
        player.update();
        if (!player.toTheLeft) {
            player.frame[2].x = player.x-20;
            player.frame[5].x = player.x-20;
        }
        else {
            player.frame[2].x = player.x-45;
            player.frame[5].x = player.x-45;
        }
        if (current_time - lastTimeDecerease > 5000) {
            timeDecreaseGenerating *= 0.9;
            lastTimeDecerease = current_time;
        }
        if (current_time - time_generate_zombie > max(5000*timeDecreaseGenerating, (float)2000) && zombies.size() < 30) {
            int r = rand();
            //cout<<r<<endl;
            if (r < 5000) {
                Zombie z;
                z.randomGenerating(window.renderer);
                zombies.push_back(z);
                time_generate_zombie = current_time;
            }
        }
        if (zombies.size() == 30) {
            boss.exist = 1;
            while (boss.zombies.size()) {
                Zombie z;
                z.summon (window.renderer, boss.zombies.front().first, boss.zombies.front().second);
                zombies.push_back(z);
                boss.zombies.pop();
            }
            player.attackBoss (boss);
            boss.listToDo (player);
            if (boss.flip) {
                boss.frame[boss.status].x = boss.x+200;
            }
            else boss.frame[boss.status].x = boss.x;
        }

        for (auto &z: zombies) {
            player.attackZombie (z);
            z.attack (player, forSpaceship);
        }
        player.checkLeftClick = 0;

        bool renderPlayer = 0;
        sort (zombies.begin(), zombies.end(), [&](Zombie x, Zombie y) {
            return x.trueY < y.trueY;
        });
        for (auto &z: zombies) {
            if (z.status == -1) continue;
            if (!renderPlayer && z.trueY >= player.trueY && player.status >= 0) {
                window.render (player);
                renderPlayer = 1;
            }
            window.render (z);
            z.update();
        }
        if (!renderPlayer && player.status > -1) window.render(player);

        if (boss.exist) {
            if (boss.status != 7 && boss.status != -1) window.render(boss);
            else if (boss.status == 7) window.renderBossSkills (boss);
        }

        for (auto &z: zombies) {
            z.walk();
        }

        string scoreText = "SCORE: " + to_string (player.score);
        string highScoreText = "HIGH SCORE: " + to_string (player.highScore);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid (font, scoreText.c_str(), textColor);
        SDL_Surface* highScoreSurface = TTF_RenderText_Solid (font, highScoreText.c_str(), textColor);
        scoreTexture = SDL_CreateTextureFromSurface(window.renderer, scoreSurface);
        highScoreTexture = SDL_CreateTextureFromSurface(window.renderer, highScoreSurface);
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
        SDL_QueryTexture(highScoreTexture, NULL, NULL, &highScoreRect.w, &highScoreRect.h);
        // Render the score and high score text on the screen
        SDL_RenderCopy(window.renderer, scoreTexture, NULL, &scoreRect);
        //SDL_RenderCopy(window.renderer, highScoreTexture, NULL, &highScoreRect);

        // Free the SDL_Surface objects, SDL_Texture objects, and TTF_Font object
        SDL_FreeSurface(scoreSurface);
        SDL_FreeSurface(highScoreSurface);
        SDL_DestroyTexture(scoreTexture);
        SDL_DestroyTexture(highScoreTexture);

        forSpaceship.render (window.renderer);
        player.health.render (window.renderer);

        if (player.status == -1) gameRunning = false;
        if (boss.status == -1) gameRunning = false;
        if (!forSpaceship.currentHealth) gameRunning = false;
        if (!gameRunning) {
            SDL_Delay(100);
        }
        //SDL_Texture* gameOver = IMG_LoadTexture (window.renderer, "data/Images/GameOver!.png");
        if (gameRunning) window.display();
    }
    bool winner = 1, quitProgram = 0;
    if (player.status == -1 || !forSpaceship.currentHealth) {
        winner = 0;
    }
    SDL_Texture* gameWin = IMG_LoadTexture (window.renderer, "data/Images/Game Win!.png");
    //if (!winner) SDL_RenderCopy (window.renderer, gameOver, NULL, NULL);
    window.clear();
    while (!quitProgram) {
        SDL_Event event;
		//Handle events on queue
		while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    quitProgram = 1;
                    break;
                case SDL_KEYDOWN:

                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            quitProgram = 1;
                        break;
                    }
                    break;
            }
		}
        if (!winner) SDL_RenderCopy (window.renderer, gameOver, NULL, NULL);
        else SDL_RenderCopy (window.renderer, gameWin, NULL, NULL);
        window.display();
    }

        //SDL_Delay(animationDelay);
        /*for (Entity& z: zombie) {
            window.render(z);

        }*/
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    window.cleanUp();
    SDL_Quit();
    return 0;
}

