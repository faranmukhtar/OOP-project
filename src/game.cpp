#include "game.h"

Game::Game(){
    user = new User();
}

void Game::init(){
    //initializing all non const variables
    score = 0;
    obstacleTimer = 0;
    gunnerTimer = 0;
    bomberTimer = 0;
    scoreTimer = 0;

    //deleting all enemies, projectiles, obstacles
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

    //Done to completely reinitialize user
    delete user;
    user = new User();
}

void Game::loadSounds(){
    //loading all sounds from files
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
    //unloading all sounds
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

void Game::loadAssets(){
    //loading font
    fontAnonymous = LoadFont("Fonts/Anonymous_Pro.ttf");

    //loading all the textures from the files and initializing texture related variables
    for(int i = 0; i < 2; i++){

        startScreenTexture[i] = LoadTexture(("Textures/Misc_textures/start_screen" + to_string(i+1) + ".png").c_str());

        gameOverTexture[i] = LoadTexture(("Textures/Misc_textures/game_over" + to_string(i+1) + ".png").c_str());

        groundTextures[i] = LoadTexture(("Textures/Ground/" + to_string(i + 1) + ".png").c_str());

    }

    for(int i = 0; i < 5; i++){

        backgroundTextures[i] = LoadTexture(("Textures/Background/" + to_string(i+1) + ".png").c_str());

        backgroundScrollX[i] = 0;

    }

    projectileTextures[0] = LoadTexture("Textures/Bullets/User.png");
    projectileTextures[1] = LoadTexture("Textures/Bullets/Gunner.png");

    userTextures[0] = LoadTexture("Textures/User/DoubleJump.png");
    userTextures[1] = LoadTexture("Textures/User/Run.png");
    userTextures[2] = LoadTexture("Textures/User/Jump.png");
    userTextures[3] = LoadTexture("Textures/User/shield.png");
    userTextures[4] = LoadTexture("Textures/User/hand.png");

    flyerTexture[0] = LoadTexture("Textures/Flyer/Flyer.png");

    bomberTexture[0] = LoadTexture("Textures/Bomber/Walk2.png");

    gunnerTextures[0] = LoadTexture("Textures/Gunner/Forward.png");
    gunnerTextures[1] = LoadTexture("Textures/Gunner/Idle.png");

    obstacleTexture = LoadTexture("Textures/Misc_textures/obstacle.png");

    Instructions = LoadTexture("Textures/Misc_textures/Instructions.png");

    groundScrollX = 0;
}

void Game::unloadAssets(){
    //unload font
    UnloadFont(fontAnonymous);

    //unloading all the textures
    for(int i = 0; i < 5; i++){

        UnloadTexture(backgroundTextures[i]);

        UnloadTexture(userTextures[i]);

    }

    for(int i = 0; i < 2; i++){

        UnloadTexture(startScreenTexture[i]);

        UnloadTexture(gameOverTexture[i]);

        UnloadTexture(groundTextures[i]);

    }

    for(int i = 0; i < 2; i++){

        UnloadTexture(projectileTextures[i]);

        UnloadTexture(gunnerTextures[i]);
    }

    UnloadTexture(flyerTexture[0]);
    UnloadTexture(bomberTexture[0]);
    UnloadTexture(obstacleTexture);
    UnloadTexture(Instructions);
}

void Game::spawnEntities(){
    //adding frame time to each timer. Each timer represent time since last spawn
    obstacleTimer += GetFrameTime();
    gunnerTimer += GetFrameTime();
    bomberTimer += GetFrameTime();

    //Each interval represents minimum time for each spawn

    //gunner spawn logic
    if(gunnerTimer > gunnerInterval){
        gunnerTimer = 0;

        enemies.push_back(new Gunner(SCREEN_WIDTH + 200,        //Initial x position
             80 + (rand() % 100),                               //Initial y position. randomized position from 80 to 180
             SCREEN_WIDTH - 400 + rand() % 300,                 //X position to be moved to. randomized from SCREEN_WIDTH-400 to SCREEN_WIDTH-100
              50 + rand() % 150));                              //X position to be moved to. randomized from 50 to 200
    }

    if(bomberTimer > bomberInterval){
        bomberTimer = 0;
        int randInt = rand() % 3;                               //Represents how many bombers will spawn. 0 for 2, 1 for 3, 2 for 4
        //Each new bomber is seperated by a distance of 80
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
        // Spawns obstacles or flyers based on a fixed probability

        if(rand() % 4 == 0){
            enemies.push_back(new Flyer(SCREEN_WIDTH + 200, GROUND_Y - (rand() % 100) - 50));
        }
        
        else{
            spawnObstacles();
        }

        obstacleTimer = 0;
    }
}

void Game::despawnEnemies(){
    vector<Enemy*> temp;            //Temporary array to store alive enemies

    for(int i = 0; i < enemies.size(); i++){
        Rectangle hitbox = enemies[i]->getHitbox();
        
        //if enemies are dead or out of bounds, deletes them
        if(!enemies[i]->isAlive() || hitbox.y + hitbox.height < 0 || hitbox.x + hitbox.width < 0){
            if(!enemies[i]->isAlive()) PlaySound(enemyDeathSound);
            delete enemies[i];
            enemies[i] = nullptr;
        }
        //otherwise save them in the temp array
        else{
            temp.push_back(enemies[i]);
        }
    }

    //All alive enemies kept
    enemies = temp;
}

void Game::updateEnemies(){

    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->move();                     //Allows all enemies to move
        Projectile* temp = nullptr;             //A temporary projectile that might be launched from an enemy

        //Check for each enemy type and performs attacks accordingly

        if(enemies[i]->getType() == "bomber"){
            temp = enemies[i]->useWeapon(0, 0, bomberShootSound);
        }

        if(enemies[i]->getType() == "flyer"){
            //checks if flyer collides with user. User may take damage if he is not blocking and the flyer takes a fixed amount of damage upon collision
            if(CheckCollisionRecs(enemies[i]->getHitbox(), user->getHitbox())){
                if(!user->isCurrentlyBlocking())
                user->takeDamage(enemies[i]->getDamage());
                enemies[i]->takeDamage(1000);
            }
        }

        if(enemies[i]->getType() == "gunner"){
            //targets users hitbox
            Rectangle hitbox = user->getHitbox();
            temp = enemies[i]->useWeapon(hitbox.x, hitbox.y, gunnerShootSound);
        }

        //if a projectile is returned from the attack, it is added to an array
        if(temp != nullptr) enemyProjectiles.push_back(temp);
    }
}



