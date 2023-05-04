/*#include "Menu.hpp"

Menu::Menu(SDL_Renderer* renderer, int screen_width, int screen_height)
    : renderer_(renderer), screen_width_(screen_width), screen_height_(screen_height),
      quit_(false), selected_option_(0)
{
    // Load textures for menu options
    start = IMG_LoadTexture(renderer_, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Play col_Button.png");
    settings = IMG_LoadTexture(renderer_, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Settings col_Button.png");
    quit = IMG_LoadTexture(renderer_, "data/Images/Menu Buttons/Large Buttons/Colored Large Buttons/Quit col_Button.png");
}

Menu::~Menu()
{
    // Clean up SDL textures
    SDL_DestroyTexture(start_game_texture_);
    SDL_DestroyTexture(settings_texture_);
    SDL_DestroyTexture(quit_texture_);
}

void Menu::handle_events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit_ = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        selected_option_--;
                        if (selected_option_ < 0)
                        {
                            selected_option_ = 2;
                        }
                        break;
                    case SDLK_DOWN:
                        selected_option_++;
                        if (selected_option_ > 2)
                        {
                            selected_option_ = 0;
                        }
                        break;
                    case SDLK_RETURN:
                        switch (selected_option_)
                        {
                            case 0:
                                // Start game
                                break;
                            case 1:
                                // Settings
                                break;
                            case 2:
                                // Quit
                                quit_ = true;
                                break;
                        }
                        break;
                }
                break;
        }
    }
}*/

