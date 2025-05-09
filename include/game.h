#pragma once
#include "raylib.h"
#include<stdexcept>
#include "resource_dir.h"
#include "constants.h"
#include "player.h"
#include "obstacle.h"
#include "projectile.h"
#include <fstream>
#include <vector>

class FileException : public exception{
    public:
        const char * what() const noexcept override{
            return "Unable to open file";
        }
};

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

        Font fontAnonymous;

        Texture2D obstacleTexture;
        Texture2D flyerTexture[1];
        Texture2D bomberTexture[1];
        Texture2D gunnerTextures[2];
        Texture2D projectileTextures[4];
        Texture2D userTextures[4];
        Texture2D startScreenTexture[2];
        Texture2D Instructions;
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


        Music bgMusic;
        Sound gunnerSpawnSound;  
        Sound bomberSpawnSound;
        Sound bombExplosionSound;
        Sound flyerSound;       
        Sound userHitSound;
        Sound userDeathSound;
        Sound enemyDeathSound;
        Sound gunnerShootSound;
        Sound bomberShootSound;
        Sound userShootSound;
        Sound userJumpSound;

    public:
        RenderTexture2D renderTexture;

        Game();
        void init();

        void loadSounds();
        void unloadSounds();
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
        bool drawControls();
        bool drawGameOver();

        void takeInput();
        void checkUserProjectilesCollision();
        void checkEnemyProjectilesCollision();
        void checkObstacleUserCollision();
        void checkUserOutOfBounds();

        void loadHighScore();
        bool checkGameOver();

        void saveHighScore();
        void updateScore();
        void addKillScore(const string& enemyType);
        ~Game();
};