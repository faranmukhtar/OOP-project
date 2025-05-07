#include "game.h"

Game::Game(){
    user = new User();
}

void Game::init(){
    score = 0;
    obstacleTimer = 0;
    gunnerTimer = 0;
    bomberTimer = 0;
    scoreTimer = 0;

    for(int i = 0; i < enemies.size(); i++){
        delete enemies[i];
    }
    enemies.clear();

    for(int i = 0; i < userProjectiles.size(); i++){
        delete userProjectiles[i];
    }
    userProjectiles.clear();

    for(int i = 0; i < obstacles.size(); i++){
        delete obstacles[i];
    }
    obstacles.clear();

    for(int i = 0; i < enemyProjectiles.size(); i++){
        delete enemyProjectiles[i];
    }
    enemyProjectiles.clear();

    delete user;
    user = new User();
}

void Game::loadSounds(){
    gunnerSpawnSound = LoadSound("sounds/gunner-spawn.mp3");
    SetSoundVolume(gunnerSpawnSound, 0.6f);
    bomberSpawnSound = LoadSound("sounds/bomber-spawn.mp3");
    SetSoundVolume(bomberSpawnSound, 0.5f);
    bombExplosionSound = LoadSound("sounds/bomb-explosion.wav");
    SetSoundVolume(bombExplosionSound, 0.7f);
    flyerSound = LoadSound("sounds/flyer-spawn.wav");
    SetSoundVolume(flyerSound, 1.0f);
    userHitSound = LoadSound("sounds/user-damage.wav");
    SetSoundVolume(userHitSound, 0.6f);
    userDeathSound = LoadSound("sounds/user-dying.mp3");
    SetSoundVolume(userDeathSound, 0.5f);
    enemyDeathSound = LoadSound("sounds/enemy-death.mp3");
    SetSoundVolume(enemyDeathSound, 0.2f);
    bgMusic = LoadMusicStream("sounds/background-music.mp3");
    gunnerShootSound = LoadSound("sounds/gunner-shoot.wav");
    SetSoundVolume(gunnerShootSound, 0.35f);
    bomberShootSound = LoadSound("sounds/bomber-shoot.mp3");
    SetSoundVolume(bomberShootSound, 1.0f);
    userShootSound = LoadSound("sounds/user-shoot.wav");
    SetSoundVolume(userShootSound, 0.33f);
    userJumpSound = LoadSound("sounds/user-jump.wav");
    SetSoundVolume(userJumpSound, 0.9f);
    PlayMusicStream(bgMusic);
    SetMusicVolume(bgMusic, 0.5f);
}

void Game::unloadSounds(){
    UnloadSound(gunnerSpawnSound);
    UnloadSound(bomberSpawnSound);
    UnloadSound(bombExplosionSound);
    UnloadSound(flyerSound);
    UnloadSound(userHitSound);
    UnloadSound(userDeathSound);
    UnloadSound(enemyDeathSound);
    UnloadMusicStream(bgMusic);
    UnloadSound(gunnerShootSound);
    UnloadSound(bomberShootSound);
    UnloadSound(userShootSound);
    UnloadSound(userJumpSound);
}

