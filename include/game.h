#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "classes.h"

//Game logic goes here
class Game{
    private:
        User user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
    public:
        void spawnEnemy();
        void despawnEnemy(int);
        void spawnObstacle();
        void despawnObstacle(int);
        void checkGameOver();
        void drawBackground();
        void drawScreen();
        //invloves jumping, moving, shooting etc
        void takeInput();
        void checkEnemyCollision();
        void checkObstacleCollision();
};