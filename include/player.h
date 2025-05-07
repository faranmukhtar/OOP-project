#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "constants.h"
#include "projectile.h"
#include <cmath>

using namespace std;

const double BOMBER_WIDTH = 40;
const double BOMBER_HEIGHT = 40;
const double BOMBER_HEALTH = 30;
const double BOMBER_SPEED = 5;
const double BOMBER_PROJECTILE_SPEEDY = 3;
const double BOMBER_PROJECTILE_RADIUS = 15;
const double BOMBER_PROJECTILE_DAMAGE = 15;

const double GUNNER_WIDTH = 40;
const double GUNNER_HEIGHT = 60;
const double GUNNER_HEALTH = 60;
const double GUNNER_SPEED = 5;
const double GUNNER_MOVE_INTERVAL = 4;
const double GUNNER_SHOOT_INTERVAL = 2.0;
const double GUNNER_PROJECTILE_SPEED_FACTOR = 5;
const double GUNNER_PROJECTILE_RADIUS = 5;
const double GUNNER_PROJECTILE_DAMAGE = 10;

const double FLYER_WIDTH = 40;
const double FLYER_HEIGHT = 20;
const double FLYER_HEALTH = 250;
const double FLYER_DAMAGE = 15;
const double FLYER_SPEED = 15;

const double USER_X = 50;
const double USER_WIDTH = 50;
const double USER_HEIGHT = 100;
const double USER_HEALTH = 100;
const double USER_SHOOT_INTERVAL = 0.5;
const double USER_PROJECTILE_SPEED_FACTOR = 8;
const double USER_PROJECTILE_RADIUS = 5;
const double USER_PROJECTILE_DAMAGE = 20;

const double JUMP_VELOCITY = -15;
const double ACCELARATION = 0.8;

class Player{
    protected:
        Rectangle hitbox;
        double health;
        double damage;
    public:
        Player(double x, double y, double width, double height, double health, double damage);
        virtual Projectile* useWeapon(double, double, Sound) = 0;
        Rectangle getHitbox();
        void takeDamage(double);
        bool isAlive();
        double getHealth();
        double getDamage();
        void setPosition(double, double);
        virtual void draw(Texture2D characterTextures[]) = 0;
};

class Enemy : public Player{
    protected:
        string type;
        Vector2 speed;
    public:
        Enemy(double x, double y, double width, double height, double health, double damage, string type);
        virtual void move() = 0;
        string getType();
};

class Bomber : public Enemy{
    private:
        bool hasDroppedBomb;
        double targetX;
    public:
        Bomber(double x, double y);
        Projectile* useWeapon(double x, double y, Sound) override;
        void move()override;
        void draw(Texture2D characterTextures[]) override;
};

class Gunner : public Enemy{ 
    private:
        Vector2 speed;
        Vector2 startPos;
        double moveTimer;
        float shootTimer;
        bool startPosReached;
    public:
        Gunner(double x, double y, double startX, double startY);
        Projectile* useWeapon(double x, double y, Sound)override;
        void draw(Texture2D characterTextures[]) override;
        void move()override;
};

class Flyer : public Enemy{
    public:
        Flyer(double x, double y);
        void move() override;
        Projectile* useWeapon(double x, double y, Sound)override;       
        void draw(Texture2D characterTextures[]) override;

};

class User : public Player{
    private:
        int jumps;
        int score;
        float jumpvelocity;
        float shootTimer;
        float blockEnergy;
        float frameCount;
        int currentFrame;
        int currentTexture;
        bool onGround;
        bool onObstacle;
        bool isBlocking = false;

        const float maxBlockEnergy = 100.0f;
        const float blockDepletionRate = 75.0f;
        const float blockRegenRate = 33.3f;
    public:
        User();
        void jump(Sound);
        void draw(Texture2D characterTextures[]) override;
        void move(double, double);
        void updatejump(Sound);
        void setOnObstacle(bool);
        Projectile* useWeapon(double, double, Sound)override;
        void updateBlockEnergy();
        void setBlocking(bool);
        float getBlockEnergy() const;
        bool isCurrentlyBlocking() const;
};