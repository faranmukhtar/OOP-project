#include "game.h"


void Game::spawnEnemy(){

}

void Game::despawnEnemies(){

}

void Game::spawnObstacle(){

}

void Game::despawnObstacles(){

}

void Game::checkGameOver(){

}

void Game::drawBackground(){
    DrawLine(0, GROUND_Y, GetScreenWidth(), GROUND_Y, WHITE);
}

void Game::drawScreen(){
    drawBackground();
    user.draw();
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