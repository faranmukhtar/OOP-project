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
        float damage;   
    public:
        Projectile(float speedX, float SpeedY, float x, float y, float radius, float damage);
        void draw(Texture2D texture);       //draws the projectile with Texture2D
        void move();                        //moves the projectile
        void adjustSpeed(float, float);     //changes the speed of projectile
        float getDamage();         
        Vector2 getCenter();
        Vector2 getSpeed();
        float getRadius();
        void setPosition(float, float);
};