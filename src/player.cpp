#include "player.h"


Player::Player(float x, float y, float width, float height, float health, float damage){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
    this->damage = damage;
    this->frameCount = 0;
    this->currentFrame = 0;
    this->isDamaged = false;
    this->damageFrames = 0;
};

void Player::takeDamage(float val){
    health -= val;
    isDamaged = true;
}

void Player::setPosition(float x, float y){
    hitbox.x = x;
    hitbox.y = y;
}

bool Player::isAlive(){
    return health > 0;
}

float Player::getDamage(){
    return damage;
}

float Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

Enemy::Enemy(float x, float y, float width, float height, float health, float damage, string type) : Player(x, y, width, height, health, damage){
    this->type = type;
}

string Enemy::getType(){
    return type;
}

Bomber::Bomber(float x, float y) : Enemy(x, y, BOMBER_WIDTH, BOMBER_HEIGHT, BOMBER_HEALTH, BOMBER_PROJECTILE_DAMAGE, "bomber"), hasDroppedBomb(false){
    //randomly target one of 10 locations
    targetX = ((rand() % 10) + 0.5) * SCREEN_WIDTH / 10;
}

void Bomber::move(){
    //moves in x direction if no bomb dropped otherwise in y direction
    if (!hasDroppedBomb){
        hitbox.x -= BOMBER_SPEED;
    }
    else{
        hitbox.y -= BOMBER_SPEED;
    }
}

Projectile* Bomber::useWeapon(float, float, Sound s){
    //Releases a bomb only when target is reached otherwise returns nullptr
    if(hasDroppedBomb) return nullptr;
    if(hitbox.x - targetX < 0){ 
        hasDroppedBomb = true;
        PlaySound(s);
        return new Projectile(0, BOMBER_PROJECTILE_SPEEDY, hitbox.x + hitbox.width / 2, hitbox.y, BOMBER_PROJECTILE_RADIUS, damage);
    }
    return nullptr;
}

void Bomber::draw(Texture2D characterTextures[]){
    //total sprites in animation
    int totalFrames = 4;

    //Makes sure that the sprite changes evey 8 frames
    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    //Gets dimensions of a single sprite from the sprite sheet
    int frameWidth = characterTextures[0].width / totalFrames;
    int frameHeight = characterTextures[0].height;

    //dimensions of single sprite
    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    //dimensions of bomber location
    Rectangle dest = {
        hitbox.x + 20,
        hitbox.y + 20,
        frameWidth * 2,
        frameHeight * 2
    };

    //Setting the center from where the texture would be rotated or scaled. it is the middle of the texture
    Vector2 origin = {
        frameWidth,
        frameHeight
    };

    //If damaged, tint the texture red for 9 frames
    if(isDamaged){
        DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, RED);
        damageFrames++;
        if(damageFrames > 10){
            isDamaged = false;
            damageFrames = 0;
        }
    }else{
        DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, WHITE);
    }
}

Gunner::Gunner(float x, float y, float startX, float startY) : Enemy(x, y, GUNNER_WIDTH, GUNNER_HEIGHT, GUNNER_HEALTH, GUNNER_PROJECTILE_DAMAGE, "gunner"){
    shootTimer = 0;
    moveTimer = 0;
    startPosReached = false;
    startPos.x = startX;
    startPos.y = startY;
    shootTimer = ((rand() % 10) + 1) / 10.0 * GUNNER_SHOOT_INTERVAL;    //random value so that all guners have different shoot times
    currentTexture = 0;
}

