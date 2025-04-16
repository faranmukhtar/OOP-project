#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "weapon.h"
using namespace std;

class Player{
    protected:
        Rectangle hitbox;
        int health;
        Weapon* weapon = nullptr;
    public:
        Player(double, double, double, double, int, Weapon*);
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
    private:
        bool onGround;
    public:
        User() : Player(50, 50, 50, 100, 100, nullptr), onGround(true){}
        //Might add more movement mechanics like dash, slide or double jump
        void draw();
        void jump();
};