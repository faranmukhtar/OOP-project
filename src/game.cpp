#include "game.h"


double Game::obstacleInterval = 5;
double Game::obstacleTimer = 0;


void Game::spawnEnemy(){

}

void Game::despawnEnemies(){
}

void Game::spawnObstacles(){
    obstacleTimer += GetFrameTime();
    if(obstacleTimer > obstacleInterval){
        obstacleTimer = 0;
        int obstaclesNumber = rand() % 7;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(OBSTACLE_PATTERN[obstaclesNumber][i][j] == "X"){
                    obstacles.push_back(new Obstacle(SCREEN_WIDTH + GROUND_Y + j * OBSTACLE_LENGTH, GROUND_Y + (i - 3) * OBSTACLE_LENGTH));
                }
            }
        }
    }
}

void Game::despawnObstacles(){
    vector<Obstacle*> temp;
    for(int i = 0; i < obstacles.size(); i++){
        Rectangle hitbox = obstacles[i]->getHitbox();
        if(hitbox.x + hitbox.width < 0){
            delete obstacles[i];
        }else{
            temp.push_back(obstacles[i]);
        }
    }
    obstacles = temp;
}

void Game::updateObstacles(){
    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->move(-10, 0);
        cout << obstacles[i]->getHitbox().x << ", "<< obstacles[i]->getHitbox().y << endl;
    }
    despawnObstacles();
}

void Game::checkGameOver(){

}

void Game::drawBackground(){
    DrawLine(0, GROUND_Y, GetScreenWidth(), GROUND_Y, WHITE);
}

void Game::drawScreen(){
    drawBackground();
    user.draw();
    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->draw();
    }
}

void Game::takeInput(){
    if (IsKeyDown(KEY_RIGHT)&&user.getHitbox().x<SCREEN_WIDTH- user.getHitbox().width){ 
        user.move(10,0);
    }
    if (IsKeyDown(KEY_LEFT)&&user.getHitbox().x>0){
        user.move(-10,0);
    }
    if(IsKeyPressed(KEY_SPACE)){
        user.jump();
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        user.useWeapon(5,5);
    }
    user.updatejump();
}

void Game::checkEnemyCollision(){

}

void Game::checkObstacleCollision(){
    
}