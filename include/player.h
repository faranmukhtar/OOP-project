#pragma once
#include <vector>
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
#include "projectile.h"
using namespace std;

class Player{
    protected:
        Rectangle hitbox;
        int health;
        std::vector<Projectile> bullets;
    public:
        Player(double x, double y, double width, double height, int health);
        virtual Projectile useWeapon(int, int) = 0;
        virtual void updateBullets();
        Rectangle& getHitbox();
        bool isAlive();
        int getHealth();
        virtual void draw() = 0;
        virtual void jump() =0;
};

class Enemy : public Player{
    public:
        Enemy(double x, double y, double width, double height, int health) : Player(x, y, width, height, health) {}
        Projectile useWeapon(int, int);
        void draw();
};

class User : public Player{
    private:
    float jumpvelocity;
    int jumps;
    bool jumping;
    public:
        User() : Player(50, GROUND_Y - 100, 50, 100, 100){
            jumpvelocity =0;
            jumps = 2;
        }
        //Might add more movement mechanics like dash, slide or double jump
        void draw();
        void jump();
        void move(int, int);
        void updatejump();
        Projectile useWeapon(int, int);
};