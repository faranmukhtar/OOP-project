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

void User::jump(){
    if(hitbox.y==GROUND_Y -100){
        jumping = 1;
        pos = 150;
    }
    else if(jumping==1 || jumping ==2){
        jumping =3;
        pos = hitbox.y -30;
    }
}

void User::updatejump(){
    if((jumping==1 ||jumping ==3)  && hitbox.y>pos){
        hitbox.y = hitbox.y-10;
        if(hitbox.y<=pos){
            jumping =2;
        }
    }
    if(jumping ==2 &&hitbox.y<GROUND_Y -100){
        hitbox.y = hitbox.y+5;
    }
    if(hitbox.y == GROUND_Y -100){
        jumping = 0;
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
