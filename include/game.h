#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
#include "player.h"
#include "obstacle.h"
#include "projectile.h"
#include <fstream>
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

const double PLAYER_SPEED = 10;
const double OBSTACLE_SPEED = 10;

//Game logic goes here
class Game{
    private:
        User user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
        vector<Projectile*> enemyProjectiles;
        vector<Projectile*> userProjectiles;
        int score = 0;
        int Highscore = -99;
        const double obstacleInterval = 5;
        double obstacleTimer = 0;
        const double gunnerInterval = 15;
        double gunnerTimer = 0;
        const double bomberInterval = 10;
        double bomberTimer = 0;
        const int baseScoreRate = 10;
        const int bomberKillBonus = 50;
        const int gunnerKillBonus = 100;
        const int flyerKillBonus = 30;
        double scoreTimer = 0;

    public:
        void spawnEntities();
        void despawnEnemies();
        void updateEnemies();
        void spawnObstacles();
        void despawnObstacles();
        void updateObstacles();
        void despawnProjectiles();
        void updateProjectiles();
        void updateGame();
        void loopGameOver();
        bool checkGameOver();
        void drawBackground();
        void drawScreen();
        void takeInput();
        void checkUserProjectilesCollision();
        void checkEnemyProjectilesCollision();
        void checkObstacleUserCollision();
        void displayGameOver();
        void drawGameOver();
        void displayScores();
        void updateScore();
        void addKillScore(const string& enemyType);
};