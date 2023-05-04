#include "Character.hpp"

void Character::creating(SDL_Renderer* renderer) {
    status = 0;
    speed = 25;
    for (int i = 1; i <= 9; i++){
        stringstream ss;
        ss << "data/Images/Character/Idle/NightBorne" << i << ".png";
        addAnimation(renderer, ss.str().c_str(), 0);
    }

    for (int i = 1; i <= 6; i++) {
        stringstream ss;
        ss << "data/Images/Character/Walk/NightBorneMoving"<< i << ".png";
        addAnimation(renderer, ss.str().c_str(), 1);
    }

    for (int i = 1; i <= 12; i++) {
        stringstream ss;
        ss << "data/Images/Character/Attack/NightBorneAttack" << i << ".png";
        addAnimation(renderer, ss.str().c_str(), 2);
    }

    for (int i = 1; i <= 5; i++) {
        stringstream ss;
        ss << "data/Images/Character/Hurt/NightBorneHurt" << i << ".png";
        addAnimation(renderer, ss.str().c_str(), 3);
    }

    for (int i = 1; i <= 23; i++) {
        stringstream ss;
        ss << "data/Images/Character/Death/NightBorneDeath" << i << ".png";
        addAnimation(renderer, ss.str().c_str(), 4);
    }
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack1.png", 5);
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack3.png", 5);
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack9.png", 5);
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack10.png", 5);
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack11.png", 5);
    addAnimation(renderer, "data/Images/Character/Attack/NightBorneAttack12.png", 5);

    for (int i = 0; i < 5; i++) frame[i].current = 0;
    trueY = y+25;
    trueX = x-25;
    attackZone = 10;
    setSizeOfFrame();
    trueW = w/2;
    trueH = h/2;
    frame[1].x -= 5;
    frame[1].y -= 15;
    frame[1].w *= 1.2;
    frame[1].h *= 1.2;
    frame[2].y -= 40;
    if (!toTheLeft) {
        frame[2].x -= 20;
        frame[5].x -= 20;
    }
    else {
        frame[2].x -= 45;
        frame[5].x -= 45;
    }
    frame[2].w *= 1.5;
    frame[2].h *= 1.3;
    frame[3].w *= 1.3;
    frame[3].x -= 15;
    frame[4].w *= 1.5;
    frame[4].h *= 1.5;
    frame[4].x -= 35;
    frame[4].y -= 55;
    frame[5].y -= 40;
    frame[5].w *= 1.5;
    frame[5].h *= 1.3;
    attackDameLeftClick = 50;
    attackDameRightClick = 200;
    attackZone = 25;
    health.isCharacter = 1;
    /*health.x = healthBarX;
    health.y = healthBarY;
    health.maxHealth = healthBarMax;
    health.h = healthBarH;
    health.w = healthBarW;*/
}

void Character::update() {
    if (status == -1) return;
    frame[status].current = (frame[status].current+1) % frame[status].texture.size();
    switch (status) {
        case 4:
            if (frame[4].current == 0) status = -1;
            break;
        case 2: // 2 is equal to attacking
            if (frame[2].current == 0) status = 0; // status 0 is idle
            break;
        case 5:
            if (frame[5].current == 0) status = 0;
            break;
        case 3: // 3 is equal to be injured
            if (frame[3].current == 0) {
                status = 0;
            }
            break;
        default:
            break;
    }

}

void Character::updateCharacterPosition(const Uint8* currentKeyStates)
{
    if (status > 1 || status < 0) return;
    if (currentKeyStates[SDL_SCANCODE_UP] && y > 55)
    {
        // Check if the character is already at the top of the screen
        updateY(-speed);
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN] && y <= window_height - character_height - 45)
    {
        // Check if the character is already at the bottom of the screen
        updateY(speed);
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT] && x > 270+speed) {
        updateX(-speed);
        status = 1;
        toTheLeft = 1;
        flip = 1;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT] && x < window_width - character_width - 25) {
        updateX(speed);
        status = 1;
        toTheLeft = 0;
        flip = 0;
    }
    else status = 0;
}

void Character::attackZombie (Zombie &z) {
    if (!contact(z)) return;
    if (status == 2 && frame[2].current >= 9) {
        z.takeDamage (attackDameRightClick);
    }
    else if (status == 5 && frame[5].current == 3 && !checkLeftClick) {
        z.takeDamage (attackDameLeftClick);
        checkLeftClick = 1;
    }
    if (z.status == 4) {
        score += 10;
        return;
    }
}

void Character::attackBoss (Boss &boss) {
    if (!contact(boss)) return;
    if (status == 2 && frame[2].current >= 10) {
        boss.injured (attackDameRightClick);
    }
    else if (status == 5 && frame[5].current == 3) {
        boss.injured (attackDameLeftClick);
    }
    if (boss.status == 4) {
        score += 100;
        return;
    }
}

void Character::injured (int damage) {
    status = 3;
    frame[2].current = 0;
    health.update(damage);
    if (health.currentHealth == 0) {
        status = 4;
    }
}
