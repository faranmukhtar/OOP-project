#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
using namespace std;

class Player{
    protected:
        Rectangle hitbox;
        int health;
    public:
        Player(double x, double y, double width, double height, int health);
        virtual void move(int, int);
        virtual void useWeapon(int, int);
        Rectangle getHitbox();
        bool isAlive();
        int getHealth();
        virtual void draw() = 0;
};

class Enemy : public Player{
    public:
        Enemy(double x, double y, double width, double height, int health) : Player(x, y, width, height, health) {}
};

class User : public Player{
    public:
        User() : Player(50, GROUND_Y - 100, 50, 100, 100){}
        //Might add more movement mechanics like dash, slide or double jump
        void draw();
        void jump();
};