void Game::spawnObstacles(){
    //Randomly chooses an obstacle pattern from seven different options and spawns them
    int obstaclesNumber = rand() % 7;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(OBSTACLE_PATTERN[obstaclesNumber][i][j] == "X"){
                //The logic for this is similar to pointers in array logic
                obstacles.push_back(new Obstacle(SCREEN_WIDTH + GROUND_Y + j * OBSTACLE_LENGTH, GROUND_Y + (i - 3) * OBSTACLE_LENGTH));
            }
        }
    }
    
}

void Game::despawnObstacles(){
    vector<Obstacle*> temp;                         //Temporary array to store in bound obstacles

    for(int i = 0; i < obstacles.size(); i++){
        Rectangle hitbox = obstacles[i]->getHitbox();
        
        //if obstacles are out of bounds, deletes them
        if(hitbox.x + hitbox.width < 0){
            delete obstacles[i];
            obstacles[i] = nullptr;
        }
        
        //otherwise add them to an array
        else{
            temp.push_back(obstacles[i]);
        }
    }

    //keeps all the in bound obstacles
    obstacles = temp;
}

void Game::updateObstacles(){
    //moves obstacles by a fixed amount
    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->move(-OBSTACLE_SPEED, 0);
    }

}

void Game::despawnProjectiles(){
    vector<Projectile*> temp1;          //Temporary array to store in bound user projectiles

    for(int i = 0; i < userProjectiles.size(); i++){
        Vector2 center = userProjectiles[i]->getCenter();
        float radius = userProjectiles[i]->getRadius();

        //if out of bounds deletes them
        if(center.y + radius < 0 || center.y - radius > SCREEN_HEIGHT || center.x + radius < 0 || center.x - radius > SCREEN_WIDTH){
            delete userProjectiles[i];
            userProjectiles[i] = nullptr;
        }
        
        //otherwise saves them in an array
        else{
            temp1.push_back(userProjectiles[i]);
        }

    }

    //keeps all the in bounds projectiles
    userProjectiles = temp1;

    //Same logic for enemy projectiles
    vector<Projectile*> temp2;      

    for(int i = 0; i < enemyProjectiles.size(); i++){
        Vector2 center = enemyProjectiles[i]->getCenter();
        float radius = enemyProjectiles[i]->getRadius();

        if(center.y + radius < 0 || center.y - radius > SCREEN_HEIGHT || center.x + radius < 0 || center.x - radius > SCREEN_WIDTH){
            delete enemyProjectiles[i];
            enemyProjectiles[i] = nullptr;
        }
        
        else{
            temp2.push_back(enemyProjectiles[i]);
        }

    }

    enemyProjectiles = temp2;

}

