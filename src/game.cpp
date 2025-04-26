#include "game.h"

double Game::obstacleInterval = 5;
double Game::obstacleTimer = 0;

void Game::spawnEnemy(){
    enemies.push_back(new Bomber(SCREEN_WIDTH / 2, 100));
    enemies.push_back(new Gunner(SCREEN_WIDTH - 200, 200));
    enemies.push_back(new Flyer(SCREEN_WIDTH - 200, SCREEN_HEIGHT / 2));
}

void Game::despawnEnemies(){
    vector<Enemy*> temp;
    for(int i = 0; i < enemies.size(); i++){
        Rectangle hitbox = enemies[i]->getHitbox();
        if(!enemies[i]->isAlive() || hitbox.y + hitbox.height < 0 || hitbox.y > SCREEN_HEIGHT || hitbox.x + hitbox.width < 0 || hitbox.x > SCREEN_WIDTH){
            delete enemies[i];
        }else{
            temp.push_back(enemies[i]);
        }
    }
    enemies = temp;
}

void Game::updateEnemies(){
    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->move(1, 1);
        Projectile* temp = enemies[i]->useWeapon(user.getHitbox().x, user.getHitbox().y);
        if(temp != nullptr) enemyProjectiles.push_back(temp);
    }
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
        obstacles[i]->move(-OBSTACLE_SPEED, 0);
    }
}

void Game::despawnProjectiles(){
    vector<Projectile*> temp;
    for(int i = 0; i < userProjectiles.size(); i++){
        Vector2 center = userProjectiles[i]->getCenter();
        double radius = userProjectiles[i]->getRadius();
        if(center.y + radius < 0 || center.y - radius > SCREEN_HEIGHT || center.x + radius < 0 || center.x - radius > SCREEN_WIDTH){
            delete userProjectiles[i];
        }else{
            temp.push_back(userProjectiles[i]);
        }
    }
    userProjectiles = temp;
}

void Game::updateProjectiles(){
    for(int i = 0; i < enemyProjectiles.size(); i++){
        enemyProjectiles[i]->move();
    }
    for(int i = 0; i < userProjectiles.size(); i++){
        userProjectiles[i]->move();
    }
    despawnProjectiles();
}

void Game::updateGame(){
    updateObstacles();
    updateProjectiles();
    updateEnemies();
    checkObstacleUserCollision();
    checkUserProjectilesCollision();
    despawnObstacles();
    despawnEnemies();
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
    for(int i = 0; i < userProjectiles.size(); i++){
        userProjectiles[i]->draw();
    }
    for(int i = 0; i < enemyProjectiles.size(); i++){
        enemyProjectiles[i]->draw();
    }
    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->draw();
    }
}

void Game::takeInput(){
    if (IsKeyDown(KEY_D) && user.getHitbox().x < SCREEN_WIDTH - user.getHitbox().width){ 
        user.move(PLAYER_SPEED, 0);
    }
    if (IsKeyDown(KEY_A)&&user.getHitbox().x > 0){
        user.move(-PLAYER_SPEED, 0);
    }
    if(IsKeyPressed(KEY_SPACE)){
        user.jump();
    }

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        Projectile* temp = user.useWeapon(GetMouseX(), GetMouseY());
        if(temp != nullptr) userProjectiles.push_back(temp);
    }
    user.updatejump();
}

void Game::checkUserProjectilesCollision(){
    for(int i = 0; i < enemies.size(); i++){
        Rectangle enemyHitbox = enemies[i]->getHitbox();
        for(int j = 0; j < userProjectiles.size(); j++){
            if(CheckCollisionCircleRec(userProjectiles[j]->getCenter(), userProjectiles[j]->getRadius(), enemyHitbox)){
                enemies[i]->takeDamage(userProjectiles[j]->getDamage());
                userProjectiles[j]->setPosition(-1, -1);
            }
        }
    }
}

void Game::checkEnemyProjectilesCollision(){
    Rectangle userHitbox = user.getHitbox();
    for(int i = 0; i < enemyProjectiles.size(); i++){
        if(CheckCollisionCircleRec(enemyProjectiles[i]->getCenter(), enemyProjectiles[i]->getRadius(), userHitbox)){
            user.takeDamage(enemyProjectiles[i]->getDamage());
        }
    }
}

void Game::checkObstacleUserCollision(){
    Rectangle userHitbox = user.getHitbox();
    bool obstacleY = false;
    for(int i = 0; i < obstacles.size(); i++){
        Rectangle obHitbox = obstacles[i]->getHitbox();
        
        if((userHitbox.x + userHitbox.width >= obHitbox.x &&
            userHitbox.x < obHitbox.x) &&
           (userHitbox.y + userHitbox.height > obHitbox.y &&
            userHitbox.y < obHitbox.y + obHitbox.height) &&
            (userHitbox.y + userHitbox.height) - obHitbox.y > 10){

            user.setPosition(obHitbox.x - userHitbox.width, userHitbox.y);
            userHitbox = user.getHitbox();

        }

        if((userHitbox.y + userHitbox.height >= obHitbox.y &&
            userHitbox.y < obHitbox.y) &&
           (userHitbox.x + userHitbox.width > obHitbox.x &&
            userHitbox.x < obHitbox.x + obHitbox.width)){

            user.setPosition(userHitbox.x, obHitbox.y - userHitbox.height);
            obstacleY = true;

        }
    }
    user.setOnObstacle(obstacleY);
}