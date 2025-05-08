#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
using namespace std;

class Obstacle{
    private:
        Rectangle hitbox;               //contains obstacle position, width and height
    public:
        Obstacle(float x, float y);

        void draw(Texture2D);           //draws the obstacle taking a Texture2D as parameter
        void move(float x, float y);    //move a fixed amount of x and y

        Rectangle getHitbox();
};