#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Boss.hpp"

RenderWindow::RenderWindow (const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout<<"Window failed to init. Error: "<<SDL_GetError()<<endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture (const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture (renderer, p_filePath);
    if (texture == NULL) {
        cout<<"Failed to load texture. Error: "<<SDL_GetError()<<endl;
    }
    return texture;
}

void RenderWindow::cleanUp () {
    SDL_DestroyWindow (window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

/*void RenderWindow::render (SDL_Texture* p_tex) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 40*2;
    src.h = 40*2;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 180;
    dst.w = 32*3;
    dst.h = 32*4;

    SDL_RenderCopy (renderer, p_tex, &src, &dst);
}*/

void RenderWindow::render (Entity& p_entity) {
    int status = p_entity.status;
    int current = p_entity.frame[status].current;
    SDL_Texture* texture = p_entity.frame[status].texture[current];
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (p_entity.flip) flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect dst;
    //if (!p_entity.isBoss) {
        dst.x = p_entity.frame[status].x;
        dst.y = p_entity.frame[status].y;
        dst.w = p_entity.frame[status].w;
        dst.h = p_entity.frame[status].h;
        SDL_RenderCopyEx (renderer, texture, NULL, &dst, 0, NULL, flip);
    //}
    /*else {
        float x = p_entity.x;
        float y = p_entity.y;
        float w = p_entity.w;
        float h = p_entity.h;
        if (1) {
            if (status == 0 || status == 1 || status == 3 || status == 4) {
                SDL_Rect srcRect = {w/2, h/3, w/2, h*2/3};
                SDL_Rect destRect = {x+w/2, y+h/3, w/2, h*2/3};
                cout<<srcRect.x<<' '<<srcRect.y<<' '<<srcRect.w<<' '<<srcRect.h<<endl;
                cout<<destRect.x<<' '<<destRect.y<<' '<<destRect.w<<' '<<destRect.h<<endl;
                SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
            }
            if (status == 2) {
                if (0 <= current && current <= 1 || current == 9) {
                    SDL_Rect srcRect = {w/2, h/3, w/2, h*2/3};
                    SDL_Rect destRect = {x+w/2, y+h/3, w/2, h*2/3};
                    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
                }
                if (2 <= current && current <= 3) {
                    SDL_Rect srcRect = {w/2, h/5, w/2, h*4/5};
                    SDL_Rect destRect = {x+w/2, y+h/5, w/2, h*4/5};
                    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
                }
                if (4 <= current && current <= 8) {
                    dst.x = p_entity.x;
                    dst.y = p_entity.y;
                    dst.w = p_entity.w;
                    dst.h = p_entity.h;
                    SDL_RenderCopyEx (renderer, texture, NULL, &dst, 0, NULL, flip);
                }
            }
            if (status == 7) {
                SDL_Rect srcRect = {w/3, h/3, w/3, h*2/3};
                SDL_Rect destRect = {x+w/2, y+h/3, w/2, h*2/3};
                SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
            }
            if (status == 8) {
                if (0 <= current && current <= 4) {
                    SDL_Rect srcRect = {w/2, h/3, w/2, h*2/3};
                    SDL_Rect destRect = {x+w/2, y+h/3, w/2, h*2/3};
                    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
                }
                else {
                    SDL_Rect srcRect = {w/2, 0, w/2, h};
                    SDL_Rect destRect = {x+w/2, y, w/2, h};
                    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
                }
            }
            SDL_GetError();
        }
    }*/
}

void RenderWindow::renderBossSkills (Boss &boss) {
    SDL_Texture* texture = boss.frame[7].texture[boss.frame[7].current];
    for (int i = 0; i < 3; i++) {
        SDL_Rect dst;
        dst.x = boss.holeZombies[i].x;
        dst.y = boss.holeZombies[i].y;
        dst.w = boss.holeZombies[i].w;
        dst.h = boss.holeZombies[i].h;
        SDL_RenderCopy (renderer, texture, NULL, &dst);
    }
}

void RenderWindow::display() {
    SDL_RenderPresent (renderer);
}
