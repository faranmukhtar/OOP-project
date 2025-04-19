#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
using namespace std;

class Obstacle{
    private:
        Rectangle hitbox;
    public:
        Obstacle(double x, double y);
        Rectangle getHitbox();
        void draw();
        void move(double x, double y);
};