void Game::spawnEntities(){
    obstacleTimer += GetFrameTime();
    gunnerTimer += GetFrameTime();
    bomberTimer += GetFrameTime();

    if(gunnerTimer > gunnerInterval){
        gunnerTimer = 0;
        enemies.push_back(new Gunner(SCREEN_WIDTH + 200, 80 + (rand() % 100), SCREEN_WIDTH - 400 + rand() % 300, 50 + rand() % 150));
        PlaySound(gunnerSpawnSound); 
    }

    if(bomberTimer > bomberInterval){
        bomberTimer = 0;
        int randInt = rand() % 3;
        enemies.push_back(new Bomber(SCREEN_WIDTH + 80, 80));
        PlaySound(bomberSpawnSound);
        enemies.push_back(new Bomber(SCREEN_WIDTH + 160, 80));
        PlaySound(bomberSpawnSound);
        if(randInt >= 1){
            enemies.push_back(new Bomber(SCREEN_WIDTH + 240, 80));
            PlaySound(bomberSpawnSound);
        }
        if(randInt == 2){
            enemies.push_back(new Bomber(SCREEN_WIDTH + 320, 80));
            PlaySound(bomberSpawnSound);
        }
    }

    if(obstacleTimer > obstacleInterval){
        if(rand() % 4 == 0){
            PlaySound(flyerSound);
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
            if(!enemies[i]->isAlive()) PlaySound(enemyDeathSound);
            delete enemies[i];
            enemies[i] = nullptr;
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
            temp = enemies[i]->useWeapon(0, 0, bomberShootSound);
        }
        if(enemies[i]->getType() == "flyer"){
            if(CheckCollisionRecs(enemies[i]->getHitbox(), user->getHitbox())){
                if(!user->isCurrentlyBlocking())
                user->takeDamage(enemies[i]->getDamage());
                enemies[i]->takeDamage(1000);
            }
        }
        if(enemies[i]->getType() == "gunner"){
            Rectangle hitbox = user->getHitbox();
            temp = enemies[i]->useWeapon(hitbox.x, hitbox.y, gunnerShootSound);
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
            obstacles[i] = nullptr;
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
            userProjectiles[i] = nullptr;
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

void Game::updateScore(){
    scoreTimer += GetFrameTime();
    if(scoreTimer >= 1.0){ 
        score += baseScoreRate;
        scoreTimer = 0;
    }
}

void Game::addKillScore(const string& enemyType){
    if(enemyType == "bomber") {score += bomberKillBonus;}
    else if(enemyType == "gunner"){score += gunnerKillBonus;}
    else if (enemyType == "flyer"){score += flyerKillBonus;}
}

void Game::updateGame(){
    updateScore();
    updateObstacles();
    updateProjectiles();
    updateEnemies();
    UpdateMusicStream(bgMusic);
    spawnEntities();
    checkObstacleUserCollision();
    checkUserProjectilesCollision();
    checkEnemyProjectilesCollision();
    checkUserOutOfBounds();

    despawnObstacles();
    despawnEnemies();
    despawnProjectiles();
}

bool Game::loopGameOver(){
    bool keyPressed = false;
    displayGameOver();
    while(!keyPressed && !WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);

        keyPressed = IsKeyPressed(KEY_ENTER);
        drawGameOver();

        EndDrawing();
    }
    if(WindowShouldClose()){
        return true;
    }
    init();
    return false;
}

bool Game::checkGameOver(){
    if(!user->isAlive()) {
        PlaySound(userDeathSound);
        return true;
    }
    return false;
}

void Game::drawBackground(){
    DrawLine(0, GROUND_Y, GetScreenWidth(), GROUND_Y, WHITE);
}

void Game::drawScreen(){
    drawBackground();
    user->draw();
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
    DrawText(TextFormat("SCORE: %d", (int)score), SCREEN_WIDTH - 200, 20, 30, WHITE);

    float energyPercent = user->getBlockEnergy()/100.0f;
    DrawRectangle(20, 50, 200, 15, GRAY);
    DrawRectangle(20, 50, 200 * energyPercent, 15, BLUE);

    float healthPercent = user->getHealth()/100.0f;
    DrawRectangle(20, 35, 200, 15, GRAY);
    DrawRectangle(20, 35, 200 * healthPercent, 15, GREEN);
}

bool Game::drawLogo(){
    bool keyPressed = false;
    while(!WindowShouldClose() && !keyPressed){
        BeginDrawing();

        DrawText("Shadow Sprint", 330, 200, 50, YELLOW);
        DrawText("Press Enter to play", 380, 250, 20, WHITE);

        keyPressed = IsKeyPressed(KEY_ENTER);

        EndDrawing();
    }
    if(WindowShouldClose()){
        return true;
    }
    return false;
}

void Game::takeInput(){
    if (IsKeyDown(KEY_D) && user->getHitbox().x < SCREEN_WIDTH - user->getHitbox().width){ 
        user->move(PLAYER_SPEED, 0);
    }
    if (IsKeyDown(KEY_A)&&user->getHitbox().x > 0){
        user->move(-PLAYER_SPEED, 0);
    }
    if(IsKeyPressed(KEY_SPACE)){
        user->jump(userJumpSound);
    }

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !user->isCurrentlyBlocking()){
        Projectile* temp = user->useWeapon(GetMouseX(), GetMouseY(), userShootSound);
        if(temp != nullptr) userProjectiles.push_back(temp);
    }
    user->updatejump(userJumpSound);

    if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && user->getBlockEnergy() > 0){
        user->setBlocking(true);
    } 
    else{
        user->setBlocking(false);
    }
    
    user->updateBlockEnergy();
}

