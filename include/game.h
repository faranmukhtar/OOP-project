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

// Exception for File handling
class FileException : public exception{
    public:
        const char * what() const noexcept override{
            return "Unable to open file";
        }
};

// Defined pattern for each obstacle
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

                                        
const float PLAYER_SPEED = 10;          //player movement speed
const float OBSTACLE_SPEED = 10;        //Obstacle movement speed

class Game{
    private:
        User* user;                                     // Player character
        vector<Enemy*> enemies;                         // Enemies(Non player characters)
        vector<Obstacle*> obstacles;
        vector<Projectile*> enemyProjectiles;
        vector<Projectile*> userProjectiles;

        // Fonts used
        Font fontAnonymous;

        //Textures used
        Texture2D obstacleTexture;
        Texture2D flyerTexture[1];                                          //had to make array of 1 to a achieve polymorphism
        Texture2D bomberTexture[1];                                         //same for this
        Texture2D gunnerTextures[2];
        Texture2D projectileTextures[2];
        Texture2D userTextures[5];
        Texture2D startScreenTexture[2];
        Texture2D Instructions;
        Texture2D gameOverTexture[2];
        Texture2D backgroundTextures[5];
        Texture2D groundTextures[2];

        const float groundScrollSpeed = 300;                                // rate at which ground texture is moving
        const float backgroundScrollSpeed[5] = {0, 20, 40, 60, 80};         // rates at which the background textures are moving

        const int baseScoreRate = 10;                                       // rate at which score is increasing

        const int bomberKillBonus = 50;                                       
        const int gunnerKillBonus = 100;
        const int flyerKillBonus = 30;

        const float obstacleInterval = 5;                                   // time(seconds) it takes to spawn a new obstacle or flyer
        const float gunnerInterval = 4;                                     // time(seconds) it takes to spawn a new gunner
        const float bomberInterval = 10;                                    // time(seconds) it take to spawn new bombers

        const float outOfBoundsDamage = 0.5;                                // damage per frame for user out of bounds

        float groundScrollX;                                                // distance moved by ground
        float backgroundScrollX[5];                                         // distances moved by backgrounds

        int score = 0;                                                      // current score
        int Highscore = -99;                                                // high score

        float obstacleTimer = 0;                                            // keeps time of last obstacle or flyer spawn 
        float gunnerTimer = 0;                                              // keeps time of last gunner spawn 
        float bomberTimer = 0;                                              // keeps time of last bomber spawn 
        float scoreTimer = 0;                                               // keeps time of last score update 

        //All sounds used
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
        Game();                                                             //initializes game
        void init();                                                        //reinitializes game if player wants to replay

        void loadSounds();                                                  //loads all sounds from file
        void unloadSounds();                                                //unloads all sounds
        void loadAssets();                                                  //loads all textures and fonts from file
        void unloadAssets();                                                //unload all textures and fonts

        void spawnEntities();                                               //Spawns enemies and obstacles using spawnObstacles()
        void spawnObstacles();                                              //Spawns random obstacles

        void despawnEnemies();                                              //Despawns enemies when out of bounds or dead
        void despawnObstacles();                                            //Despawns obstacles when out of bounds
        void despawnProjectiles();                                          //Despawns projectiles when out of bounds

        void updateEnemies();                                               //Allows enemies to move and attack
        void updateObstacles();                                             //Moves obstacles
        void updateProjectiles();                                           //Moves projectiles
        void updateGame();                                                  //Updates each entity in game class

        void drawGround();                                                  //draws ground textures
        void drawBackground();                                              //draws background textures
        void drawScreen();                                                  //draws the entire screen when the user is playing the game
        bool drawLogo();                                                    //draws the logo and loops until user feedback
        bool drawControls();                                                //draws the Controls and loops until user feedback
        bool drawGameOver();                                                //draws the Game Over screen and loops until user feedback

        void takeInput();                                                   //Takes user input and calls functions accordingly
        void checkUserProjectilesCollision();                               //Checks if any user projectiles hits the enemies and updates enemy and projectile if hit
        void checkEnemyProjectilesCollision();                              //Checks if any enemy projectiles hits the user and updates user and projectile if hit
        void checkObstacleUserCollision();                                  //Checks if any user projectiles hits the enemies and updates enemy and projectile if hit
        void checkUserOutOfBounds();                                        //Check if user is out of bounds and updates user accordingly

        void loadHighScore();                                               //loads high score from file
        bool checkGameOver();                                               //checks for game over

        void saveHighScore();                                               //saves new high score
        void updateScore();                                                 //updates the score 
        void addKillScore(const string& enemyType);                         //adds kill score to current score based on enemy type
        ~Game();
};