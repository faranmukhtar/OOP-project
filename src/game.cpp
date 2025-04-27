#include "game.h"

Game::Game(){
    obstacleInterval = 5;
    obstacleTimer = 0;
    gunnerTimer = 0;
    gunnerInterval = 10;
    bomberTimer = 0;
    bomberInterval = 5;
}

void Game::spawnEntities(){
    obstacleTimer += GetFrameTime();
    gunnerTimer += GetFrameTime();
    bomberTimer += GetFrameTime();

    if(gunnerTimer > gunnerInterval){
        gunnerTimer = 0;
        enemies.push_back(new Gunner(SCREEN_WIDTH + 200, 130));
    }

    if(bomberTimer > bomberInterval){
        bomberTimer = 0;
        int randInt = rand() % 3;
        enemies.push_back(new Bomber(SCREEN_WIDTH + 80, 80));
        enemies.push_back(new Bomber(SCREEN_WIDTH + 160, 80));
        if(randInt >= 1){
            enemies.push_back(new Bomber(SCREEN_WIDTH + 240, 80));
        }
        if(randInt == 2){
            enemies.push_back(new Bomber(SCREEN_WIDTH + 320, 80));
        }
    }

    if(obstacleTimer > obstacleInterval){
        if(rand() % 4 == 0){
            enemies.push_back(new Flyer(SCREEN_WIDTH + 200, GROUND_Y - (rand() % 100) - 50));
        }else{
            spawnObstacles();
        }
        obstacleTimer = 0;
    }
}

void Game::despawnEnemies(){
    vector<Enemy*> temp;
    for(int i = 0; i < enemies.size(); i++){
        Rectangle hitbox = enemies[i]->getHitbox();
        if(!enemies[i]->isAlive() || hitbox.y + hitbox.height < 0 || hitbox.x + hitbox.width < 0){
            delete enemies[i];
        }else{
            temp.push_back(enemies[i]);
        }
    }
    enemies = temp;
}

void Game::updateEnemies(){
    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->move();
        Projectile* temp = nullptr;
        if(enemies[i]->getType() == "bomber"){
            temp = enemies[i]->useWeapon(0, 0);
        }
        if(enemies[i]->getType() == "flyer"){
            if(CheckCollisionRecs(enemies[i]->getHitbox(), user.getHitbox())){
                user.takeDamage(enemies[i]->getDamage());
                enemies[i]->takeDamage(1000);
            }
        }
        if(temp != nullptr) enemyProjectiles.push_back(temp);
    }
}

void Game::spawnObstacles(){
    int obstaclesNumber = rand() % 7;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(OBSTACLE_PATTERN[obstaclesNumber][i][j] == "X"){
                obstacles.push_back(new Obstacle(SCREEN_WIDTH + GROUND_Y + j * OBSTACLE_LENGTH, GROUND_Y + (i - 3) * OBSTACLE_LENGTH));
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
    vector<Projectile*> temp1;
    for(int i = 0; i < userProjectiles.size(); i++){
        Vector2 center = userProjectiles[i]->getCenter();
        double radius = userProjectiles[i]->getRadius();
        if(center.y + radius < 0 || center.y - radius > SCREEN_HEIGHT || center.x + radius < 0 || center.x - radius > SCREEN_WIDTH){
            delete userProjectiles[i];
        }else{
            temp1.push_back(userProjectiles[i]);
        }
    }
    userProjectiles = temp1;

    vector<Projectile*> temp2;
    for(int i = 0; i < enemyProjectiles.size(); i++){
        Vector2 center = enemyProjectiles[i]->getCenter();
        double radius = enemyProjectiles[i]->getRadius();
        if(center.y + radius < 0 || center.y - radius > SCREEN_HEIGHT || center.x + radius < 0 || center.x - radius > SCREEN_WIDTH){
            delete enemyProjectiles[i];
            enemyProjectiles[i] = nullptr;
        }else{
            temp2.push_back(enemyProjectiles[i]);
        }
    }
    enemyProjectiles = temp2;
}

void Game::updateProjectiles(){
    for(int i = 0; i < enemyProjectiles.size(); i++){
        enemyProjectiles[i]->move();
    }
    for(int i = 0; i < userProjectiles.size(); i++){
        userProjectiles[i]->move();
    }
}

void Game::updateGame(){
    updateObstacles();
    updateProjectiles();
    updateEnemies();
    spawnEntities();
    checkObstacleUserCollision();
    checkUserProjectilesCollision();
    checkEnemyProjectilesCollision();
    despawnObstacles();
    despawnEnemies();
    despawnProjectiles();
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
                userProjectiles[j]->setPosition(-30, -30);
            }
        }
    }
}

void Game::checkEnemyProjectilesCollision(){
    Rectangle userHitbox = user.getHitbox();
    for(int i = 0; i < enemyProjectiles.size(); i++){
        if(CheckCollisionCircleRec(enemyProjectiles[i]->getCenter(), enemyProjectiles[i]->getRadius(), userHitbox)){
            user.takeDamage(enemyProjectiles[i]->getDamage());
            enemyProjectiles[i]->setPosition(-30, -30);
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

void Game::displaygameover(){
    score = 500;
    DrawText("Game Over", 380, 200, 40, YELLOW);
    string scored = "Score: "+std::to_string(score);
    string Hscore = "High Score: "+std::to_string(Highscore);
    DrawText( scored.c_str(), 380, 250, 20, BLUE);
    DrawText( Hscore.c_str(), 380, 283, 20, BLUE);
    fstream Scores("Scores.dat",ios::binary|ios::out);
    if(!Scores){
        cout<<"Error opening Score file"<<endl;
    }
    else{
        if(score >Highscore){
            Scores.write(reinterpret_cast<char*>(&score),sizeof(score));
            Highscore = score;
        }
    }

    Scores.close();
}



void Game::displayscores() {
    ifstream Scores("Scores.dat", ios::binary | ios::in);
    if (!Scores) {
        cout << "Error opening Score file" << endl;
        Highscore = 0;
    } else {
        if (Scores.read(reinterpret_cast<char*>(&Highscore), sizeof(Highscore))) {
           
        } else {
            Highscore = 0; 
        }
        Scores.close();
    }

    string scoreText = "HIGH SCORE: " + std::to_string(Highscore);
    DrawText(scoreText.c_str(), 380, 200, 40, YELLOW);
}
