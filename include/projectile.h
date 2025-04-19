#pragma once
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

class Projectile{
    protected:
        Vector2 speed;
        Vector2 center;
        double radius;
        Color color;
    public:
        Projectile(double, double, double, double, double, Color);
        void drawProjectile();
        void move();
        void adjustSpeed(double, double);
        Vector2 getCenter();
        Vector2 getSpeed();
        double getRadius();
        Color getColor();
};