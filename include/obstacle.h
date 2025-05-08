#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
using namespace std;

class Obstacle{
    private:
        Rectangle hitbox;
    public:
        Obstacle(float x, float y);
        Rectangle getHitbox();
        void draw(Texture2D);
        void move(float x, float y);
};