void Gunner::move(){ 
    //this is done until the fixed start position is reached
    if(!startPosReached){
        //Calculations to go towards the startpos from its current position
        Vector2 direction = {float(startPos.x - hitbox.x),float(startPos.y - hitbox.y)};
        direction = Vector2Normalize(direction);
        speed = {direction.x * (float)GUNNER_SPEED, direction.y * (float)GUNNER_SPEED};
        hitbox.x += speed.x;
        hitbox.y += speed.y;

        //if the start position is reached, randomly decide the direction it should travel and calculate speed accordingly
        if(hitbox.x <= startPos.x && (hitbox.y <= startPos.y + 10 && hitbox.y >= startPos.y - 10)){
            startPosReached = true;
            direction.x = rand() % 2 == 0 ? 1 : -1;
            direction.y = rand() % 2 == 0 ? 1 : -1;
            direction = Vector2Normalize(direction);
            speed = {direction.x * (float)GUNNER_SPEED, direction.y * (float)GUNNER_SPEED};
        }
    }
    //After start position is reached
    else{
        //wait until a fixed time period to move
        moveTimer += GetFrameTime();  
        if (moveTimer >= GUNNER_MOVE_INTERVAL){
            //setting the current texture to moving texture
            currentTexture = 0;
            //fixed rectangle defined in which the gunner bounces around changing directions when hitting a boundary
            if(hitbox.x <= SCREEN_WIDTH - 600 || 
                hitbox.x + hitbox.width >= SCREEN_WIDTH - 50 ||
                hitbox.y + hitbox.height >= 300 ||
                hitbox.y <= 50){

                moveTimer = 0;
                if(hitbox.x <= SCREEN_WIDTH - 400 || hitbox.x + hitbox.width >= SCREEN_WIDTH - 50){
                    speed.x *= -1;
                }
                if(hitbox.y + hitbox.height >= 300 || hitbox.y <= 50){
                    speed.y *= -1;
                }
            }
            //Movement logic
            hitbox.x += speed.x;
            hitbox.y += speed.y;
        }else{
            //setting current texture to idle texture
            currentTexture = 1;
        }
    }
}

Projectile* Gunner::useWeapon(float userX, float userY, Sound s){  
    //waits until a fixed time to shoot
    shootTimer += GetFrameTime();
    if (shootTimer >= GUNNER_SHOOT_INTERVAL){
        //shoots towards user position provided in parameter
        shootTimer = 0;
        Vector2 direction = {float(userX - hitbox.x),float(userY - hitbox.y)};
        direction = Vector2Normalize(direction);
        PlaySound(s);
        return new Projectile(direction.x * GUNNER_PROJECTILE_SPEED_FACTOR, direction.y * GUNNER_PROJECTILE_SPEED_FACTOR, hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2, GUNNER_PROJECTILE_RADIUS, damage);
    }
    return nullptr;
}

void Gunner::draw(Texture2D characterTextures[]){
    //deciding total frames based on current sprite sheet
    int totalFrames;
    if(currentTexture == 1 || currentTexture == 0){
        totalFrames = 4;
    }

    //Makes sure that the sprite changes evey 8 frames
    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    //Gets dimensions of a single sprite from the sprite sheet
    int frameWidth = characterTextures[currentTexture].width / totalFrames;
    int frameHeight = characterTextures[currentTexture].height;

    //dimensions of single sprite
    Rectangle source = {
        (float)((currentFrame + 1) * frameWidth), //slightly different calculation for sheet being inverted
        0,
        -(float)frameWidth,               //negative because the sheet is inverted
        (float)frameHeight
    };

    //dimensions of gunner location
    Rectangle dest = {
        hitbox.x + 20,
        hitbox.y + 20,
        frameWidth * 2,
        frameHeight * 2
    };

    //Setting the center from where the texture would be rotated or scaled. it is the middle of the texture
    Vector2 origin = {
        frameWidth,
        frameHeight
    };

     //If damaged, tint the texture red for 9 frames
    if(isDamaged){
        DrawTexturePro(characterTextures[currentTexture], source, dest, origin, 0.0f, RED);
        damageFrames++;
        if(damageFrames > 10){
            isDamaged = false;
            damageFrames = 0;
        }
    }else{
        DrawTexturePro(characterTextures[currentTexture], source, dest, origin, 0.0f, WHITE);
    }
}

Flyer::Flyer(float x, float y) : Enemy(x, y, FLYER_WIDTH, FLYER_HEIGHT, FLYER_HEALTH, FLYER_DAMAGE, "flyer"){}

