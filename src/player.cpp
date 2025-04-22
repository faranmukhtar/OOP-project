#include "player.h"


Player::Player(double x, double y, double width, double height, int health){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
};

void Player::takeDamage(double val){
    health -= val;
}

void Player::setPosition(int x, int y){
    hitbox.x = x;
    hitbox.y = y;
}

bool Player::isAlive(){
    return alive;
}

int Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

void Bomber::move(int x, int y){
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

Projectile* Bomber::useWeapon(int userX, int userY){
    if(!alive || hasDroppedBomb) return nullptr;
    if(abs(hitbox.x - userX) < 5){ 
        hasDroppedBomb = true;
        return new Projectile(0, 3, hitbox.x, hitbox.y, 10, PURPLE, 25);
    }
    return nullptr;
}

void Bomber::draw(){
    if(alive){
        DrawRectangleRec(hitbox, GREEN);
    }
}

void Gunner::move(int x, int y){ 
    timer += GetFrameTime();   
    if (timer >= moveInterval){
        moveDirection*= -1;
        timer = 0;
    }
    hitbox.x += moveDirection * 1.5f;
}

Projectile* Gunner::useWeapon(int userX, int userY){  
    if(!alive) return nullptr;
    shootTimer += GetFrameTime();
    if (shootTimer >= shootInterval){
        shootTimer = 0;
        Vector2 direction = {float(userX - hitbox.x),float(userY - hitbox.y)};
        direction = Vector2Normalize(direction);
        return new Projectile(direction.x * 5, direction.y * 5, hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2, 5, YELLOW, 10);
    }
    return nullptr;
}

void Gunner::draw(){
    if(alive){
        DrawRectangleRec(hitbox, BLUE);
    }
}

Flyer::Flyer(double x, double y) : Enemy(x, y, 40, 20, 2){}

void Flyer::draw(){
    if(alive){
        DrawRectangleRec(hitbox, WHITE);
    }
}

Projectile* Flyer::useWeapon(int x, int y){
    return nullptr;
}

void User::move(int x, int y){ 
    hitbox.x =hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

Projectile* User::useWeapon(int x, int y){
    Projectile* newBullet = new Projectile(10, 0, hitbox.x + hitbox.width, hitbox.y + hitbox.height / 2, 5, YELLOW, 50);
    return newBullet;
}

void User::setOnObstacle(bool val){
    onObstacle = val;
}

void User::draw(){
    DrawRectangleRec(hitbox, RED);
}

void User::jump() {
    if (jumps>0) {
        jumpvelocity = -15; 
        jumps--;
        onGround = false;
        onObstacle = false;
    }
}

void User::updatejump() {
    cout << onGround << ", " << onObstacle << endl;
    if(!onGround && !onObstacle){
        jumpvelocity+= 0.8; 
        hitbox.y += jumpvelocity;

        if (hitbox.y >= GROUND_Y - hitbox.height) {
            hitbox.y = GROUND_Y - hitbox.height;
            jumpvelocity = 0;
            jumps =2;
            onGround = true;
        }
    }
    else if(onObstacle){
        jumpvelocity = 0;
        jumps = 2;
    }
}

//Enemy made by Faran decided to comment it for later

// Projectile Enemy::useWeapon(int x, int y){
//     Projectile newBullet(10, 0, hitbox.x + hitbox.width, hitbox.y + hitbox.height / 2, 5, YELLOW);
//         bullets.push_back(newBullet);
//         updateBullets();
//         return newBullet;
// }
