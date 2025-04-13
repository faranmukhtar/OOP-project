#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include <vector>
using namespace std;

//Future considerations:
//Use of Projectile class
//Use Rectangle instead of Vector2

class Weapon{
    private:
        int ammo;
        int maxAmmo;
        int durability;
        double damage;
    public:
        Weapon(int a);
        virtual void shoot();
        virtual void reload();
        int getAmmo();
};

class Player{
    private:
        Vector2 position;
        int health;
        Weapon* weapon = nullptr;
        vector<Vector2> projectiles;
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

class Obstacle{
    private:
        Vector2 position;
    public:
        Obstacle(int x, int y);
        Vector2 getPosition();
        void draw();
};