#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
using namespace std;

class Projectile{
    protected:
        Vector2 speed;
        Vector2 center;
        float radius;
        Color color;
        float damage;
    public:
        Projectile(float speedX, float SpeedY, float x, float y, float radius, Color color, float damage);
        void draw(Texture2D texture);
        void move();
        void adjustSpeed(float, float);
        float getDamage();
        Vector2 getCenter();
        Vector2 getSpeed();
        float getRadius();
        Color getColor();
        void setPosition(float, float);
};