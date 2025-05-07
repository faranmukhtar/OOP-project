#include "player.h"


Player::Player(double x, double y, double width, double height, double health, double damage){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
    this->damage = damage;
    this->frameCount = 0;
    this->currentFrame = 0;
};

void Player::takeDamage(double val){
    health -= val;
}

void Player::setPosition(double x, double y){
    hitbox.x = x;
    hitbox.y = y;
}

bool Player::isAlive(){
    return health > 0;
}

double Player::getDamage(){
    return damage;
}

double Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

Enemy::Enemy(double x, double y, double width, double height, double health, double damage, string type) : Player(x, y, width, height, health, damage){
    this->type = type;
}

string Enemy::getType(){
    return type;
}

Bomber::Bomber(double x, double y) : Enemy(x, y, BOMBER_WIDTH, BOMBER_HEIGHT, BOMBER_HEALTH, BOMBER_PROJECTILE_DAMAGE, "bomber"), hasDroppedBomb(false){
    targetX = ((rand() % 10) + 0.5) * SCREEN_WIDTH / 10;
}

void Bomber::move(){
    if (!hasDroppedBomb){
        hitbox.x -= BOMBER_SPEED;
    }
    else{
        hitbox.y -= BOMBER_SPEED;
    }
}

Projectile* Bomber::useWeapon(double, double, Sound s){
    if(hasDroppedBomb) return nullptr;
    if(hitbox.x - targetX < 0){ 
        hasDroppedBomb = true;
        PlaySound(s);
        return new Projectile(0, BOMBER_PROJECTILE_SPEEDY, hitbox.x + hitbox.width / 2, hitbox.y, BOMBER_PROJECTILE_RADIUS, PURPLE, damage);
    }
    return nullptr;
}

void Bomber::draw(Texture2D characterTextures[]){
    int totalFrames = 1;

    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    int frameWidth = characterTextures[0].width / totalFrames;
    int frameHeight = characterTextures[0].height;

    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dest = {
        hitbox.x + 20,
        hitbox.y + 20,
        frameWidth * 2,
        frameHeight * 2
    };

    Vector2 origin = {
        (frameWidth * 2) / 2,
        (frameHeight * 2) / 2
    };

    DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, WHITE);
}

Gunner::Gunner(double x, double y, double startX, double startY) : Enemy(x, y, GUNNER_WIDTH, GUNNER_HEIGHT, GUNNER_HEALTH, GUNNER_PROJECTILE_DAMAGE, "gunner"){
    shootTimer = 0;
    moveTimer = 0;
    startPosReached = false;
    startPos.x = startX;
    startPos.y = startY;
    shootTimer = (float)(rand() % int(GUNNER_SHOOT_INTERVAL));
}