void Flyer::draw(Texture2D characterTextures[]){
    int totalFrames = 8;

    //Makes sure that the sprite changes evey 8 frames
    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    //Gets dimensions of a single sprite from the sprite sheet
    int frameWidth = characterTextures[0].width / totalFrames;
    int frameHeight = characterTextures[0].height;

    //dimensions of single sprite
    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    //dimensions of bomber location
    Rectangle dest = {
        hitbox.x + 20,
        hitbox.y + 20,
        frameWidth * 2,
        frameHeight * 2
    };

    //Setting the center from where the texture would be rotated or scaled. it is the middle of the texture
    Vector2 origin = {
        frameWidth,
        frameHeight
    };

    //If damaged, tint the texture red for 9 frames
    if(isDamaged){
        DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, RED);
        damageFrames++;
        if(damageFrames > 10){
            isDamaged = false;
            damageFrames = 0;
        }
    }else{
        DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, WHITE);
    }
}

void Flyer::move(){
    //move a fixed amount
    hitbox.x -= FLYER_SPEED;
}

Projectile* Flyer::useWeapon(float x, float y, Sound){
    //no projectile so only return nullptr
    return nullptr;
}

User::User() : Player(USER_X, GROUND_Y - USER_HEIGHT, USER_WIDTH, USER_HEIGHT, USER_HEALTH, USER_PROJECTILE_DAMAGE){
    jumpvelocity = 0;
    jumps = 2;
    onGround = true;
    onObstacle = false;
    shootTimer = 0;
    blockEnergy = 100.0f;
    currentTexture = 1;
    isBlocking = false; 
}

void User::move(float x, float y){ 
    hitbox.x = hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

Projectile* User::useWeapon(float mouseX, float mouseY, Sound s){
    //GetTime() is similar to GetFrameTime() but it gives you the total time since the program started
    //shoots after a fixed time
    if(GetTime() - shootTimer > USER_SHOOT_INTERVAL){
        //Shoots towards mouse position passed from parameters
        shootTimer = GetTime();
        PlaySound(s);
        Vector2 shootLocation = {hitbox.x + hitbox.width, hitbox.y + hitbox.height / 4.0};
        Vector2 direction = {float(mouseX - shootLocation.x),float(mouseY - shootLocation.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * USER_PROJECTILE_SPEED_FACTOR, direction.y * USER_PROJECTILE_SPEED_FACTOR, shootLocation.x, shootLocation.y, USER_PROJECTILE_RADIUS, damage);
    }
    return nullptr;
}

void User::setOnObstacle(bool val){
    onObstacle = val;
}

void User::draw(Texture2D characterTextures[]){
    //deciding total frames based on current sprite sheet
    int totalFrames;
    if(currentTexture <= 1){
        totalFrames = 6;
    }else if(currentTexture == 2){
        totalFrames = 4;
    }

    //Makes sure that the sprite changes evey 8 frames
    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1);
        //extra logic here to make sure jumping animations dont loop around
        if(currentTexture == 2 || currentFrame == 0){
            if(currentFrame > totalFrames - 1)
            currentFrame = totalFrames - 1;
        }
        else{
            currentFrame = currentFrame % totalFrames;
        }
    }

    //Gets dimensions of a single sprite from the sprite sheet
    int frameWidth = characterTextures[currentTexture].width / totalFrames;
    int frameHeight = characterTextures[currentTexture].height;

    //dimensions of single sprite
    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    //dimesnsions of user location
    Rectangle dest = {
        hitbox.x - 20, hitbox.y - 45,
        frameWidth * 3,
        frameHeight * 3
    };

    Vector2 origin = { 0, 0 };

    //blocking texture for user 
    if(isBlocking && blockEnergy > 5){
        //dimensions of texture
        Rectangle source = {
            0,
            0,
            (float)characterTextures[3].width,
            (float)characterTextures[3].height
        };

        //dimensions of player
        Rectangle dest = {
            hitbox.x - 40, hitbox.y - 20,
            frameWidth * 3,
            frameHeight * 3
        };

        DrawTexturePro(characterTextures[3], source, dest, origin, 0.0f, WHITE);
    }

    //for hand texture
    if(currentTexture != 0) {   
        //scale of texture   
        float scale = 2.0f;

        //Setting the center at which it will be rotated
        Vector2 pivot = {
            3 * scale,
            14 * scale
        };

        //dmensions of sprite
        Rectangle source = {
            0.0f,
            0.0f,
            characterTextures[4].width,
            characterTextures[4].height
        };

        //dimensions of hand location
        Rectangle dest = {
            hitbox.x + hitbox.width / 2 + 25 - pivot.x,  // Adjusted for scaled pivot
            hitbox.y + hitbox.height / 2 + 15 - pivot.y,
            characterTextures[4].width * scale,
            characterTextures[4].height * scale
        };

        //angle between mouse and player positions
        float angle = atan2(GetMouseY() - hitbox.y - hitbox.height / 2 - 15, GetMouseX() - hitbox.x - hitbox.width / 2 - 25) * RAD2DEG;
        if(angle <= -90.0f && angle >= -180.0f){
            angle = -90.0f;
        }else if(angle <= 180 && angle >= 90.0f){
            angle = 90.0f;
        }

        //display red for 9 frames if damaged
        if(isDamaged){
            DrawTexturePro(characterTextures[4], source, dest, pivot, angle, RED);
        }else{
            DrawTexturePro(characterTextures[4], source, dest, pivot, angle, WHITE);
        }
    }
    
    //display red for 9 frames if damaged
    //This is for normal user texturess
    if(isDamaged){
        DrawTexturePro(characterTextures[currentTexture], source, dest, origin, 0.0f, RED);
        damageFrames++;
        if(damageFrames > 10){
            isDamaged = false;
            damageFrames = 0;
        }
    }else{
        DrawTexturePro(characterTextures[currentTexture], source, dest, origin, 0.0f, WHITE);
    }
}

