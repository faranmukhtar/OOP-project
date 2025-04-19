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

}

void Game::checkEnemyCollision(){

}

void Game::checkObstacleCollision(){
    
}