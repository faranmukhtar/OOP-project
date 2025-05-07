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
        User* user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
        vector<Projectile*> enemyProjectiles;
        vector<Projectile*> userProjectiles;

        Font fontOswald;

        Texture2D characterTextures[3];
        Texture2D startScreenTexture[2];
        Texture2D gameOverTexture[2];
        Texture2D backgroundTextures[5];
        Texture2D groundTextures[2];

        const double groundScrollSpeed = 300;
        const double backgroundScrollSpeed[5] = {0, 20, 40, 60, 80};

        double groundScrollX;
        double backgroundScrollX[5];

        const int baseScoreRate = 10;
        const int bomberKillBonus = 50;
        const int gunnerKillBonus = 100;
        const int flyerKillBonus = 30;
        const double obstacleInterval = 5;
        const double gunnerInterval = 6;
        const double bomberInterval = 10;
        const double outOfBoundsDamage = 0.5;

        int score = 0;
        int Highscore = -99;
        double obstacleTimer = 0;
        double gunnerTimer = 0;
        double bomberTimer = 0;
        double scoreTimer = 0;
    public:
        RenderTexture2D renderTexture;

        Game();
        void init();

        void loadAssets();
        void unloadAssets();

        void spawnEntities();
        void spawnObstacles();

        void despawnEnemies();
        void despawnObstacles();
        void despawnProjectiles();

        void updateEnemies();
        void updateObstacles();
        void updateProjectiles();
        void updateGame();

        void drawGround();
        void drawBackground();
        void drawScreen();
        bool drawLogo();
        bool drawGameOver();

        void takeInput();
        void checkUserProjectilesCollision();
        void checkEnemyProjectilesCollision();
        void checkObstacleUserCollision();
        void checkUserOutOfBounds();

        void displayGameOver();
        bool checkGameOver();

        void displayScores();
        void updateScore();
        void addKillScore(const string& enemyType);
        ~Game();
};