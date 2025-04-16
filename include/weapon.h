#pragma once
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

//Might delete later

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