void User::jump(Sound s) {
    //change texture to jump
    if(jumps == 2){
        currentTexture = 2;
    }
    //change texture to double jump
    else if(jumps == 1){
        currentTexture = 0;
    }
    //if jumps are availabe, sets up jump
    if (jumps>0) {
        PlaySound(s);
        jumpvelocity = JUMP_VELOCITY; 
        jumps--;
        onGround = false;
        onObstacle = false;
        currentFrame = 0;
    }
}

void User::updatejump(Sound s) {
    //if player is in air
    if(!onGround && !onObstacle){
        //changes jump velocity by a fixed amount every frame
        jumpvelocity+= ACCELARATION; 
        hitbox.y += jumpvelocity;

        //Checks if it touches the ground and reinitializes jump if it is and sets the user on the ground
        if (hitbox.y >= GROUND_Y - hitbox.height) {
            hitbox.y = GROUND_Y - hitbox.height;
            jumpvelocity = 0;
            jumps = 2;
            onGround = true;
            currentFrame = 0;
            currentTexture = 1;
        }
    }
    //if user is on obstacle, regenerates jumps
    else if(onObstacle){
        jumpvelocity = 0;
        jumps = 2;
        currentFrame = 0;
        currentTexture = 1;
    }
}

void User::setBlocking(bool val){
    isBlocking = val;
}

void User::updateBlockEnergy(){
    //depletes energy by a fixed rate when blocking
    if(isBlocking){
        blockEnergy -= blockDepletionRate * GetFrameTime();
        if(blockEnergy < 0){blockEnergy = 0;}
    } 
    //when not blocking regenerates energy
    else{
        blockEnergy += blockRegenRate * GetFrameTime();
        if(blockEnergy > maxBlockEnergy){blockEnergy = maxBlockEnergy;}
    }
}

float User::getBlockEnergy()const{
    return blockEnergy;
}

bool User::isCurrentlyBlocking()const{
    return isBlocking && blockEnergy > 0;
}
