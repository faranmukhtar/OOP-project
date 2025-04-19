#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
#include "player.h"
#include "obstacle.h"
#include "projectile.h"
#include <vector>

//Game logic goes here
class Game{
    private:
        User user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
        vector<Projectile*> enemyProjectiles;
        vector<Projectile*> userProjectiles;
    public:
        void spawnEnemy();
        void despawnEnemies();
        void spawnObstacle();
        void despawnObstacles();
        void checkGameOver();
        void drawBackground();
        void drawScreen();
        //invloves jumping, moving, shooting etc
        void takeInput();
        void checkEnemyCollision();
        void checkObstacleCollision();
};