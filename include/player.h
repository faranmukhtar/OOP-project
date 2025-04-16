#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "weapon.h"
using namespace std;

class Player{
    private:
        Vector2 position;
        int health;
        Weapon* weapon = nullptr;
    public:
        Player(int x, int y, int h, Weapon* w);
        virtual void assignWeapon(Weapon*);
        virtual void move(int, int);
        virtual void useWeapon(int, int);
        Vector2 getPosition();
        bool isAlive();
        int getHealth();
        //Maybe virtual
        virtual void draw();
};

class Enemy : public Player{
    public:
        Enemy(int x, int y, int h, Weapon* w) : Player(x, y, h, w) {}
};

class User : public Player{
    private:
        bool onGround;
    public:
        User() : Player(50, 50, 100, nullptr), onGround(true){}
        //Might add more movement mechanics like dash, slide or double jump
        void jump();
};