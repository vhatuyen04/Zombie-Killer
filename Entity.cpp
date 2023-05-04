#include "Entity.hpp"
#include <iostream>

Entity::Entity(float p_x, float p_y, float p_w, float p_h)
:x(p_x), y(p_y), w(p_w), h(p_h)
{
}

/*float Entity::getX () {
    return x;
}

float Entity::getY () {
    return y;
}

float Entity::getW () {
    return w;
}

float Entity::getH() {
    return h;
}*/

/*void Entity::addAnimation(const std::string& imagePath, int numFrames, int delay) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        // handle error
    }
    SDL_FreeSurface(surface);
    animations.push_back({ texture, numFrames, delay });
}

void Entity::updateAnimation() {
    animationDelayCounter++;
    if (animationDelayCounter >= animations[currentAnimation].delay) {
        currentFrame++;
        if (currentFrame >= animations[currentAnimation].numFrames) {
            currentFrame = 0;
        }
        animationDelayCounter = 0;
    }
    SDL_Rect src = { w * currentFrame, 0, w, h };
    SDL_Rect dest = { x, y, w, h };
    SDL_RenderCopy(renderer, animations[currentAnimation].texture, &src, &dest);
}*/

void Entity::setSizeOfFrame() {
    for (int i = 0; i <= 9; i++) {
        frame[i].x = x;
        frame[i].y = y;
        frame[i].w = w;
        frame[i].h = h;
    }
    trueW = w;
    trueH = h;
}

void Entity::addAnimation (SDL_Renderer* renderer, const char* image_path, int st) {

    SDL_Surface* surf = IMG_Load(image_path);

    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 255, 255));
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(text, 255);
    frame[st].texture.push_back(text);
}

void Entity::updateX (float x1) {
    x += x1;
    for (int i = 0; i <= 9; i++) {
        frame[i].x += x1;
    }
    trueX += x1;
}

void Entity::updateY (float y1) {
    y += y1;
    for (int i = 0; i <= 9; i++) {
        frame[i].y += y1;
    }
    trueY += y1;
}

void Entity::update() {
}

bool Entity::contact (Entity b) {
    if (b.status == -1 || b.status == 4 || status == -1 || status == 4) return 0;
    if (abs(trueY-b.trueY) > 85) return 0; // lech frame 2 khung hinh`
    Entity a(x, y, w, h);
    a.attackZone = attackZone;
    a.trueX = trueX;
    a.w = w;
    a.toTheLeft = toTheLeft;
    a.w += a.trueX;
    b.w += b.trueX;
    if (a.trueX < b.trueX) {
        if (a.toTheLeft) return 0;
        if (a.w+a.attackZone >= b.trueX) return 1;
        return 0;
    }
    else {
        if (!a.toTheLeft) return 0;
        if (a.trueX-b.w <= a.attackZone) return 1;
        return 0;
    }
}

/*SDL_Rect* getFrame() {
    return currentFrame;
}*/
