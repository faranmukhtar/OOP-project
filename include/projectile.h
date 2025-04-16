#pragma once
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

class Projectile{
    private:
        Rectangle hitbox;
    public:
        void drawProjectile();
        void checkCollision();
        Rectangle getHitbox();
};