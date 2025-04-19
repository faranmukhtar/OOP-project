#include "game.h"

void Game::spawnEnemy(){

}

void Game::despawnEnemies(){

}

void Game::spawnObstacles(){

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
    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->draw();
    }
}

void Game::takeInput(){

}

void Game::checkEnemyCollision(){

}

void Game::checkObstacleCollision(){
    
}