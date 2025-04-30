#include "player.h"


Player::Player(double x, double y, double width, double height, double health, double damage){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
    this->damage = damage;
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

Enemy::Enemy(double x, double y, double width, double height, double health, double damage, string type) : Player(x, y, width, height, health, damage), timer(0), type(type){}

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

Projectile* Bomber::useWeapon(double, double){
    if(hasDroppedBomb) return nullptr;
    if(hitbox.x - targetX < 0){ 
        hasDroppedBomb = true;
        return new Projectile(0, BOMBER_PROJECTILE_SPEEDY, hitbox.x, hitbox.y, BOMBER_PROJECTILE_RADIUS, PURPLE, damage);
    }
    return nullptr;
}

void Bomber::draw(){
    DrawRectangleRec(hitbox, GREEN);
}

Gunner::Gunner(double x, double y) : Enemy(x, y, GUNNER_WIDTH, GUNNER_HEIGHT, GUNNER_HEALTH, GUNNER_PROJECTILE_DAMAGE, "gunner"), moveDirection(1), shootTimer(0){}

void Gunner::move(){ 
    timer += GetFrameTime();   
    if (timer >= GUNNER_MOVE_INTERVAL){
        moveDirection*= -1;
        timer = 0;
    }
    hitbox.x += moveDirection * 1.5f;
}

Projectile* Gunner::useWeapon(double userX, double userY){  
    shootTimer += GetFrameTime();
    if (shootTimer >= GUNNER_SHOOT_INTERVAL){
        shootTimer = 0;
        Vector2 direction = {float(userX - hitbox.x),float(userY - hitbox.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * GUNNER_PROJECTILE_SPEED_FACTOR, direction.y * GUNNER_PROJECTILE_SPEED_FACTOR, hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2, GUNNER_PROJECTILE_RADIUS, YELLOW, damage);
    }
    return nullptr;
}

void Gunner::draw(){
    DrawRectangleRec(hitbox, BLUE);
}

Flyer::Flyer(double x, double y) : Enemy(x, y, FLYER_WIDTH, FLYER_HEIGHT, FLYER_HEALTH, FLYER_DAMAGE, "flyer"){}

void Flyer::draw(){
    DrawRectangleRec(hitbox, WHITE);
}

void Flyer::move(){
    hitbox.x -= FLYER_SPEED;
}

Projectile* Flyer::useWeapon(double x, double y){
    return nullptr;
}

User::User() : Player(USER_X, GROUND_Y - USER_HEIGHT, USER_WIDTH, USER_HEIGHT, USER_HEALTH, USER_PROJECTILE_DAMAGE){
    jumpvelocity = 0;
    jumps = 2;
    onGround = true;
    onObstacle = false;
    shootTimer = 0;
}

void User::move(double x, double y){ 
    hitbox.x = hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

Projectile* User::useWeapon(double mouseX, double mouseY){
    if(GetTime() - shootTimer > USER_SHOOT_INTERVAL){
        shootTimer = GetTime();
        Vector2 direction = {float(mouseX - hitbox.x),float(mouseY - hitbox.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * USER_PROJECTILE_SPEED_FACTOR, direction.y * USER_PROJECTILE_SPEED_FACTOR, hitbox.x, hitbox.y, USER_PROJECTILE_RADIUS, YELLOW, damage);
    }
    return nullptr;
}

void User::setOnObstacle(bool val){
    onObstacle = val;
}

void User::draw(){
    DrawRectangleRec(hitbox, RED);
    
}

void User::jump() {
    if (jumps>0) {
        jumpvelocity = JUMP_VELOCITY; 
        jumps--;
        onGround = false;
        onObstacle = false;
    }
}

void User::updatejump() {
    if(!onGround && !onObstacle){
        jumpvelocity+= ACCELARATION; 
        hitbox.y += jumpvelocity;

        if (hitbox.y >= GROUND_Y - hitbox.height) {
            hitbox.y = GROUND_Y - hitbox.height;
            jumpvelocity = 0;
            jumps = 2;
            onGround = true;
        }
    }
    else if(onObstacle){
        jumpvelocity = 0;
        jumps = 2;
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
