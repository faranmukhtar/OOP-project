#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
#include "player.h"
#include "obstacle.h"
#include "projectile.h"
#include <vector>

const string OBSTACLE_PATTERN[][3][3] = {{{"O", "O", "O"},
                                          {"O", "X", "O"},
                                          {"X", "X", "X"}},

                                         {{"O", "O", "O"},
                                          {"O", "X", "X"},
                                          {"X", "X", "X"}},

                                         {{"O", "X", "O"},
                                          {"O", "X", "O"},
                                          {"O", "X", "O"}},

                                         {{"O", "O", "O"},
                                          {"X", "X", "O"},
                                          {"X", "X", "X"}},
                                        
                                         {{"X", "O", "O"},
                                          {"X", "X", "O"},
                                          {"X", "X", "X"}},

                                          {{"O", "O", "O"},
                                          {"X", "X", "X"},
                                          {"X", "X", "X"}},

                                          {{"O", "O", "X"},
                                          {"O", "X", "X"},
                                          {"X", "X", "X"}}};

//Game logic goes here
class Game{
    private:
        User user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
        vector<Projectile*> enemyProjectiles;
        vector<Projectile*> userProjectiles;
    public:
        static double obstacleInterval;
        static double obstacleTimer;

        void spawnEnemy();
        void despawnEnemies();
        void spawnObstacles();
        void despawnObstacles();
        void updateObstacles();
        void checkGameOver();
        void drawBackground();
        void drawScreen();
        //invloves jumping, moving, shooting etc
        void takeInput();
        void checkEnemyCollision();
        void checkObstacleCollision();
};