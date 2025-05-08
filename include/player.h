#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "constants.h"
#include "projectile.h"
#include <cmath>

using namespace std;

//BOMBER CONSTANTS
const float BOMBER_WIDTH = 40;
const float BOMBER_HEIGHT = 40;
const float BOMBER_HEALTH = 30;
const float BOMBER_SPEED = 5;
const float BOMBER_PROJECTILE_SPEEDY = 5;
const float BOMBER_PROJECTILE_RADIUS = 10;
const float BOMBER_PROJECTILE_DAMAGE = 15;


//GUNNER CONSTANTS
const float GUNNER_WIDTH = 40;
const float GUNNER_HEIGHT = 60;
const float GUNNER_HEALTH = 60;
const float GUNNER_SPEED = 5;
const float GUNNER_MOVE_INTERVAL = 0.5;
const float GUNNER_SHOOT_INTERVAL = 2.0;
const float GUNNER_PROJECTILE_SPEED_FACTOR = 5;
const float GUNNER_PROJECTILE_RADIUS = 5;
const float GUNNER_PROJECTILE_DAMAGE = 10;


//FLYER CONSTANTS
const float FLYER_WIDTH = 40;
const float FLYER_HEIGHT = 40;
const float FLYER_HEALTH = 250;
const float FLYER_DAMAGE = 15;
const float FLYER_SPEED = 15;


//USER CONSTANTS
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
        Rectangle hitbox;   //contains player position, width and height
        float health;
        float damage;

        float frameCount;   //Keeps track of total frames passed since current frame of the texture
        int currentFrame;   //Keeps track of the current frame of the texture

        bool isDamaged;     //Tells if the player was damaged
        float damageFrames; //Keeps time of the last time player was damaged
    public:
        Player(float x, float y, float width, float height, float health, float damage);
        virtual Projectile* useWeapon(float, float, Sound) = 0;            //takes target position and weapon sound as parameters and returns a projectile
        
        void takeDamage(float);                                             //takes a fixed amount of damage
        void setPosition(float, float);                                     //sets the position to a fixed amount
        virtual void draw(Texture2D characterTextures[]) = 0;               //takes a Texture2D array and draws the Player

        bool isAlive();                                                     //returns whether the player is alive or not
        Rectangle getHitbox();
        float getHealth();
        float getDamage();
};

class Enemy : public Player{
    protected:
        string type;            //type of enemy
        Vector2 speed;          //speed of movement
    public:
        Enemy(float x, float y, float width, float height, float health, float damage, string type);
        virtual void move() = 0;    //Allows the enemy to move
        string getType();
};

class Bomber : public Enemy{
    private:    
        bool hasDroppedBomb;        //Keeps track of if the bomb is dropped or not
        float targetX;              //x position at which it is supposed to drop a bomb
    public:
        Bomber(float x, float y);
        Projectile* useWeapon(float x, float y, Sound) override;    //inherited from player
        void move()override;                                        //inherited from enemy
        void draw(Texture2D characterTextures[]) override;          //inherited from player
};

class Gunner : public Enemy{ 
    private:
        Vector2 startPos;           //position it is supposed to reach before shooting
        float moveTimer;            //keeps track of last movement
        float shootTimer;           //keeps track of last attack
        bool startPosReached;       //shows if it has reached startPos
        int currentTexture;         //shows the current texture in the array
    public:
        Gunner(float x, float y, float startX, float startY);
        Projectile* useWeapon(float x, float y, Sound)override;         //inherited from player
        void draw(Texture2D characterTextures[]) override;              //inherited from player
        void move()override;                                            //inherited from enemy
};

class Flyer : public Enemy{
    public:
        Flyer(float x, float y);
        void move() override;                                           //inherited from enemy
        Projectile* useWeapon(float x, float y, Sound)override;         //inherited from player     
        void draw(Texture2D characterTextures[]) override;              //inherited from player

};

class User : public Player{
    private:
        int jumps;                                  //total number of jumps the user can curently do                                  
        float jumpvelocity;                         //show the current vertical velocity
        float shootTimer;                           //time before last attack
        float blockEnergy;                          //shows the percentage of time that user can block
        int currentTexture;                         //keeps track of current texture
        bool onGround;                              //shows whether user is on ground or not
        bool onObstacle;                            //shows whether user is on obstacle or not
        bool isBlocking;                            //shows if user is blocking or not

        const float maxBlockEnergy = 100.0f;
        const float blockDepletionRate = 75.0f;
        const float blockRegenRate = 33.3f;
    public:
        User();
        void jump(Sound);                                       //Takes Sound as parameter and allows user to jump and double jump
        void draw(Texture2D characterTextures[]) override;      //inherited from player
        void move(float, float);                                //moves a fixed amount
        void updatejump(Sound);                                 //updates velocity and number of jumps
        void setOnObstacle(bool);
        Projectile* useWeapon(float, float, Sound)override;     //inherited from player
        void updateBlockEnergy();                               
        void setBlocking(bool);
        float getBlockEnergy() const;
        bool isCurrentlyBlocking() const;
};