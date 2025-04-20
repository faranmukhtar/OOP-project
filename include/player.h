#pragma once
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "constants.h"
#include "projectile.h"
#include <cmath>
using namespace std;

class Player{
    protected:
        Rectangle hitbox;
        int health;
        bool alive;
    
    public:
        Player(double x, double y, double width, double height, int health);
        virtual void move(int x, int y);
        virtual Projectile* useWeapon(int x, int y);
        Rectangle getHitbox();
        bool isAlive();
        int getHealth();
        virtual void draw() = 0;
};

class Enemy : public Player{
    protected:
        float timer;
    public:
        Enemy(double x, double y, double width, double height, int health) :Player(x, y, width, height, health),timer(0){}
        virtual void takeDamage() = 0;
};

class Bomber : public Enemy{
    private:
        bool hasDroppedBomb;
        int moveSpeed;
    
    public:
        Bomber(double x, double y) : Enemy(x, y, 40, 40, 1), hasDroppedBomb(false), moveSpeed(2){}
        Projectile* useWeapon(int x, int y) override;
        void move(int x, int y)override;
        void takeDamage()override;
        void draw() override;
};

class Gunner : public Enemy{ 
    private:
        int moveDirection;
        const float moveInterval = 1.5f;
        const float shootInterval = 1.0f;
        float shootTimer;
    
    public:
        Gunner(double x, double y) : Enemy(x, y, 40, 60, 3), moveDirection(1), shootTimer(0){}
        Projectile* useWeapon(int x, int y)override;
        void draw() override;
        void takeDamage()override;
        void move(int x, int y)override;
};

class Bird : public Enemy{
    public:
        Bird(double x, double y);
        void move(int x, int y)override{}
        Projectile* useWeapon(int x, int y)override;
        void takeDamage() override;
        void draw() override;


};

class User : public Player{
    public:
        User() : Player(50, GROUND_Y - 100, 50, 100, 100) {}
        //Might add more movement mechanics like dash, slide or double jump
        void draw() override;
        void jump();
};