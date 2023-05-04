#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
using namespace std;

const int window_height = 600, window_width = 1200;
const int character_x = 275, character_y = 250, character_height = 125, character_width = 150;


class Entity {
public:
    Entity (float p_x, float p_y, float p_w, float p_h);
    bool isBoss = 0;
    int status, type;
    double lastAttack = 0, attackSpeed, speed, attackDame;
    bool readyToAttack = 1, toTheLeft = 0, flip = 0;
    float attackZone;
    struct inforOfFrame {
        float x, y, w, h;
        int current = 0;
        Uint32 last_update_time = 0;
        Uint32 delay = 0;
        vector <SDL_Texture*> texture;
    }frame[10];
    float x, y, w, h, trueX, trueY, trueW, trueH;
    SDL_Texture* getTex();
    void setSizeOfFrame();
    void updateX (float x1);
    void updateY (float y1);
    void addAnimation (SDL_Renderer* renderer, const char* image_path, int st);
    float getMaxSizeY();
    virtual void update();
    bool contact (Entity b);
    //SDL_Rect getFrame();
    // 5 states tuong duong voi 5 trang thai
    // 0 la dung yen, 1 la di chuyen, 2 la attack, 3 la bi tan cong, 4 la chet, 5 la xuat hien (danh cho zombie)
};
