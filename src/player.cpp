#include "player.h"

Player::Player(double x, double y, double width, double height, int health){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
    
};

void User::move(int x, int y){ 
    hitbox.x =hitbox.x + x;
    hitbox.y = hitbox.y + y;
}

//Recheck later

Projectile User::useWeapon(int x, int y){
    Projectile newBullet(10, 0, hitbox.x + hitbox.width, hitbox.y + hitbox.height / 2, 5, YELLOW);
        bullets.push_back(newBullet);
        updateBullets();
        return newBullet;
   
}

void Player::updateBullets() {
    for (Projectile& bullet : bullets) {
        bullet.move();
        bullet.draw();
    }
}

bool Player::isAlive(){
    return health == 0;
}

int Player::getHealth(){
    return health;
}

Rectangle& Player::getHitbox(){
    return hitbox;
}

void User::draw(){
    DrawRectangleRec(hitbox, RED);
    updateBullets();
}

void User::jump() {
    if (jumps>0) {
        jumpvelocity = -15; 
        jumping = true;
        jumps--;
    }
}


void User::updatejump() {
    jumpvelocity+= 0.8; 
    hitbox.y += jumpvelocity;

    if (hitbox.y >= GROUND_Y - hitbox.height) {
        hitbox.y = GROUND_Y - hitbox.height;
        jumpvelocity = 0;
        jumping = false;
        jumps =2;
    }
}


Projectile Enemy::useWeapon(int x, int y){
    Projectile newBullet(10, 0, hitbox.x + hitbox.width, hitbox.y + hitbox.height / 2, 5, YELLOW);
        bullets.push_back(newBullet);
        updateBullets();
        return newBullet;
}

void Enemy::draw(){
    DrawRectangleRec(hitbox, PURPLE);
}
