#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "weapon.h"
#include "constants.h"
using namespace std;

class Player{
    protected:
        Rectangle hitbox;
        int health;
        Weapon* weapon = nullptr;
    public:
        Player(double x, double y, double width, double height, int health, Weapon* weapon);
        virtual void assignWeapon(Weapon*);
        virtual void move(int, int);
        virtual void useWeapon(int, int);
        Rectangle getHitbox();
        bool isAlive();
        int getHealth();
        virtual void draw() = 0;
};

class Enemy : public Player{
    public:
        Enemy(double x, double y, double width, double height, int health, Weapon* weapon) : Player(x, y, width, height, health, weapon) {}
};

class User : public Player{
    public:
        User() : Player(50, GROUND_Y - 100, 50, 100, 100, nullptr){}
        //Might add more movement mechanics like dash, slide or double jump
        void draw();
        void jump();
};