void Game::updateProjectiles(){
    //Allows projectiles to move
    for(int i = 0; i < enemyProjectiles.size(); i++){
        enemyProjectiles[i]->move();
    }

    for(int i = 0; i < userProjectiles.size(); i++){
        userProjectiles[i]->move();
    }

}

void Game::updateScore(){
    //updates scores every second
    scoreTimer += GetFrameTime();

    if(scoreTimer >= 1.0){ 
        score += baseScoreRate;
        scoreTimer = 0;
    }

}

void Game::addKillScore(const string& enemyType){
    //adds a fixed kill score to current score for each enemy type
    if(enemyType == "bomber") {score += bomberKillBonus;}
    else if(enemyType == "gunner"){score += gunnerKillBonus;}
    else if (enemyType == "flyer"){score += flyerKillBonus;}

}

void Game::updateGame(){
    //updates entities
    updateScore();
    updateObstacles();
    updateProjectiles();
    updateEnemies();
    UpdateMusicStream(bgMusic);

    //spawns new entities
    spawnEntities();

    //checks for collisions
    checkObstacleUserCollision();
    checkUserProjectilesCollision();
    checkEnemyProjectilesCollision();
    checkUserOutOfBounds();

    //despawns enemies
    despawnObstacles();
    despawnEnemies();
    despawnProjectiles();
}

bool Game::checkGameOver(){
    //checks if game is over
    if(!user->isAlive()) {
        PlaySound(userDeathSound);

        return true;
    }

    return false;
}


void Game::takeInput(){
    // 'D' to move user forward while keeping user in bounds
    if (IsKeyDown(KEY_D) && user->getHitbox().x < SCREEN_WIDTH - user->getHitbox().width){ 
        user->move(PLAYER_SPEED, 0);
    }

    // 'A' to move user backward while keeping user in bounds
    if (IsKeyDown(KEY_A)&&user->getHitbox().x > 0){
        user->move(-PLAYER_SPEED, 0);
    }

    // 'Space' to jump
    if(IsKeyPressed(KEY_SPACE)){
        user->jump(userJumpSound);
    }

    // 'LMB' to shoot but only when user is not currently blocking
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !user->isCurrentlyBlocking()){
        //spawns projectiles in direction of mouse position
        Projectile* temp = user->useWeapon(GetMouseX(), GetMouseY(), userShootSound);
        if(temp != nullptr) userProjectiles.push_back(temp);
    }

    //updates jumping logic for user
    user->updatejump(userJumpSound);

    //'RMB' for user block
    if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && user->getBlockEnergy() > 0){
        user->setBlocking(true);
    } 

    else{
        user->setBlocking(false);
    }
    
    // updating blocking energy after each frame
    user->updateBlockEnergy();
}

void Game::checkUserProjectilesCollision(){
    //checks for collision between Enemy and user projectiles
    for(int i = 0; i < enemies.size(); i++){
        Rectangle enemyHitbox = enemies[i]->getHitbox();

        for(int j = 0; j < userProjectiles.size(); j++){
            if(CheckCollisionCircleRec(userProjectiles[j]->getCenter(), userProjectiles[j]->getRadius(), enemyHitbox)){
                enemies[i]->takeDamage(userProjectiles[j]->getDamage());
                userProjectiles[j]->setPosition(-30, -30);                  //Projectile moved out of bounds to allow it to despawn

                if(!enemies[i]->isAlive()) {
                    addKillScore(enemies[i]->getType());                    //Kill score added according to each type
                }

            }
        }

    }

}

void Game::checkEnemyProjectilesCollision(){
    //checks for collision between User and enemy projectiles
    Rectangle userHitbox = user->getHitbox();

    for(int i = 0; i < enemyProjectiles.size(); i++){

        if(CheckCollisionCircleRec(enemyProjectiles[i]->getCenter(), enemyProjectiles[i]->getRadius(), userHitbox)){

            // Plays bomber sound upon hit if the projectile is of bomber
            if(enemyProjectiles[i]->getRadius() == BOMBER_PROJECTILE_RADIUS){
                PlaySound(bombExplosionSound);
            }
            
            //user takes damage if he is not blocking
            if(!user->isCurrentlyBlocking()){
                user->takeDamage(enemyProjectiles[i]->getDamage());
                PlaySound(userHitSound);
            }
            enemyProjectiles[i]->setPosition(-30, -30);         //Moves projectile out of bound to allow it to despawn

        }

    }
}

