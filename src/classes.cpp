#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
using namespace std;

// USE VECTORS FOR COORDINATES LATER

//Unsure if this is needed
class Projectile{

};

//Might have to change attributes for specialized weapons
class Weapon{
    private:
        int ammo;
        int maxAmmo;
        int durability;
    public:
        Weapon(int a){
            this->maxAmmo = ammo;
        }

        //Returns probably a projectile object. Check later
        virtual void shoot() = 0;

        //Unsure whether this is needed
        virtual void reload() = 0;

        int getAmmo(){return ammo;}
};

class Player{
    private:
        Vector2 position;
        int health;
        Weapon* weapon = nullptr;
    public:
        Player(int x, int y, int h, Weapon* w){
            this->health = h;
            this->weapon = w;
            position.x = x;
            position.y = y;
        };

        virtual void assignWeapon(Weapon*) = 0;

        virtual void move(int, int) = 0;

        Vector2 getPosition(){return position;}
};

class Enemy : public Player{

};

class User : public Player{

};

//Setup different types of obstacles later
class Obstacle{
    private:
        Vector2 position;
    public:
        Obstacle(int x, int y){
            position.x = x;
            position.y = y;
        }

        Vector2 getPosition(){return position;}
};