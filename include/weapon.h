#pragma once
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

//Might delete later

class Weapon{
    private:
        int ammo;
        int maxAmmo;
        int durability;
        double damage;
    public:
        Weapon(int ammo);
        virtual void shoot();
        virtual void reload();
        int getAmmo();
};