void Game::checkUserProjectilesCollision(){
    for(int i = 0; i < enemies.size(); i++){
        Rectangle enemyHitbox = enemies[i]->getHitbox();
        for(int j = 0; j < userProjectiles.size(); j++){
            if(CheckCollisionCircleRec(userProjectiles[j]->getCenter(), userProjectiles[j]->getRadius(), enemyHitbox)){
                enemies[i]->takeDamage(userProjectiles[j]->getDamage());
                userProjectiles[j]->setPosition(-30, -30);
                if(!enemies[i]->isAlive()) {
                    addKillScore(enemies[i]->getType());
                }
            }
        }
    }
}

void Game::checkEnemyProjectilesCollision(){
    Rectangle userHitbox = user->getHitbox();
    for(int i = 0; i < enemyProjectiles.size(); i++){
        if(CheckCollisionCircleRec(enemyProjectiles[i]->getCenter(), enemyProjectiles[i]->getRadius(), userHitbox)){
            if(enemyProjectiles[i]->getRadius() == BOMBER_PROJECTILE_RADIUS){
                PlaySound(bombExplosionSound);
            }
            if(!user->isCurrentlyBlocking()){
                user->takeDamage(enemyProjectiles[i]->getDamage());
                PlaySound(userHitSound);
            }
            enemyProjectiles[i]->setPosition(-30, -30);
        }
    }
}

void Game::checkObstacleUserCollision(){
    Rectangle userHitbox = user->getHitbox();
    bool obstacleY = false;
    for(int i = 0; i < obstacles.size(); i++){
        Rectangle obHitbox = obstacles[i]->getHitbox();
        
        if((userHitbox.x + userHitbox.width >= obHitbox.x &&
            userHitbox.x < obHitbox.x) &&
           (userHitbox.y + userHitbox.height > obHitbox.y &&
            userHitbox.y < obHitbox.y + obHitbox.height) &&
            (userHitbox.y + userHitbox.height) - obHitbox.y > 10){

            user->setPosition(obHitbox.x - userHitbox.width, userHitbox.y);
            userHitbox = user->getHitbox();

        }

        if((userHitbox.y + userHitbox.height >= obHitbox.y &&
            userHitbox.y < obHitbox.y) &&
           (userHitbox.x + userHitbox.width > obHitbox.x &&
            userHitbox.x < obHitbox.x + obHitbox.width)){

            user->setPosition(userHitbox.x, obHitbox.y - userHitbox.height);
            obstacleY = true;

        }
    }
    
    user->setOnObstacle(obstacleY);
}

void Game::checkUserOutOfBounds(){
    if(user->getHitbox().x + user->getHitbox().width < 0){
        user->takeDamage(outOfBoundsDamage);
    }
}

void Game::displayGameOver(){
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

void Game::drawGameOver(){
    DrawText("Game Over", 380, 200, 40, YELLOW);
    string scored = "Score: "+std::to_string(score);
    string Hscore = "High Score: "+std::to_string(Highscore);
    DrawText( scored.c_str(), 380, 250, 20, BLUE);
    DrawText( Hscore.c_str(), 380, 283, 20, BLUE);

    DrawText("Press Enter to play again", 380, 500, 20, WHITE);
}



void Game::displayScores() {
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

    string scoreText = "HIGH SCORE: " + to_string(Highscore);
    DrawText(scoreText.c_str(), 380, 200, 40, YELLOW);
}

Game::~Game(){
    for(int i = 0; i < enemies.size(); i++){
        delete enemies[i];
    }

    for(int i = 0; i < userProjectiles.size(); i++){
        delete userProjectiles[i];
    }

    for(int i = 0; i < obstacles.size(); i++){
        delete obstacles[i];
    }

    for(int i = 0; i < enemyProjectiles.size(); i++){
        delete enemyProjectiles[i];
    }

    delete user;
}