void Gunner::move(){ 
    if(!startPosReached){
        Vector2 direction = {float(startPos.x - hitbox.x),float(startPos.y - hitbox.y)};
        direction = Vector2Normalize(direction);
        speed = {direction.x * (float)GUNNER_SPEED, direction.y * (float)GUNNER_SPEED};
        hitbox.x += speed.x;
        hitbox.y += speed.y;
        if(hitbox.x <= startPos.x && (hitbox.y <= startPos.y + 10 && hitbox.y >= startPos.y - 10)){
            startPosReached = true;
            direction.x = rand() % 2 == 0 ? 1 : -1;
            direction.y = rand() % 2 == 0 ? 1 : -1;
            direction = Vector2Normalize(direction);
            speed = {direction.x * (float)GUNNER_SPEED, direction.y * (float)GUNNER_SPEED};
        }
    }
    else{
        moveTimer += GetFrameTime();  
        if (moveTimer >= GUNNER_MOVE_INTERVAL){
            if(hitbox.x <= SCREEN_WIDTH - 400 || 
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
            hitbox.x += speed.x;
            hitbox.y += speed.y;
        }
    }
}

Projectile* Gunner::useWeapon(double userX, double userY, Sound s){  
    shootTimer += GetFrameTime();
    if (shootTimer >= GUNNER_SHOOT_INTERVAL){
        shootTimer = 0;
        Vector2 direction = {float(userX - hitbox.x),float(userY - hitbox.y)};
        direction = Vector2Normalize(direction);
        PlaySound(s);
        return new Projectile(direction.x * GUNNER_PROJECTILE_SPEED_FACTOR, direction.y * GUNNER_PROJECTILE_SPEED_FACTOR, hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2, GUNNER_PROJECTILE_RADIUS, YELLOW, damage);
    }
    return nullptr;
}

void Gunner::draw(Texture2D characterTextures[]){
    DrawRectangleRec(hitbox, BLUE);
}

Flyer::Flyer(double x, double y) : Enemy(x, y, FLYER_WIDTH, FLYER_HEIGHT, FLYER_HEALTH, FLYER_DAMAGE, "flyer"){}

void Flyer::draw(Texture2D characterTextures[]){
    int totalFrames = 8;

    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    int frameWidth = characterTextures[0].width / totalFrames;
    int frameHeight = characterTextures[0].height;

    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dest = {
        hitbox.x + 20,
        hitbox.y + 20,
        frameWidth * 2,
        frameHeight * 2
    };

    Vector2 origin = {
        (frameWidth * 2) / 2,
        (frameHeight * 2) / 2
    };

    DrawTexturePro(characterTextures[0], source, dest, origin, 0.0f, WHITE);
}

void Flyer::move(){
    hitbox.x -= FLYER_SPEED;
}

Projectile* Flyer::useWeapon(double x, double y, Sound){
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
}

void User::move(double x, double y){ 
    hitbox.x = hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

Projectile* User::useWeapon(double mouseX, double mouseY, Sound s){
    if(GetTime() - shootTimer > USER_SHOOT_INTERVAL){
        shootTimer = GetTime();
        PlaySound(s);
        Vector2 shootLocation = {hitbox.x + hitbox.width, hitbox.y + hitbox.height / 4.0};
        Vector2 direction = {float(mouseX - shootLocation.x),float(mouseY - shootLocation.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * USER_PROJECTILE_SPEED_FACTOR, direction.y * USER_PROJECTILE_SPEED_FACTOR, shootLocation.x, shootLocation.y, USER_PROJECTILE_RADIUS, YELLOW, damage);
    }
    return nullptr;
}

void User::setOnObstacle(bool val){
    onObstacle = val;
}

void User::draw(Texture2D characterTextures[]){
    int totalFrames;
    if(currentTexture <= 1){
        totalFrames = 6;
    }else if(currentTexture == 2){
        totalFrames = 4;
    }

    frameCount++;
    if (frameCount >= (60 / 8)) {
        frameCount = 0;
        currentFrame = (currentFrame + 1);
        if(currentTexture == 2 || currentFrame == 0){
            if(currentFrame > totalFrames - 1)
            currentFrame = totalFrames - 1;
        }
        else{
            currentFrame = currentFrame % totalFrames;
        }
    }

    int frameWidth = characterTextures[currentTexture].width / totalFrames;
    int frameHeight = characterTextures[currentTexture].height;

    Rectangle source = {
        (float)(currentFrame * frameWidth),
        0,
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dest = {
        hitbox.x - 20, hitbox.y - 45,
        frameWidth * 3,
        frameHeight * 3
    };

    Vector2 origin = { 0, 0 };

    if(isBlocking && blockEnergy > 5){
        Rectangle source = {
            0,
            0,
            (float)characterTextures[3].width,
            (float)characterTextures[3].height
        };

        Rectangle dest = {
            hitbox.x - 40, hitbox.y - 20,
            frameWidth * 3,
            frameHeight * 3
        };

        DrawTexturePro(characterTextures[3], source, dest, origin, 0.0f, WHITE);
    }

    DrawTexturePro(characterTextures[currentTexture], source, dest, origin, 0.0f, WHITE);
}

void User::jump(Sound s) {
    PlaySound(s);
    if(jumps == 2){
        currentTexture = 2;
    }
    else if(jumps == 1){
        currentTexture = 0;
    }
    if (jumps>0) {
        jumpvelocity = JUMP_VELOCITY; 
        jumps--;
        onGround = false;
        onObstacle = false;
        currentFrame = 0;
    }
}

void User::updatejump(Sound s) {
    if(!onGround && !onObstacle){
        jumpvelocity+= ACCELARATION; 
        hitbox.y += jumpvelocity;

        if (hitbox.y >= GROUND_Y - hitbox.height) {
            hitbox.y = GROUND_Y - hitbox.height;
            jumpvelocity = 0;
            jumps = 2;
            onGround = true;
            currentFrame = 0;
            currentTexture = 1;
        }
    }
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
    if(isBlocking){
        blockEnergy -= blockDepletionRate * GetFrameTime();
        if(blockEnergy < 0){blockEnergy = 0;}
    } 
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
