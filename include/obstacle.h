#pragma once
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

class Obstacle{
    private:
        Vector2 position;
    public:
        Obstacle(int x, int y);
        Vector2 getPosition();
        void draw();
};