void Game::checkObstacleUserCollision(){
    //checks for collision with obstacles for users and update the user to outside the obstacle
    Rectangle userHitbox = user->getHitbox();
    bool obstacleY = false;

    for(int i = 0; i < obstacles.size(); i++){
        Rectangle obHitbox = obstacles[i]->getHitbox();
        
        if((userHitbox.x + userHitbox.width >= obHitbox.x &&
            userHitbox.x < obHitbox.x) &&
           (userHitbox.y + userHitbox.height > obHitbox.y &&
            userHitbox.y < obHitbox.y + obHitbox.height) &&
            (userHitbox.y + userHitbox.height) - obHitbox.y > 10 ){  // slight room for error

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
    
    //Sets the onObstacle attribute in user
    user->setOnObstacle(obstacleY);
}

void Game::checkUserOutOfBounds(){
    //User takes damage if out of bounds
    if(user->getHitbox().x + user->getHitbox().width < 0){
        user->takeDamage(outOfBoundsDamage);
    }

}


void Game::drawGround() {
    //defines different textures for the top and every layer below it
    Texture2D topTexture = groundTextures[0];
    Texture2D fillTexture = groundTextures[1];
    
    //Custom scaling for size of tiles
    const float tileScale = 1.5;  
    const int tileWidth = topTexture.width * tileScale;
    const int tileHeight = topTexture.height * tileScale;

    //Number of layers
    const int groundHeight = 3;            
    
    //Calculating total amount of tiles to be rendered horizontally at a time
    int numHorizontalTiles = (int)ceil(GetScreenWidth() / (float)tileWidth) + 1;
    
    //Distance scrolled for each frame
    groundScrollX -= groundScrollSpeed * GetFrameTime();
    //Distance that has to be transformed
    groundScrollX = fmod(groundScrollX, tileWidth);
    
    //loop for every layer
    for (int yLayer = 0; yLayer < groundHeight; yLayer++) {
        Texture2D currentTexture = (yLayer == 0) ? topTexture : fillTexture;
        
        //Getting y position of current tile
        float yPos = GROUND_Y + yLayer * tileHeight;
        
        for (int xTile = 0; xTile < numHorizontalTiles; xTile++) {
            //Getting x position for each tile in the row
            float xPos = groundScrollX + xTile * tileWidth;
            
            //check if x position is of texture is inbounds and loads them if it is
            if (xPos + tileWidth > 0 && xPos < GetScreenWidth()) {
                //defines the position, width and height of each tile
                Rectangle destRec = {xPos, yPos, (float)tileWidth, (float)tileHeight};

                //defines the position to start, width and height of texture in file
                Rectangle sourceRec = {0, 0, (float)currentTexture.width, (float)currentTexture.height};

                //draws the texture
                DrawTexturePro(currentTexture, sourceRec, destRec, {0,0}, 0.0f, WHITE);
            }

        }

    }

}

void Game::drawBackground(){
    //loop for each background layer
    for (int i = 0; i < 5; i++) {
        //Distance scrolled for each frame
        backgroundScrollX[i] -= backgroundScrollSpeed[i] * GetFrameTime();
        //Distance that has to be transformed
        backgroundScrollX[i] = fmod(backgroundScrollX[i], backgroundTextures[i].width);

        //Scaling width according to a fixed height to GROUND_Y
        float scale = GROUND_Y / backgroundTextures[i].height;
        int scaledWidth = backgroundTextures[i].width * scale;
        
        //Getting number of repeating textures that have to be loaded for each layer
        int numTextures = (int)ceil(GetScreenWidth() / (float)scaledWidth) + 1;

        for (int n = 0; n < numTextures; n++) {
            //Defining X position for each layer. Each scroll x is scaled first
            float xPos = backgroundScrollX[i] * scale + (n * scaledWidth);
            
            //loads texture if it is inbound
            if (xPos + scaledWidth > 0 && xPos < GetScreenWidth()) {
                //defines the position to start, width and height of texture in file
                Rectangle sourceRec = {0, 0, (float)backgroundTextures[i].width, (float)backgroundTextures[i].height};

                //defines the position, width and height of each texture
                Rectangle destRec = {xPos, 0, (float)scaledWidth, (float)GROUND_Y};
                DrawTexturePro(backgroundTextures[i], sourceRec, destRec, {0,0}, 0.0f, WHITE);
            }

        }

    }

}

void Game::drawScreen(){
    //draws backgorund, ground, user, obtacle, projectile and enemy
    drawBackground();
    drawGround();
    user->draw(userTextures);

    for(int i = 0; i < obstacles.size(); i++){
        obstacles[i]->draw(obstacleTexture);
    }

    for(int i = 0; i < userProjectiles.size(); i++){
        userProjectiles[i]->draw(projectileTextures[0]);
    }

    for(int i = 0; i < enemyProjectiles.size(); i++){
        enemyProjectiles[i]->draw(projectileTextures[1]);
    }

    for(int i = 0; i < enemies.size(); i++){
        if(enemies[i]->getType() == "flyer"){
            enemies[i]->draw(flyerTexture);
        }else if(enemies[i]->getType() == "bomber"){
            enemies[i]->draw(bomberTexture);
        }else{
            enemies[i]->draw(gunnerTextures);
        }
    }

    //Drawing score text
    string scoreText = to_string(score);

    //adjusting score to 5 digits
    while(scoreText.size() < 5)
    scoreText.insert(0, 1, '0');

    DrawText(scoreText.c_str(), SCREEN_WIDTH - 180, 40, 40, WHITE);


    //Drawing block bar
    float energyPercent = user->getBlockEnergy()/100.0f;
    DrawRectangle(20, 50, 200, 15, GRAY);
    DrawRectangle(20, 50, 200 * energyPercent, 15, BLUE);

    //Drawing health bar
    float healthPercent = user->getHealth()/100.0f;
    DrawRectangle(20, 35, 200, 15, GRAY);
    DrawRectangle(20, 35, 200 * healthPercent, 15, GREEN);
}

bool Game::drawLogo(){
    bool keyPressed = false;
    float timer = 0;

    //loops and draws logo until enter is pressed or window is closed
    while(!WindowShouldClose() && !keyPressed){
        BeginDrawing();

        timer += GetFrameTime();

        //animation every second
        if(fmod(timer, 2.0) < 1.0){
            DrawTexture(startScreenTexture[0], 0, 0, WHITE);
        }
        
        else{
            DrawTexture(startScreenTexture[1], 0, 0, WHITE);
        }

        keyPressed = IsKeyPressed(KEY_ENTER);

        EndDrawing();
    }

    //returning if window should close or not
    if(WindowShouldClose()){
        return true;
    }

    return false;

}

bool Game::drawGameOver(){
    bool keyPressed = false;
    saveHighScore();
    float timer = 0;

    //loops and draws game over until enter is pressed or window is closed
    while(!keyPressed && !WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);

        keyPressed = IsKeyPressed(KEY_ENTER);

        timer += GetFrameTime();

        //animation every second
        if(fmod(timer, 2.0) < 1.0){
            DrawTexture(gameOverTexture[0], 0, 0, WHITE);
        }
        
        else{
            DrawTexture(gameOverTexture[1], 0, 0, WHITE);
        }

        //Drawing score and high score
        string scores = "Score:           " + to_string(score) + "\nHigh Score:      " + to_string(Highscore);

        //Center string
        Vector2 textSize = MeasureTextEx(fontAnonymous, scores.c_str(), 34, 3);
        int x = (SCREEN_WIDTH - textSize.x) / 2;

        //Draw text
        DrawTextEx(fontAnonymous, scores.c_str(), { (float)x, 350 }, 34, 3, WHITE);

        EndDrawing();
    }

    //returning if window should close or not

    if(WindowShouldClose()){
        return true;
    }

    init();
    return false;
}


bool Game::drawControls() {
    bool keyPressed = false;

    //loops and draws game over until enter is pressed or window is closed
    while (!WindowShouldClose() && !keyPressed) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(Instructions, 0, 0, WHITE);

        keyPressed = IsKeyPressed(KEY_ENTER);

        EndDrawing();
    }

    //returning if window should close or not
    
    if(WindowShouldClose()){
        return true;
    }

    return false;

}



void Game::saveHighScore(){
    //Saving high score to file
    try{
        if(score > Highscore){
            fstream Scores("Scores.dat",ios::binary|ios::out | ios::trunc);

            if(!Scores){
                throw FileException();
            }
                
            Scores.write(reinterpret_cast<char*>(&score),sizeof(score));
            Highscore = score;
            Scores.close();

        }
    }
    catch(FileException &ex){
        cerr<<ex.what()<<endl;
    }
    
}

void Game::loadHighScore() {
    //Saving high score from file
    try{
        ifstream Scores("Scores.dat", ios::binary | ios::in);

        if (!Scores) {
            Highscore = 0;
            throw FileException();

        } 
        
        else {

            if (Scores.read(reinterpret_cast<char*>(&Highscore), sizeof(Highscore))) {
            } 
            
            else {
                Highscore = 0; 
            }

            Scores.close();
            
        }
    }
    catch(FileException &ex){
        cerr<<ex.what()<<endl;
    }
}

Game::~Game(){
    //freeing dynamic memory
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
