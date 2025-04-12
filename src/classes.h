#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include <vector>
using namespace std;

class Weapon{
    private:
        int ammo;
        int maxAmmo;
        int durability;
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
        Vector2 getPosition();
};

class Enemy : public Player{

};

class User : public Player{

};

class Obstacle{
    private:
        Vector2 position;
    public:
        Obstacle(int x, int y);
        Vector2 getPosition();
};