#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
using namespace std;

class Projectile{
    protected:
        Vector2 speed;
        Vector2 center;
        double radius;
        Color color;
        double damage;
    public:
        Projectile(double speedX, double SpeedY, double x, double y, double radius, Color color, double damage);
        void draw(Texture2D texture);
        void move();
        void adjustSpeed(double, double);
        double getDamage();
        Vector2 getCenter();
        Vector2 getSpeed();
        double getRadius();
        Color getColor();
        void setPosition(double, double);
};