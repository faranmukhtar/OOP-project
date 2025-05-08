#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "constants.h"
#include "projectile.h"
#include <cmath>

using namespace std;

const float BOMBER_WIDTH = 40;
const float BOMBER_HEIGHT = 40;
const float BOMBER_HEALTH = 30;
const float BOMBER_SPEED = 5;
const float BOMBER_PROJECTILE_SPEEDY = 5;
const float BOMBER_PROJECTILE_RADIUS = 10;
const float BOMBER_PROJECTILE_DAMAGE = 15;

const float GUNNER_WIDTH = 40;
const float GUNNER_HEIGHT = 60;
const float GUNNER_HEALTH = 60;
const float GUNNER_SPEED = 5;
const float GUNNER_MOVE_INTERVAL = 0.5;
const float GUNNER_SHOOT_INTERVAL = 2;
const float GUNNER_PROJECTILE_SPEED_FACTOR = 5;
const float GUNNER_PROJECTILE_RADIUS = 5;
const float GUNNER_PROJECTILE_DAMAGE = 10;

const float FLYER_WIDTH = 40;
const float FLYER_HEIGHT = 40;
const float FLYER_HEALTH = 250;
const float FLYER_DAMAGE = 15;
const float FLYER_SPEED = 15;

const float USER_X = 50;
const float USER_WIDTH = 50;
const float USER_HEIGHT = 100;
const float USER_HEALTH = 100;
const float USER_SHOOT_INTERVAL = 0.5;
const float USER_PROJECTILE_SPEED_FACTOR = 8;
const float USER_PROJECTILE_RADIUS = 5;
const float USER_PROJECTILE_DAMAGE = 20;

const float JUMP_VELOCITY = -15;
const float ACCELARATION = 0.8;

class Player{
    protected:
        Rectangle hitbox;
        float health;
        float damage;
        float frameCount;
        int currentFrame;
    public:
        Player(float x, float y, float width, float height, float health, float damage);
        virtual Projectile* useWeapon(float, float, Sound) = 0;
        Rectangle getHitbox();
        void takeDamage(float);
        bool isAlive();
        float getHealth();
        float getDamage();
        void setPosition(float, float);
        virtual void draw(Texture2D characterTextures[]) = 0;
};

class Enemy : public Player{
    protected:
        string type;
        Vector2 speed;
    public:
        Enemy(float x, float y, float width, float height, float health, float damage, string type);
        virtual void move() = 0;
        string getType();
};

class Bomber : public Enemy{
    private:
        bool hasDroppedBomb;
        float targetX;
    public:
        Bomber(float x, float y);
        Projectile* useWeapon(float x, float y, Sound) override;
        void move()override;
        void draw(Texture2D characterTextures[]) override;
};

class Gunner : public Enemy{ 
    private:
        Vector2 speed;
        Vector2 startPos;
        float moveTimer;
        float shootTimer;
        bool startPosReached;
        int currentTexture;
    public:
        Gunner(float x, float y, float startX, float startY);
        Projectile* useWeapon(float x, float y, Sound)override;
        void draw(Texture2D characterTextures[]) override;
        void move()override;
};

class Flyer : public Enemy{
    public:
        Flyer(float x, float y);
        void move() override;
        Projectile* useWeapon(float x, float y, Sound)override;       
        void draw(Texture2D characterTextures[]) override;

};

class User : public Player{
    private:
        int jumps;
        int score;
        float jumpvelocity;
        float shootTimer;
        float blockEnergy;
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
        void move(float, float);
        void updatejump(Sound);
        void setOnObstacle(bool);
        Projectile* useWeapon(float, float, Sound)override;
        void updateBlockEnergy();
        void setBlocking(bool);
        float getBlockEnergy() const;
        bool isCurrentlyBlocking() const;
};