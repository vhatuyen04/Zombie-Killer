#include "Boss.hpp"

using namespace std;

Boss::Boss() : Entity (x, y, w, h) {

}

void Boss::creating (SDL_Renderer* renderer) {
    isBoss = 1;
    x = 500;
    y = 285;
    w = 400;
    h = 200;
    setSizeOfFrame();
    trueX = x+w/2;
    trueY = y+h/2;
    trueW = w/2;
    health = 1000;
    status = 0;
    speed = 5;
    attackZone = 200;
    attackDame = 5;
    toTheLeft = 1;
    for (int i = 1; i <= 8; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Idle/Bringer-of-Death_Idle_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 0);
    }

    for (int i = 1; i <= 8; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Walk/Bringer-of-Death_Walk_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 1);
    }

    for (int i = 1; i <= 10; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Attack/Bringer-of-Death_Attack_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 2);
    }

    for (int i = 1; i <= 3; i++) {
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Hurt/Bringer-of-Death_Hurt_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 3);
    }

    for (int i = 1; i <= 10; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Death/Bringer-of-Death_Death_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 4);
    }

    for (int i = 1; i <= 16; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Spell/Bringer-of-Death_Spell_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 7);
    }

    for (int i = 1; i <= 9; i++){
        stringstream ss;
        ss << "data/Images/Boss/Bringer-Of-Death/Individual Sprite/Cast/Bringer-of-Death_Cast_" << i << ".png";
        addAnimation (renderer, ss.str().c_str(), 8);
    }
    frame[2].delay = 100;
    frame[0].delay = 100;
    frame[3].delay = 100;
}

float Boss::distance (float x1, float y1) {
    float realX, realY;
    if (!flip) {
        realX = x+5/6*x;
        realY = y+3/4*y;
    }
    return sqrt((x1-realX)*(x1-realX)+(y1-realY)*(y1-realY));
}

void Boss::walk () {
    float distanceX = targetX - trueX;
    float distanceY = targetY - trueY;
    float distanceTotal = sqrt(distanceX*distanceX + distanceY*distanceY);
    if (distanceTotal < speed) {
        spotToGo = 0;
        return;
    }
    float vX = speed * (distanceX / distanceTotal);
    float vY = speed * (distanceY / distanceTotal);
    //cout<<targetX<<' '<<x<<' '<<targetY<<' '<<y<<endl;
    //cout<<abs(targetX-trueX)<<' '<<abs(targetY-trueY)<<' '<<distanceX<<' '<<distanceY<<' '<<vX<<' '<<vY<<' '<<trueX<<' '<<trueY<<endl;
    if (abs(targetX-trueX) >= 0.5 || abs(targetY-trueY) >= 0.5) {
        if (vX > 0) {
            flip = 1;
            toTheLeft = 0;
        }
        else {
            flip = 0;
            toTheLeft = 1;
        }
        updateX (vX);
        updateY (vY);
    }
}

void Boss::chasingCharacter (Character &player) {
    if (contact(player)) {
        status = 2;
    }
    else {
        status = 1;
        spotToGo = 1;
        targetX = player.trueX;
        targetY = player.trueY;
        walk();
    }
}

void Boss::summonZombies () {
    for (int i = 0; i < 3; i++) {
        holeZombies[i].w = 400;
        holeZombies[i].h = 300;
        holeZombies[i].x = rand()%(1000-385+1)+200;
        holeZombies[i].y = rand()%300;
    }
}

void Boss::createExplosion () {
    int r = rand()%2;
    if (!r) return;
    hole newHole;
    newHole.w = 200;
    newHole.h = 300;
    newHole.x = rand()%(1000-285+1)+285;
    newHole.y = rand()%350;
    //cout<<newHole.w<<' '<<newHole.h<<' '<<newHole.x<<' '<<newHole.y<<endl;
    explosion.push_back(newHole);
}

void Boss::behavior (Character &player) {
    if (!spotToGo) {
        spotToGo = 1;
        targetX = rand()%(maxX-minX)+minX;
        targetY = rand()%(maxY-minY)+minY;
    }
    float dis1 = (targetX-trueX)*(targetX-trueX)+(targetY-trueY)*(targetY-trueY);
    float dis2 = (player.trueX-trueX)*(player.trueX-trueX)+(player.trueY-trueY)*(player.trueY-trueY);
    //cout<<boss.targetX<<' '<<boss.targetY<<endl;
    if (dis2 < dis1) { // chon player de tan cong
        chasingCharacter (player);
    }
    else {
        status = 1;
        walk();
    }
}

void Boss::update (Character &player) {
    Uint32 current = SDL_GetTicks();
    bool change(0);
    if (current-frame[status].last_update_time >= frame[status].delay) {
        frame[status].current = (frame[status].current+1) % frame[status].texture.size();
        frame[status].last_update_time = current;
        change = 1;
    }
    int haveMood = rand()%2;
    if (!change) return;
    switch (status) {
    case 0:
        if (frame[status].current == 0 || (!appear && current-lastIdle > 5000) || haveMood) {
            appear = 1;
            lastIdle = current;
            int r = rand()%2;
            if (!r || current-lastCast < 10000) status = 1;
            else {
                status = 7;
                lastCast = current;
            }
        }
        break;
    case 1:
        if (frame[status].current == 0 && current-lastWalk > 10000) {
            lastWalk = current;
            status = 0;
        }
        break;
    case 2:
        if (frame[status].current == 0 && !contact(player)) {
            status = 0;
        }
        break;
    case 3:
        if (frame[status].current == 0) {
            status = 0;
        }
        break;
    case 4:
        if (frame[status].current == 0) status = -1;
        break;
    case 7:
        if (frame[status].current == 0) {
            for (int i = 0; i < 3; i++) {
                zombies.push(make_pair(holeZombies[i].x+holeZombies[i].w*1/3, holeZombies[i].y+holeZombies[i].h*2/3));
            }
            if (contact(player)) status = 2;
            else status = 0;
        }
        break;
    default:
        break;
    }
}

void Boss::listToDo (Character &player) {
    switch (status) {
    case 1:
        behavior (player);
        break;
    case 2:
        if (contact(player) && status == 2 && frame[2].current >= 5 && frame[2].current <= 7) {
            player.injured(attackDame);
        }
        break;
    case 7:
        if (!frame[status].current) {
            summonZombies ();
            x = rand()%(maxX-minX+1)+minX;
            y = rand()%(maxY-minY+1)+minY;
            setSizeOfFrame();
            trueX = x+w/2;
            trueY = y+h/2;
        }
        break;
    default:
        break;
    }
    update(player);
}

void Boss::injured (int damage) {
    status = 3;
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    if (!health) status = 4;
}
