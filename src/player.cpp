#include "player.h"


Player::Player(double x, double y, double width, double height, double health){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
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

double Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

Bomber::Bomber(double x, double y) : Enemy(x, y, BOMBER_WIDTH, BOMBER_HEIGHT, BOMBER_HEALTH), hasDroppedBomb(false), moveSpeed(BOMBER_SPEED){}

void Bomber::move(double x, double y){
    if (!hasDroppedBomb){
        if (hitbox.x < x) hitbox.x += moveSpeed; 
        else if (hitbox.x > x) hitbox.x -= moveSpeed;
    }
    else{
        hitbox.y -= moveSpeed;  
        if (hitbox.y + hitbox.height < 0){
            alive = false;
        }
    }
}

Projectile* Bomber::useWeapon(double userX, double userY){
    if(!alive || hasDroppedBomb) return nullptr;
    if(abs(hitbox.x - userX) < 5){ 
        hasDroppedBomb = true;
        return new Projectile(0, BOMBER_PROJECTILE_SPEEDY, hitbox.x, hitbox.y, BOMBER_PROJECTILE_RADIUS, PURPLE, BOMBER_PROJECTILE_DAMAGE);
    }
    return nullptr;
}

void Bomber::draw(){
    if(alive){
        DrawRectangleRec(hitbox, GREEN);
    }
}

Gunner::Gunner(double x, double y) : Enemy(x, y, GUNNER_WIDTH, GUNNER_HEIGHT, GUNNER_HEALTH), moveDirection(1), shootTimer(0){}

void Gunner::move(double x, double y){ 
    timer += GetFrameTime();   
    if (timer >= GUNNER_MOVE_INTERVAL){
        moveDirection*= -1;
        timer = 0;
    }
    hitbox.x += moveDirection * 1.5f;
}

Projectile* Gunner::useWeapon(double userX, double userY){  
    if(!alive) return nullptr;
    shootTimer += GetFrameTime();
    if (shootTimer >= GUNNER_SHOOT_INTERVAL){
        shootTimer = 0;
        Vector2 direction = {float(userX - hitbox.x),float(userY - hitbox.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * GUNNER_PROJECTILE_SPEED_FACTOR, direction.y * GUNNER_PROJECTILE_SPEED_FACTOR, hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2, GUNNER_PROJECTILE_RADIUS, YELLOW, GUNNER_PROJECTILE_DAMAGE);
    }
    return nullptr;
}

void Gunner::draw(){
    if(alive){
        DrawRectangleRec(hitbox, BLUE);
    }
}

Flyer::Flyer(double x, double y) : Enemy(x, y, FLYER_WIDTH, FLYER_HEIGHT, FLYER_HEALTH){}

void Flyer::draw(){
    if(alive){
        DrawRectangleRec(hitbox, WHITE);
    }
}

Projectile* Flyer::useWeapon(double x, double y){
    return nullptr;
}

User::User() : Player(USER_X, GROUND_Y - USER_HEIGHT, USER_WIDTH, USER_HEIGHT, USER_HEALTH){
    jumpvelocity = 0;
    jumps = 2;
    onGround = true;
    onObstacle = false;
    shootTimer = 0;
}

void User::move(double x, double y){ 
    hitbox.x =hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

Projectile* User::useWeapon(double mouseX, double mouseY){
    if(GetTime() - shootTimer > USER_SHOOT_INTERVAL){
        shootTimer = GetTime();
        Vector2 direction = {float(mouseX - hitbox.x),float(mouseY - hitbox.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * USER_PROJECTILE_SPEED_FACTOR, direction.y * USER_PROJECTILE_SPEED_FACTOR, hitbox.x, hitbox.y, USER_PROJECTILE_RADIUS, YELLOW, USER_PROJECTILE_DAMAGE);
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

//Enemy made by Faran decided to comment it for later

// Projectile Enemy::useWeapon(double x, double y){
//     Projectile newBullet(10, 0, hitbox.x + hitbox.width, hitbox.y + hitbox.height / 2, 5, YELLOW);
//         bullets.push_back(newBullet);
//         updateBullets();
//         return newBullet;
// }
